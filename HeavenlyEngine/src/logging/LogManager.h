#ifndef LOGGER_HEAVENLY_H_
#define LOGGER_HEAVENLY_H_

#include <string>
#include <vector>

// spdlog includes
#include "spdlog.h"
#include "spdlog/sinks/base_sink.h"

namespace spdlog 
{
    class logger;
}

#define HV_LOG_INFO(system, msg)        HV_LOG(system, msg, spdlog::level::info)
#define HV_LOG_WARNING(system, msg)     HV_LOG(system, msg, spdlog::level::warn)
#define HV_LOG_ERROR(system, msg)       HV_LOG(system, msg, spdlog::level::err)
#define HV_LOG_FATAL(system, msg)       HV_LOG(system, msg, spdlog::level::critical)

// TODO: Create macros to call logger
#define HV_LOG(system, msg, level) Heavenly::Logging::LogManager::Log(system, msg, level);

namespace Heavenly
{


namespace Logging
{

class LogManager
{

public:

    static void InitLogging();

    static void Log(const std::string& system, const std::string& msg, const spdlog::level::level_enum& level);

    template<class SinkT, typename ... SinkArgs>
    static void CreateLogger(const std::string& loggerName, SinkArgs &&... sinkArgs)
    {
        static_assert(std::is_base_of_v<spdlog::sinks::base_sink, SinkT>());
        loggers.push_back(spdlog::create<SinkT>(loggerName, std::forward<SinkArgs>(sinkArgs)...));
    }

    static void CreateStdOutLogger(const std::string& name);

private:
    static std::vector<std::shared_ptr<spdlog::logger>> loggers;
};

}

}

#endif
