#pragma once



namespace HeavenlyApp::App
{

class IAppWindow {
public:
	
	IAppWindow(const std::string_view& title) : title(title) {}

	virtual void Draw() = 0;
	
	std::string GetTitle() const {
		return title;
	}

	bool IsOpen() const {
		return isOpen;
	}

private:

	constexpr std::string_view title;
	bool isOpen = true;
}

class IAppScope {
public:
	IAppScope();	

private:

}

void ShowMainMenuBar();

void ShowSceneExplorer();

void ShowInspector();

}