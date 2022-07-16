#include "Application.h"

namespace HBL {

	Application::Application(float width, float height, const std::string& name, bool full_screen)
	{
		GlobalSystems::windowSystem.Initialize(width, height, name, full_screen);
	}

	void Application::Add_Scene(Scene* scene)
	{
		scenes.push_back(scene);
	}

	void Application::Register_System(ISystem* system)
	{
		systems.push_back(system);
	}

}
