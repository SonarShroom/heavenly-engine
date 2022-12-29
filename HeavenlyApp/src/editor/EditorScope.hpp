#pragma once

#include <string_view>

#include <Heavenly.h>

namespace HeavenlyApp::Editor
{

class GUI;

class IEditorScope {
public:
	constexpr ~IEditorScope() = default;

	bool isOpen = true;

	inline constexpr virtual std::string_view GetTitle() const = 0;

	void Draw()
	{
		if (isOpen)
		{
			if (ImGui::Begin(GetTitle().data(), &isOpen))
			{
				DrawContents();
			}
			ImGui::End();
		}
		
	}

protected:
	virtual void DrawContents() = 0;
};

}