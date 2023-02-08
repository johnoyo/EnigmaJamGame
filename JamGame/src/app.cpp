#include "../../Humble/src/Humble.h"
#include "../../Humble/src/Graphics.h"

// User defined components
#include "MyComponents.h"

// User defined systems
#include "Systems\HealthSystem.h"

// User declared systems
HBL::HealthSystem healthSystem;

#include "Levels\MainMenu.h"
#include "Levels\Level1.h"

int main() 
{
	HBL::MainMenu mainMenu;
	HBL::Level1 level1;

	HBL::Application *app = new HBL::Application(1280.0f, 720.0f, "JamGame", false, false, false, 30.0f);

	HBL::Registry::Get().RegisterSystem(&healthSystem);
	HBL::Registry::Get().AddArray<HBL::Component::Health>();

	app->AddScene(&mainMenu);
	app->AddScene(&level1);

	app->Start();

	delete app;

	return 0;
}