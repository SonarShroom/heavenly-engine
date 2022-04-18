#include <catch2/catch.hpp>
#include "world/EntityComponentSystem.h"

namespace Heavenly::Tests
{
SCENARIO("World entity creation", "[EntityComponentSystem]")
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
				REQUIRE(_entityComps.size() == 1);
				REQUIRE(dynamic_cast<WTransComp*>(_entityComps.at(0)));
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

SCENARIO("World system registration", "[EntityComponentSystem]")
{
	GIVEN("A world with an entity with a test component")
	{
		auto* _victim = World::CreateWorld();
		auto* _victimEntity = World::CreateEntity(_victim, "testEntity");
		auto* _victimComp = World::CreateComponent<TestComponent>(_victimEntity);
		
		WHEN("A system that acts on test components is registered")
		{
			World::RegisterSystem(_victim, &TestSystem);
			THEN("Ticking the world changes the component")
			{
				World::Tick(_victim, .0f);
				REQUIRE(_victimComp->hasExecuted);
				REQUIRE(_victimComp->sysExecCount == 1);
			}
		}
		AND_WHEN("No systems are registered")
		{
			THEN("Ticking the world does not change the component's state")
			{
				World::Tick(_victim, .0f);
				REQUIRE_FALSE(_victimComp->hasExecuted);
				REQUIRE_FALSE(_victimComp->sysExecCount);
			}
		}
	}
}

SCENARIO("World entity and component management", "[EntityComponentSystem]")
{
	GIVEN("A world with an entity")
	{
		auto* _victim = World::CreateWorld();
		auto* _victimEntity = World::CreateEntity(_victim, "testEntity");
		WHEN("A test component is created on the entity")
		{
			auto* _victimComponent = World::CreateComponent<TestComponent>(_victimEntity);
			THEN("The world must have the same transform and test components as the entity")
			{
				REQUIRE(dynamic_cast<World::TransformComponent*>(_victim->components.at(0)));
				REQUIRE(dynamic_cast<TestComponent*>(_victim->components.at(1)));
				REQUIRE(_victim->components.at(0) == _victimEntity->components.at(0));
				REQUIRE(_victim->components.at(1) == _victimEntity->components.at(1));
			}
			AND_WHEN("That component is destroyed")
			{
				World::DestroyComponent(_victimComponent);
				THEN("The world must only have a single transform component")
				{
					REQUIRE(_victim->components.size() == 1);
					REQUIRE(dynamic_cast<World::TransformComponent*>(_victim->components.at(0)));
					REQUIRE(_victim->components.at(0) == _victimEntity->components.at(0));
				}
			}
			AND_WHEN("The entity is destroyed")
			{
				World::DestroyEntity(_victimEntity);
				THEN("The world must have no components nor entities")
				{
					REQUIRE(_victim->components.empty());
					REQUIRE(_victim->entities.empty());
				}
			}
		}
	}
}

} // Heavenly::Tests
