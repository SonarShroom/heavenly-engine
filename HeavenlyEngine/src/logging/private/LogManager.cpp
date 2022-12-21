#include "LogManager.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Heavenly::Logging
{

std::shared_ptr<spdlog::logger> p_engineLogger;
std::shared_ptr<spdlog::logger> p_appLogger;

void Init() {

	// Set pattern for out messages:
	spdlog::set_pattern("%^[%Y-%m-%d %H:%M:%S.%e][%n][%l]: %v %$");
	p_engineLogger = spdlog::stdout_color_mt("Heavenly");
	p_appLogger = spdlog::stdout_color_mt("App");
}

void Terminate()
{
	p_engineLogger = nullptr;
	p_appLogger = nullptr;
	spdlog::drop_all();
}

spdlog::logger* GetEngineLogger()
{
	return p_engineLogger.get();
}

spdlog::logger* GetAppLogger()
{
	return p_appLogger.get();
}

}
