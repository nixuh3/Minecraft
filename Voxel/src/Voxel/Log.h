#pragma once

#include "Voxel/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include <memory>

namespace Voxel {

class Log {
  public:
    static void Init();

    static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
    static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

  private:
    inline static std::shared_ptr<spdlog::logger> s_CoreLogger;
    inline static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

// Core log macros
#define VOXEL_CORE_TRACE(...) ::Voxel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define VOXEL_CORE_INFO(...) ::Voxel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define VOXEL_CORE_WARN(...) ::Voxel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define VOXEL_CORE_ERROR(...) ::Voxel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define VOXEL_CORE_CRITICAL(...) ::Voxel::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define VOXEL_TRACE(...) ::Voxel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define VOXEL_INFO(...) ::Voxel::Log::GetClientLogger()->info(__VA_ARGS__)
#define VOXEL_WARN(...) ::Voxel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define VOXEL_ERROR(...) ::Voxel::Log::GetClientLogger()->error(__VA_ARGS__)
#define VOXEL_CRITICAL(...) ::Voxel::Log::GetClientLogger()->critical(__VA_ARGS__)

}
