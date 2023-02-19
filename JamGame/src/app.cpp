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

#include "Levels\MainMenu.h"
#include "Levels\Level1.h"

int main() 
{
	MainMenu* mainMenu = new MainMenu;
	Level1* level1 = new Level1;

	HBL::Application *app = new HBL::Application(1920.0f, 1080.0f, "Cursed Nighmare", false, true, false, 30.0f);

	HBL::Registry::Get().RegisterSystem<MenuSystem>(&menuSystem);
	HBL::Registry::Get().RegisterSystem<TranquilizerSystem>(&tranquilizerSystem);
	HBL::Registry::Get().RegisterSystem<GhostBehaviourSystem>(&ghostBehaviourSystem);
	HBL::Registry::Get().RegisterSystem<GhostStunnerSystem>(&ghostStunnerSystem);
	HBL::Registry::Get().RegisterSystem<CollectibleSystem>(&collectibleSystem);
	HBL::Registry::Get().RegisterSystem<LavaSystem>(&lavaSystem);
	HBL::Registry::Get().RegisterSystem<PlayerHandlerSystem>(&playerHandlerSystem);
	HBL::Registry::Get().RegisterSystem<PlayerHandlerSystem>(&doorSystem);
	HBL::Registry::Get().RegisterSystem<MovingEnemySystem>(&movingEnemySystem);
	HBL::Registry::Get().RegisterSystem<BossBehaviourSystem>(&bossBehaviourSystem);
	HBL::Registry::Get().RegisterSystem<YellowGhostBehaviourSystem>(&yellowGhostBehaviourSystem);
	HBL::Registry::Get().RegisterSystem<PatrolGhostBehaviourSystem>(&patrolGhostBehaviourSystem);

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

	app->AddScene(mainMenu);
	app->AddScene(level1);

	app->Start();

	delete mainMenu;
	delete level1;
	delete app;

	return 0;
}