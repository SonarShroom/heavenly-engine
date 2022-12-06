#pragma once

#include <string_view>

namespace HeavenlyApp::App
{

class Runtime;

class IAppWindow {
public:
	
	constexpr IAppWindow(const std::string_view& title) : title(title) {}

	virtual void Draw() = 0;
	
	const std::string_view& GetTitle() const {
		return title;
	}

	bool IsOpen() const {
		return isOpen;
	}

private:

	const std::string_view title;
	bool isOpen = true;
};

class IAppScope {
public:
	IAppScope();	

private:

};

class EditorGUI
{
public:
	EditorGUI(Runtime& runtime) : runtime(runtime) { }

	void ShowMainMenuBar();

	void ShowSceneExplorer();

	void ShowInspector();

private:
	bool showSceneExplorer = true;

	Runtime& runtime;
};



}