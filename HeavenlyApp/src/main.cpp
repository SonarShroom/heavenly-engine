#include <Heavenly.h>

#include <memory>

#include "app/Runtime.h"

int main(int argc, char** argv)
{
	using EngineT = Heavenly::Core::Engine;
	EngineT _engine = EngineT(argc, argv, std::make_unique<HeavenlyApp::App::Runtime>(_engine));
	return _engine.Run();
}
