#include "LogManager.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Heavenly::Logging
{

std::vector<std::shared_ptr<spdlog::logger>> LogManager::loggers;

void LogManager::Init() {

    // Set pattern for out messages:
    spdlog::set_pattern("%^[%Y-%m-%d %H:%M:%S.%e][%n][%l]: %v %$");

    // Create main std out logger
    CreateStdOutLogger("Heavenly");
}

void LogManager::CreateStdOutLogger(const std::string& loggerName)
{
    LogManager::loggers.push_back(spdlog::stdout_color_mt(loggerName));
}

}
