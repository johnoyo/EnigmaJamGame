#include "../../Humble/src/Humble.h"
#include "../../Humble/src/Graphics.h"

// User defined components
#include "MyComponents.h"

// User defined systems
#include "Systems\TranquilizerSystem.h"
#include "Systems\GhostBehaviourSystem.h"
#include "Systems\GhostStunnerSystem.h"
#include "Systems\CollectibleSystem.h"
#include "Systems\LavaSystem.h"
#include "Systems\PlayerHandlerSystem.h"
#include "Systems\DoorSystem.h"
#include "Systems\MenuSystem.h"
#include "Systems\MovingEnemySystem.h"
#include "Systems\BossBehaviourSystem.h"
#include "Systems\YellowGhostBehaviourSystem.h"
#include "Systems\PatrolGhostBehaviourSystem.h"
#include "Systems\LightSystem.h"

// User declared systems
MenuSystem menuSystem;
TranquilizerSystem tranquilizerSystem;
GhostBehaviourSystem ghostBehaviourSystem;
GhostStunnerSystem ghostStunnerSystem;
CollectibleSystem collectibleSystem;
LavaSystem lavaSystem;
PlayerHandlerSystem playerHandlerSystem;
DoorSystem doorSystem;
MovingEnemySystem movingEnemySystem;
BossBehaviourSystem bossBehaviourSystem;
YellowGhostBehaviourSystem yellowGhostBehaviourSystem;
PatrolGhostBehaviourSystem patrolGhostBehaviourSystem;
LightSystem lightSystem;

#include "Levels\MainMenu.h"
#include "Levels\Level1.h"

int main() 
{
	MainMenu* mainMenu = new MainMenu;
	Level1* level1 = new Level1;

	HBL::Application *app = new HBL::Application(1920.0f, 1080.0f, "Cursed Nighmare", false, false, false, 30.0f);

	HBL::Registry::Get().RegisterSystem(&menuSystem);
	HBL::Registry::Get().RegisterSystem(&tranquilizerSystem);
	HBL::Registry::Get().RegisterSystem(&ghostBehaviourSystem);
	HBL::Registry::Get().RegisterSystem(&ghostStunnerSystem);
	HBL::Registry::Get().RegisterSystem(&collectibleSystem);
	HBL::Registry::Get().RegisterSystem(&lavaSystem);
	HBL::Registry::Get().RegisterSystem(&playerHandlerSystem);
	HBL::Registry::Get().RegisterSystem(&doorSystem);
	HBL::Registry::Get().RegisterSystem(&movingEnemySystem);
	HBL::Registry::Get().RegisterSystem(&bossBehaviourSystem);
	HBL::Registry::Get().RegisterSystem(&yellowGhostBehaviourSystem);
	HBL::Registry::Get().RegisterSystem(&patrolGhostBehaviourSystem);
	HBL::Registry::Get().RegisterSystem(&lightSystem);

	HBL::Registry::Get().AddArray<MyComponent::Menu>();
	HBL::Registry::Get().AddArray<MyComponent::Tranquilizer>();
	HBL::Registry::Get().AddArray<MyComponent::GhostBehaviour>();
	HBL::Registry::Get().AddArray<MyComponent::GhostStunner>();
	HBL::Registry::Get().AddArray<MyComponent::Collectible>();
	HBL::Registry::Get().AddArray<MyComponent::Lava>();
	HBL::Registry::Get().AddArray<MyComponent::PlayerHandler>();
	HBL::Registry::Get().AddArray<MyComponent::Door>();
	HBL::Registry::Get().AddArray<MyComponent::MovingGhostBehaviour>();
	HBL::Registry::Get().AddArray<MyComponent::BossBehaviour>();
	HBL::Registry::Get().AddArray<MyComponent::YellowGhostBehaviour>();
	HBL::Registry::Get().AddArray<MyComponent::PatrolGhostBehaviour>();
	HBL::Registry::Get().AddArray<MyComponent::Light>();

	app->AddScene(mainMenu);
	app->AddScene(level1);

	app->Start();

	delete mainMenu;
	delete level1;
	delete app;

	return 0;
}