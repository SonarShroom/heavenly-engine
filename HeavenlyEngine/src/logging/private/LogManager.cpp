#include "LogManager.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Heavenly::Logging
{

std::shared_ptr<spdlog::logger> _engineLogger;
std::shared_ptr<spdlog::logger> _appLogger;

void Init() {

    // Set pattern for out messages:
    spdlog::set_pattern("%^[%Y-%m-%d %H:%M:%S.%e][%n][%l]: %v %$");
	_engineLogger = spdlog::stdout_color_mt("Heavenly");
	_appLogger = spdlog::stdout_color_mt("App");
}

spdlog::logger* GetEngineLogger()
{
	return _engineLogger.get();
}

spdlog::logger* GetAppLogger()
{
	return _appLogger.get();
}

}
