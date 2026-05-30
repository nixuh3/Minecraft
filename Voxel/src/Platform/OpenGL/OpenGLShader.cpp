#include "pch.h"
#include "OpenGLShader.h"

#include <glm/gtc/type_ptr.hpp>
#include <glad/gl.h>

namespace Voxel {

namespace {
GLenum ShaderTypeFromString(std::string_view type) {
    if (type == "vertex") {
        return GL_VERTEX_SHADER;
    }
    if (type == "fragment" || type == "pixel") {
        return GL_FRAGMENT_SHADER;
    }

    VOXEL_CORE_ASSERT(false, "Unknown shader type");
    return 0;
}
}

OpenGLShader::OpenGLShader(
    std::string_view name, std::string_view vertSrc, std::string_view fragSrc)
    : m_Name(name) {
    std::unordered_map<GLenum, std::string> sources;
    sources[GL_VERTEX_SHADER] = vertSrc;
    sources[GL_FRAGMENT_SHADER] = fragSrc;
    Compile(sources);
}

OpenGLShader::OpenGLShader(std::string_view filepath) {
    std::string source = ReadFile(filepath);
    auto shaderSources = Preprocess(source);
    Compile(shaderSources);

    auto lastSlash = filepath.find_last_of("/\\");
    lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
    auto lastDot = filepath.rfind(".");
    auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
    m_Name = filepath.substr(lastSlash, count);
}

OpenGLShader::~OpenGLShader() { glDeleteProgram(m_RendererID); }

void OpenGLShader::Bind() const { glUseProgram(m_RendererID); }

void OpenGLShader::Unbind() const { glUseProgram(0); }

void OpenGLShader::UploadUniformInt(std::string_view name, int value) {
    int location = glGetUniformLocation(m_RendererID, name.data());
    glUniform1i(location, value);
}

void OpenGLShader::UploadUniformFloat(std::string_view name, float value) {
    int location = glGetUniformLocation(m_RendererID, name.data());
    glUniform1f(location, value);
}

void OpenGLShader::UploadUniformFloat2(std::string_view name, const glm::vec2& value) {
    int location = glGetUniformLocation(m_RendererID, name.data());
    glUniform2f(location, value.x, value.y);
}

void OpenGLShader::UploadUniformFloat3(std::string_view name, const glm::vec3& value) {
    int location = glGetUniformLocation(m_RendererID, name.data());
    glUniform3f(location, value.x, value.y, value.z);
}

void OpenGLShader::UploadUniformFloat4(std::string_view name, const glm::vec4& value) {
    int location = glGetUniformLocation(m_RendererID, name.data());
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void OpenGLShader::UploadUniformMat3(std::string_view name, const glm::mat3& matrix) {
    int location = glGetUniformLocation(m_RendererID, name.data());
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::UploadUniformMat4(std::string_view name, const glm::mat4& matrix) {
    int location = glGetUniformLocation(m_RendererID, name.data());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

std::string OpenGLShader::ReadFile(std::string_view filepath) {
    std::ifstream in(std::string(filepath), std::ios::binary | std::ios::ate);
    std::string result;

    if (in) {
        result.resize(static_cast<size_t>(in.tellg()));
        in.seekg(0, std::ios::beg);
        in.read(result.data(), result.size());
        in.close();
    } else {
        VOXEL_CORE_ERROR("Could not open file: '{0}'", filepath);
    }

    return result;
}

std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(std::string_view source) {
    std::unordered_map<GLenum, std::string> sources;

    std::string_view typeToken = "#type";
    size_t typeTokenLength = typeToken.size();
    size_t pos = source.find(typeToken, 0);
    while (pos != std::string::npos) {
        size_t eol = source.find_first_of("\r\n", pos);
        VOXEL_CORE_ASSERT(eol != std::string::npos, "Syntax error");
        size_t begin = pos + typeTokenLength + 1;
        std::string_view type = source.substr(begin, eol - begin);
        VOXEL_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");
        size_t nextLinePos = source.find_first_not_of("\r\n", eol);
        pos = source.find(typeToken, nextLinePos);
        sources[ShaderTypeFromString(type)] = source.substr(nextLinePos,
            pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
    }

    return sources;
}

void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {
    GLuint program = glCreateProgram();

    VOXEL_CORE_ASSERT(shaderSources.size() <= 2, "2 shaders maximum");
    std::array<GLuint, 2> glShaderIDs;

    for (int i = 0; const auto& [type, shaderSource] : shaderSources) {
        GLuint shader = glCreateShader(type);

        const GLchar* source = shaderSource.c_str();
        glShaderSource(shader, 1, &source, 0);

        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(shader);

            VOXEL_CORE_ERROR(infoLog.data());
            VOXEL_CORE_ASSERT(false, "Shader compilation failure!");
            break;
        }

        glAttachShader(program, shader);
        glShaderIDs[i++] = shader;
    }

    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        glDeleteProgram(program);

        for (auto id : glShaderIDs) {
            glDeleteShader(id);
        }

        VOXEL_CORE_ERROR(infoLog.data());
        VOXEL_CORE_ASSERT(false, "Shader linking failure!");
        return;
    }

    for (auto id : glShaderIDs) {
        glDetachShader(program, id);
    }
    m_RendererID = program;
}

}
