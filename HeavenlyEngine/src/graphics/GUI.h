#ifndef GUI_H_
#define GUI_H_

#include "EntityComponentSystem.h"
#include "MathBaseTypes.h"
#include <string>

namespace Heavenly::GUI
{

class GUIComponent : public EntityComponentSystem::Component
{
public:
	Math::Vector2 position;
	Math::Vector2 size;
};

class GUISystem
{
public:
	void Tick(float time_delta);
};

}

#endif //GUI_H_
