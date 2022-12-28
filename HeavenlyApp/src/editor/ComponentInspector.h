#pragma once

#include <string_view>

#include <Heavenly.h>

namespace HeavenlyApp::Editor
{

class IComponentInspector
{
public:
	virtual ~IComponentInspector() = default;
	constexpr virtual std::string_view GetInspectorTitle() = 0;
	virtual void InspectComponent() = 0;
};

template <typename InspectorT>
concept InspectorType = std::is_base_of_v<IComponentInspector, InspectorT>;

}