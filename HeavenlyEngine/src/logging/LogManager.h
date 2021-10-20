#ifndef LOG_MANAGER_H_
#define LOG_MANAGER_H_

#include <string>
#include <vector>

// spdlog includes
#include "spdlog.h"
#include "spdlog/sinks/base_sink.h"

#define HV_LOG_INFO(msg, ...)        HV_LOG(spdlog::level::info, msg, ##__VA_ARGS__)
#define HV_LOG_WARNING(msg, ...)     HV_LOG(spdlog::level::warn, msg, ##__VA_ARGS__)
#define HV_LOG_ERROR(msg, ...)       HV_LOG(spdlog::level::err, msg, ##__VA_ARGS__)
#define HV_LOG_FATAL(msg, ...)       HV_LOG(spdlog::level::critical, msg, ##__VA_ARGS__)

// TODO: Create macros to call logger
#define HV_LOG(level, msg, ...)      Heavenly::Logging::LogManager::Log(level, msg, ##__VA_ARGS__)

namespace Heavenly
{


namespace Logging
{

class LogManager
{

public:

    static void Init();

    // TODO: Understand why this Args var cannot be const
    template<typename ...Args>
    static void Log(const spdlog::level::level_enum& level, Args&&... msgArgs)
    {
        // TODO: Log to all loggers
        for(auto logger : loggers) {
            logger->log(level, msgArgs...);
        }
    }

    template<class SinkT, typename ...SinkArgs>
    static void CreateLogger(const std::string& loggerName, const SinkArgs&&... sinkArgs)
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

#endif //LOG_MANAGER_H_
