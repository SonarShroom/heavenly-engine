#include <Heavenly.h>

#include "appruntime.h"

int main(int argc, char** argv)
{
	auto* _app = new HeavenlyApp::App::Runtime();
	Heavenly::Run(argc, argv, _app);
	delete _app;
	return 0;
}
