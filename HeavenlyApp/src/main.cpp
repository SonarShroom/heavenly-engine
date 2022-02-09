#include <Heavenly.h>

Heavenly::AppRuntime* CreateAppRuntime()
{
	// TODO: Create app lifetime functions. For now they are still inside the engine.
	auto* _appRuntime = new Heavenly::AppRuntime();
	return _appRuntime;
}

int main()
{
	auto* _app = CreateAppRuntime();
	Heavenly::Run(_app);
	delete _app;
	return 0;
}
