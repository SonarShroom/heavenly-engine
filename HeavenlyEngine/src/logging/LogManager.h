#ifndef LOGGER_HEAVENLY_H_
#define LOGGER_HEAVENLY_H_

#include <string>
#include <vector>

// spdlog includes
#include "logger.h"

#define HV_LOG_INFO(system, msg) HV_LOG(system, msg, spdlog::level::info)
#define HV_LOG_WARNING(system, msg) HV_LOG(system, msg, spdlog::level::warn)
#define HV_LOG_ERROR(system, msg) HV_LOG(system, msg, spdlog::level::err)
#define HV_LOG_FATAL(system, msg) HV_LOG(system, msg, spdlog::level::critical)

// TODO: Create macros to call logger
#define HV_LOG(system, msg, level) LogManager::Log(system, msg, level);

class LogManager {

public:
    static void Log(const std::string& system, const std::string& msg, const spdlog::level::level_enum& level);

private:
    std::vector<spdlog::logger> loggers;
};

#endif
