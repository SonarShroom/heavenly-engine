#include <catch2/catch_all.hpp>

#include <memory>

#include "world/Component.h"
#include "world/Entity.h"
#include "world/WorldAdmin.h"

namespace Heavenly::Tests
{
SCENARIO("World entity creation", "[EntityComponentSystem]")
{
	GIVEN("An empty world")
	{
		World::WorldAdmin _victim;

		WHEN("An entity is created")
		{
			auto& _entity = _victim.CreateEntity("victimEntity");
			THEN("It must be registered within the world")
			{
				REQUIRE(_victim.GetEntity("victimEntity") != nullptr);
			}
			AND_THEN("It must only have a transform component")
			{
				using WTransComp = World::TransformComponent;
				auto _entityComps = _entity.GetComponents();
				REQUIRE(_entityComps.size() == 1);
				REQUIRE(dynamic_cast<WTransComp*>(&_entityComps.at(0).get()));
			}
		}
	}
}

struct TestComponent : public World::Component
{
	TestComponent(World::Entity& ent) : Component(ent) {}

	bool hasExecuted = false;		// Has the system executed at least once
	unsigned int sysExecCount = 0;		// Test system execution count
};

void TestSystem(TestComponent& testComp, float deltaTime)
{
	if (!testComp.hasExecuted) {
		testComp.hasExecuted = true;
	}
	
	testComp.sysExecCount++;
}

SCENARIO("World system registration", "[EntityComponentSystem]")
{
	GIVEN("A world with an entity with a test component")
	{
		World::WorldAdmin _victim;
		auto& _victimEntity = _victim.CreateEntity("testEntity");
		auto* _victimComp = _victim.CreateComponent<TestComponent>(_victimEntity);
		
		WHEN("A system that acts on test components is registered")
		{
			_victim.RegisterSystem(&TestSystem);
			THEN("Ticking the world changes the component")
			{
				_victim.Tick(.0f);
				REQUIRE(_victimComp->hasExecuted);
				REQUIRE(_victimComp->sysExecCount == 1);
			}
		}
		AND_WHEN("No systems are registered")
		{
			THEN("Ticking the world does not change the component's state")
			{
				_victim.Tick(.0f);
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
		World::WorldAdmin _victim;
		auto& _victimEntity = _victim.CreateEntity("testEntity");
		WHEN("A test component is created on the entity")
		{
			auto* _victimComponent = _victim.CreateComponent<TestComponent>(_victimEntity);
			THEN("The world must have the same transform and test components as the entity")
			{
				auto _victimEntityComps = _victimEntity.GetComponents();
				REQUIRE(dynamic_cast<World::TransformComponent*>(&_victimEntityComps[0].get()));
				REQUIRE(&_victimEntity.GetComponents()[0]);
				REQUIRE(_victim.IsComponentRegistered(*_victimComponent));
				REQUIRE(dynamic_cast<TestComponent*>(&_victimEntityComps[1].get()));
			}
			AND_WHEN("That component is destroyed")
			{
				_victim.DestroyComponent(*_victimComponent);
				THEN("The world must only have a single transform component")
				{
					REQUIRE(_victim.GetNumComponents() == 1);
					REQUIRE(_victim.IsComponentRegistered(_victimEntity.GetComponents()[0]));
				}
			}
			AND_WHEN("The entity is destroyed")
			{
				_victim.DestroyEntity("testEntity");
				THEN("The world must have no components nor entities")
				{
					REQUIRE(_victim.GetNumComponents() == 0);
					REQUIRE(_victim.GetNumEntities() == 0);
				}
			}
		}
	}
}

} // Heavenly::Tests
