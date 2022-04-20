#ifndef LOG_MANAGER_H_
#define LOG_MANAGER_H_

#include <string>
#include <vector>

// spdlog includes
#include "spdlog.h"
#include "spdlog/sinks/base_sink.h"

#define HV_LOG_INFO(msg, ...)        HV_LOG(spdlog::level::info, msg __VA_OPT__(,) __VA_ARGS__)
#define HV_LOG_WARNING(msg, ...)     HV_LOG(spdlog::level::warn, msg __VA_OPT__(,) __VA_ARGS__)
#define HV_LOG_ERROR(msg, ...)       HV_LOG(spdlog::level::err, msg __VA_OPT__(,) __VA_ARGS__)
#define HV_LOG_FATAL(msg, ...)       HV_LOG(spdlog::level::critical, msg __VA_OPT__(,) __VA_ARGS__)

// TODO: Create macros to call logger
#define HV_LOG(level, msg, ...)      ::Heavenly::Logging::GetEngineLogger()->log(level, msg __VA_OPT__(,) __VA_ARGS__)

namespace Heavenly::Logging
{
	void Init();

	spdlog::logger* GetEngineLogger();
	spdlog::logger* GetAppLogger();
}

#endif //LOG_MANAGER_H_
