#include "LogManager.h"

#include "spdlog/sinks/stdout_color_sinks.h"

using namespace Heavenly::Logging;

std::vector<std::shared_ptr<spdlog::logger>> LogManager::loggers;

void LogManager::InitLogging() {

    // Set pattern for out messages:
    spdlog::set_pattern("%^[%Y-%m-%d %H:%M:%S.%e][%l] %n: %v %$");

    // Create main std out logger
    CreateStdOutLogger("Heavenly");
}

void LogManager::Log(const std::string& system, const std::string& msg, const spdlog::level::level_enum& level)
{
    // TODO: Log to all loggers
    for(auto logger : loggers) {
        logger->log(level, "[{0}] {1}", system, msg);
    }
}

void LogManager::CreateStdOutLogger(const std::string& loggerName)
{
    LogManager::loggers.push_back(spdlog::stdout_color_mt(loggerName));
}