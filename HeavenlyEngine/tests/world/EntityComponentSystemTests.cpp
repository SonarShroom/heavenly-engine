#include <catch2/catch.hpp>
#include "world/EntityComponentSystem.h"

namespace Heavenly::Tests
{
SCENARIO("World entities created", "[EntityComponentSystem]")
{
	GIVEN("An empty world")
	{
		auto* _victim = World::CreateWorld();

		WHEN("An entity is created")
		{
			auto* _entity = World::CreateEntity(_victim, "victimEntity");
			THEN("It must be registered within the world")
			{
				auto _victimEntities = _victim->entities;
				REQUIRE(std::find(_victimEntities.begin(), _victimEntities.end(), _entity) != _victimEntities.end());
			}
			AND_THEN("It must only have a transform component")
			{
				using WTransComp = World::TransformComponent;
				auto _entityComps = _entity->components;
				REQUIRE(_entityComps.size() == 1 && dynamic_cast<WTransComp*>(_entityComps.at(0)));
			}
		}
	}
}

struct TestComponent : public World::Component
{
	TestComponent(World::Entity* ent) : World::Component(ent) {}

	bool hasExecuted = false;		// Has the system executed at least once
	unsigned int sysExecCount = 0;	// Test system execution count
};

void TestSystem(TestComponent* testComp, float deltaTime)
{
	if (!testComp->hasExecuted) {
		testComp->hasExecuted = true;
	}
	
	testComp->sysExecCount++;
}

SCENARIO("World ticking", "[EntityComponentSystem]")
{
	
}

} // Heavenly::Tests
