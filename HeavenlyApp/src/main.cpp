#include <Heavenly.h>

#include "appruntime.h"

Heavenly::Core::AppRuntime* CreateAppRuntime()
{
	auto* _app = new Heavenly::Core::AppRuntime();

	_app->bootFunction = HeavenlyApp::App::OnBoot;
	_app->updateFunction = HeavenlyApp::App::OnUpdate;
	_app->drawImGuiFunction = HeavenlyApp::App::OnDrawImGui;
	
	return _app;
}

int main(int argc, char** argv)
{
	auto _app = CreateAppRuntime();
	Heavenly::Run(argc, argv, _app);
	delete _app;
	return 0;
}
