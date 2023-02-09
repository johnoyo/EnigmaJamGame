#include "../../Humble/src/Humble.h"
#include "../../Humble/src/Graphics.h"

// User defined components
#include "MyComponents.h"

// User defined systems
#include "Systems\PlayerDirectionSystem.h"
#include "Systems\GhostBehaviourSystem.h"
#include "Systems\GhostStunnerSystem.h"

// User declared systems
PlayerDirectionSystem playerDirectionSystem;
GhostBehaviourSystem ghostBehaviourSystem;
GhostStunnerSystem ghostStunnerSystem;

#include "Levels\MainMenu.h"
#include "Levels\Level1.h"

int main() 
{
	MainMenu* mainMenu = new MainMenu;
	Level1* level1 = new Level1;

	HBL::Application *app = new HBL::Application(1920.0f, 1080.0f, "JamGame", false, false, false, 30.0f);

	HBL::Registry::Get().RegisterSystem(&playerDirectionSystem);
	HBL::Registry::Get().RegisterSystem(&ghostBehaviourSystem);
	HBL::Registry::Get().RegisterSystem(&ghostStunnerSystem);

	HBL::Registry::Get().AddArray<MyComponent::PlayerDirection>();
	HBL::Registry::Get().AddArray<MyComponent::GhostBehaviour>();
	HBL::Registry::Get().AddArray<MyComponent::GhostStunner>();

	app->AddScene(mainMenu);
	app->AddScene(level1);

	app->Start();

	delete mainMenu;
	delete level1;
	delete app;

	return 0;
}