#include "Level1.h"

using namespace HBL;

void Level1::OnAttach()
{
	// Enroll entities.
	for (uint32_t i = 0; i < 1700; i++)
		Registry::Get().EnrollEntity(wall[i]);

	for (uint32_t i = 0; i < 5500; i++)
		Registry::Get().EnrollEntity(floor[i]);

	for (uint32_t i = 0; i < 3; i++)
		Registry::Get().EnrollEntity(door[i]);

	for (uint32_t i = 0; i < 20; i++)
		Registry::Get().EnrollEntity(territory[i]);

	for (uint32_t i = 0; i < 20; i++)
		Registry::Get().EnrollEntity(doorWay[i]);

	Registry::Get().EnrollEntity(player, "Player");

	for (uint32_t i = 0; i < 200; i++)
		Registry::Get().EnrollEntity(enemy[i], "Ghost");

	for (uint32_t i = 0; i < 20; i++)
		Registry::Get().EnrollEntity(movingEnemy[i]);

	for (uint32_t i = 0; i < 6; i++)
		Registry::Get().EnrollEntity(patrolEnemy[i]);

	for (uint32_t i = 0; i < 150; i++)
		Registry::Get().EnrollEntity(yellowEnemy[i], "Ghost");

	for (uint32_t i = 0; i < 500; i++)
		Registry::Get().EnrollEntity(lava[i]);

	for (uint32_t i = 0; i < 200; i++)
		Registry::Get().EnrollEntity(collectible[i]);

	Registry::Get().EnrollEntity(tranquilizerWave, "TranquilizerWave");
	Registry::Get().EnrollEntity(camera, "Camera");

	Registry::Get().EnrollEntity(key[0], "Key0");
	Registry::Get().EnrollEntity(key[1], "Key1");
	Registry::Get().EnrollEntity(key[2], "Key2");

	Registry::Get().EnrollEntity(coinsCounter, "CoinsCounter");

	Registry::Get().EnrollEntity(boss, "Boss");

	Registry::Get().EnrollEntity(light, "Light");

	// Add components.
	for (uint32_t i = 0; i < 1700; i++)
	{
		Registry::Get().AddComponent<Component::CollisionBox>(wall[i]);
		Registry::Get().AddComponent<Component::SpriteRenderer>(wall[i]);
		Registry::Get().AddComponent<Component::Shadow>(wall[i]);
	}

	for (uint32_t i = 0; i < 3; i++)
	{
		Registry::Get().AddComponent<Component::Shadow>(door[i]);
		Registry::Get().AddComponent<Component::CollisionBox>(door[i]);
		Registry::Get().AddComponent<Component::SpriteRenderer>(door[i]);
		Registry::Get().AddComponent<MyComponent::Door>(door[i]);
	}

	for (uint32_t i = 0; i < 5500; i++)
	{
		Registry::Get().AddComponent<Component::SpriteRenderer>(floor[i]);
	}

	for (uint32_t i = 0; i < 20; i++)
	{
		Registry::Get().AddComponent<Component::SpriteRenderer>(territory[i]);
		Registry::Get().AddComponent<Component::CollisionBox>(territory[i]);
	}

	for (uint32_t i = 0; i < 20; i++)
	{
		Registry::Get().AddComponent<Component::SpriteRenderer>(doorWay[i]);
	}

	for (uint32_t i = 0; i < 200; i++)
	{
		Registry::Get().AddComponent<Component::SpriteRenderer>(enemy[i]);
		Registry::Get().AddComponent<Component::CollisionBox>(enemy[i]);
		Registry::Get().AddComponent<Component::Animation>(enemy[i]);
		Registry::Get().AddComponent<MyComponent::GhostBehaviour>(enemy[i]);
		Registry::Get().AddComponent<MyComponent::GhostStunner>(enemy[i]);
	}

	for (uint32_t i = 0; i < 150; i++)
	{
		Registry::Get().AddComponent<Component::SpriteRenderer>(yellowEnemy[i]);
		Registry::Get().AddComponent<Component::CollisionBox>(yellowEnemy[i]);
		Registry::Get().AddComponent<Component::Animation>(yellowEnemy[i]);
		Registry::Get().AddComponent<MyComponent::YellowGhostBehaviour>(yellowEnemy[i]);
		Registry::Get().AddComponent<MyComponent::GhostStunner>(yellowEnemy[i]);
	}

	for (uint32_t i = 0; i < 20; i++)
	{
		Registry::Get().AddComponent<Component::SpriteRenderer>(movingEnemy[i]);
		Registry::Get().AddComponent<Component::CollisionBox>(movingEnemy[i]);
		Registry::Get().AddComponent<Component::Animation>(movingEnemy[i]);
		Registry::Get().AddComponent<MyComponent::MovingGhostBehaviour>(movingEnemy[i]);
	}

	for (uint32_t i = 0; i < 6; i++)
	{
		Registry::Get().AddComponent<Component::SpriteRenderer>(patrolEnemy[i]);
		Registry::Get().AddComponent<Component::CollisionBox>(patrolEnemy[i]);
		Registry::Get().AddComponent<Component::Animation>(patrolEnemy[i]);
		Registry::Get().AddComponent<MyComponent::PatrolGhostBehaviour>(patrolEnemy[i]);
	}

	for (uint32_t i = 0; i < 500; i++)
	{
		Registry::Get().AddComponent<Component::SpriteRenderer>(lava[i]);
		Registry::Get().AddComponent<Component::CollisionBox>(lava[i]);
		Registry::Get().AddComponent<Component::Animation>(lava[i]);
		Registry::Get().AddComponent<MyComponent::Lava>(lava[i]);
	}

	for (uint32_t i = 0; i < 200; i++)
	{
		Registry::Get().AddComponent<Component::SpriteRenderer>(collectible[i]);
		Registry::Get().AddComponent<Component::CollisionBox>(collectible[i]);
		Registry::Get().AddComponent<MyComponent::Collectible>(collectible[i]);
	}

	for (uint32_t i = 0; i < 3; i++)
	{
		Registry::Get().AddComponent<Component::CollisionBox>(key[i]);
		Registry::Get().AddComponent<Component::SpriteRenderer>(key[i]);
	}

	Registry::Get().AddComponent<Component::SpriteRenderer>(player);
	Registry::Get().AddComponent<Component::CollisionBox>(player);
	Registry::Get().AddComponent<Component::Animation>(player);
	Registry::Get().AddComponent<Component::Text>(player);
	Registry::Get().AddComponent<MyComponent::PlayerHandler>(player);

	Registry::Get().AddComponent<Component::Camera>(camera);

	Registry::Get().AddComponent<Component::SpriteRenderer>(tranquilizerWave);
	Registry::Get().AddComponent<Component::CollisionBox>(tranquilizerWave);
	Registry::Get().AddComponent<Component::Text>(tranquilizerWave);
	Registry::Get().AddComponent<Component::Animation>(tranquilizerWave);
	Registry::Get().AddComponent<MyComponent::Tranquilizer>(tranquilizerWave);

	Registry::Get().AddComponent<Component::Text>(coinsCounter);

	Registry::Get().AddComponent<Component::SpriteRenderer>(boss);
	Registry::Get().AddComponent<Component::CollisionBox>(boss);
	Registry::Get().AddComponent<Component::Animation>(boss);
	Registry::Get().AddComponent<MyComponent::BossBehaviour>(boss);

	Registry::Get().AddComponent<Component::Transform>(light);
	Registry::Get().AddComponent<MyComponent::Light>(light);

	// Initialize components.
	Registry::Get().GetComponent<Component::Text>(player).text = "FEAR: " + std::to_string((int)Registry::Get().GetComponent<MyComponent::PlayerHandler>(player).fear);
	Registry::Get().GetComponent<Component::Text>(player).color = { 0.25f, 0.8f, 0.25f, 1.0f };
	Registry::Get().GetComponent<Component::Text>(player).scale = { 0.75f, 0.75f, 0.f };
	Registry::Get().GetComponent<Component::Text>(player).screenSpace = true;
	Registry::Get().GetComponent<Component::Text>(player).sreenSpaceOffset = { 250.f, Systems::Window.GetHeight() - 163.f };
	Registry::Get().GetComponent<Component::Transform>(player).Static = false;

	Registry::Get().GetComponent<Component::Transform>(boss).Static = true;
	Registry::Get().GetComponent<Component::CollisionBox>(boss).Trigger = true;

	Registry::Get().GetComponent<Component::Transform>(tranquilizerWave).Static = false;
	Registry::Get().GetComponent<Component::CollisionBox>(tranquilizerWave).Trigger = true;

	Registry::Get().GetComponent<Component::Text>(tranquilizerWave).text = "CHARGE: " + std::to_string((int)Registry::Get().GetComponent<MyComponent::Tranquilizer>(tranquilizerWave).remaining);
	Registry::Get().GetComponent<Component::Text>(tranquilizerWave).color = { 1.0f, 0.8f, 0.5f, 1.0f};
	Registry::Get().GetComponent<Component::Text>(tranquilizerWave).scale = { 0.75f, 0.75f, 0.f };
	Registry::Get().GetComponent<Component::Text>(tranquilizerWave).screenSpace = true;
	Registry::Get().GetComponent<Component::Text>(tranquilizerWave).sreenSpaceOffset = { Systems::Window.GetWidth() - 525.f, Systems::Window.GetHeight() - 163.f };

	Registry::Get().GetComponent<Component::Text>(coinsCounter).text = "COINS: " + std::to_string(0) + "/12";
	Registry::Get().GetComponent<Component::Text>(coinsCounter).color = { 1.0f, 0.8f, 0.5f, 1.0f };
	Registry::Get().GetComponent<Component::Text>(coinsCounter).scale = { 0.75f, 0.75f, 0.f };
	Registry::Get().GetComponent<Component::Text>(coinsCounter).screenSpace = true;
	Registry::Get().GetComponent<Component::Text>(coinsCounter).sreenSpaceOffset = { Systems::Window.GetWidth() - 1125.f, Systems::Window.GetHeight() - 163.f };

	Registry::Get().GetComponent<Component::Camera>(camera).projection = glm::ortho( 200.0f, Systems::Window.GetWidth() - 200.f, 113.0f, Systems::Window.GetHeight() - 113.f, -1.0f, 1.0f);

	for (uint32_t i = 0; i < 1700; i++)
	{
		Registry::Get().GetComponent<Component::Transform>(wall[i]).Static = true;
		Registry::Get().GetComponent<Component::Transform>(wall[i]).Enabled = false;
		Registry::Get().GetComponent<Component::CollisionBox>(wall[i]).Enabled = false;
		Registry::Get().GetComponent<Component::SpriteRenderer>(wall[i]).Enabled = false;
		Registry::Get().GetComponent<Component::Shadow>(wall[i]).Enabled = false;
		Registry::Get().GetComponent<Component::Shadow>(wall[i]).source = &player;
	}

	for (uint32_t i = 0; i < 3; i++)
	{
		Registry::Get().GetComponent<Component::Transform>(door[i]).Static = true;
		Registry::Get().GetComponent<Component::Transform>(door[i]).Enabled = false;
		Registry::Get().GetComponent<Component::CollisionBox>(door[i]).Enabled = false;
		Registry::Get().GetComponent<Component::SpriteRenderer>(door[i]).Enabled = false;
		Registry::Get().GetComponent<Component::Shadow>(door[i]).Enabled = false;
		Registry::Get().GetComponent<Component::Shadow>(door[i]).source = &player;
	}

	for (uint32_t i = 0; i < 5500; i++)
	{
		Registry::Get().GetComponent<Component::Transform>(floor[i]).Static = true;
		Registry::Get().GetComponent<Component::Transform>(floor[i]).Enabled = false;
		Registry::Get().GetComponent<Component::SpriteRenderer>(floor[i]).Enabled = false;
	}

	for (uint32_t i = 0; i < 20; i++)
	{
		Registry::Get().GetComponent<Component::Transform>(territory[i]).Static = true;
		Registry::Get().GetComponent<Component::Transform>(territory[i]).Enabled = false;
		Registry::Get().GetComponent<Component::CollisionBox>(territory[i]).Enabled = false;
		Registry::Get().GetComponent<Component::SpriteRenderer>(territory[i]).Enabled = false;
	}

	for (uint32_t i = 0; i < 20; i++)
	{
		Registry::Get().GetComponent<Component::Transform>(doorWay[i]).Static = true;
		Registry::Get().GetComponent<Component::Transform>(doorWay[i]).Enabled = false;
		Registry::Get().GetComponent<Component::SpriteRenderer>(doorWay[i]).Enabled = false;
	}

	for (uint32_t i = 0; i < 20; i++)
	{
		Registry::Get().GetComponent<Component::Transform>(movingEnemy[i]).Static = true;
		Registry::Get().GetComponent<Component::Transform>(movingEnemy[i]).Enabled = false;
		Registry::Get().GetComponent<Component::SpriteRenderer>(movingEnemy[i]).Enabled = false;
		Registry::Get().GetComponent<MyComponent::MovingGhostBehaviour>(movingEnemy[i]).Enabled = false;
	}

	for (uint32_t i = 0; i < 6; i++)
	{
		Registry::Get().GetComponent<Component::Transform>(patrolEnemy[i]).Static = true;
		Registry::Get().GetComponent<Component::Transform>(patrolEnemy[i]).Enabled = false;
		Registry::Get().GetComponent<Component::SpriteRenderer>(patrolEnemy[i]).Enabled = false;
		Registry::Get().GetComponent<MyComponent::PatrolGhostBehaviour>(patrolEnemy[i]).Enabled = false;
	}

	for (uint32_t i = 0; i < 200; i++)
	{
		Registry::Get().GetComponent<Component::Transform>(enemy[i]).Static = true;
		Registry::Get().GetComponent<Component::Transform>(enemy[i]).Enabled = false;
		Registry::Get().GetComponent<Component::SpriteRenderer>(enemy[i]).Enabled = false;
		Registry::Get().GetComponent<MyComponent::GhostBehaviour>(enemy[i]).Enabled = false;
		Registry::Get().GetComponent<MyComponent::GhostStunner>(enemy[i]).Enabled = false;
	}

	for (uint32_t i = 0; i < 150; i++)
	{
		Registry::Get().GetComponent<Component::Transform>(yellowEnemy[i]).Static = false;
		Registry::Get().GetComponent<Component::Transform>(yellowEnemy[i]).Enabled = false;
		Registry::Get().GetComponent<Component::CollisionBox>(yellowEnemy[i]).Trigger = true;
		Registry::Get().GetComponent<Component::SpriteRenderer>(yellowEnemy[i]).Enabled = false;
		Registry::Get().GetComponent<MyComponent::YellowGhostBehaviour>(yellowEnemy[i]).Enabled = false;
		Registry::Get().GetComponent<MyComponent::GhostStunner>(yellowEnemy[i]).Enabled = false;
	}

	for (uint32_t i = 0; i < 500; i++)
	{
		Registry::Get().GetComponent<Component::Tag>(lava[i]).tag = "Lava";
		Registry::Get().GetComponent<Component::Transform>(lava[i]).Static = true;
		Registry::Get().GetComponent<Component::Transform>(lava[i]).Enabled = false;
		Registry::Get().GetComponent<Component::CollisionBox>(lava[i]).Enabled = false;
		Registry::Get().GetComponent<Component::SpriteRenderer>(lava[i]).Enabled = false;
		Registry::Get().GetComponent<Component::Animation>(lava[i]).Enabled = false;
		Registry::Get().GetComponent<MyComponent::Lava>(lava[i]).Enabled = false;
	}

	for (uint32_t i = 0; i < 200; i++)
	{
		Registry::Get().GetComponent<Component::Transform>(collectible[i]).Static = true;
		Registry::Get().GetComponent<Component::Transform>(collectible[i]).Enabled = false;
		Registry::Get().GetComponent<Component::SpriteRenderer>(collectible[i]).Enabled = false;
		Registry::Get().GetComponent<MyComponent::Collectible>(collectible[i]).Enabled = false;
		Registry::Get().GetComponent<Component::CollisionBox>(collectible[i]).Enabled = false;
	}

	for (uint32_t i = 0; i < 3; i++)
	{
		Registry::Get().GetComponent<Component::Transform>(key[i]).Static = true;
		Registry::Get().GetComponent<Component::Transform>(key[i]).Enabled = false;
		Registry::Get().GetComponent<Component::CollisionBox>(key[i]).Enabled = false;
		Registry::Get().GetComponent<Component::SpriteRenderer>(key[i]).Enabled = false;
	}

	InitializeLevel("res/levels/testMap_Tile Layer 1.csv", "res/levels/testMap_Tile Layer 2.csv");
}

void Level1::OnCreate()
{
	SoundManager::Play("res/audio/s.mp3", true);
}

void Level1::OnDetach()
{
	SoundManager::Stop("res/audio/s.mp3");

	for (int i = 0; i < m_LevelTiles.size(); i++)
	{
		m_LevelTiles[i].clear();
	}
	
	m_LevelTiles.clear();

	for (int i = 0; i < m_EntityTiles.size(); i++)
	{
		m_EntityTiles[i].clear();
	}

	m_EntityTiles.clear();
}

void Level1::CSVImporter(const std::string& levelPath, bool level)
{
	std::fstream fin;
	fin.open(levelPath, std::ios::in);
	std::vector<int> row;
	std::string word, temp;

	while (fin >> temp)
	{
		row.clear();

		std::stringstream s(temp);

		while (std::getline(s, word, ','))
		{
			row.push_back(stoi(word));
		}

		if (level)
			m_LevelTiles.push_back(row);
		else
			m_EntityTiles.push_back(row);
	}

	fin.close();
}

void Level1::InitializeLevel(const std::string& levelPath1, const std::string& levelPath2)
{
	CSVImporter(levelPath1, true);

	int rows = m_LevelTiles.size();
	int collumns = m_LevelTiles[0].size();

	SceneManager::Get().m_WorldSize = { (float)rows, (float)collumns };
	SceneManager::Get().m_SectorSize = { 4.0f, 4.0f };
	SceneManager::Get().m_TileSize = 30.0f;

	HandleEntityTiles();

	CSVImporter(levelPath2, false);

	HandleEntities();

	// Tranquilizer wave.
	Component::Transform& tranquilizerTransform = Registry::Get().GetComponent<Component::Transform>(tranquilizerWave);

	tranquilizerTransform.scale.x = 30.0f;
	tranquilizerTransform.scale.y = 30.0f;
	tranquilizerTransform.position.x = 55.f * tranquilizerTransform.scale.x;
	tranquilizerTransform.position.y = 5.f * tranquilizerTransform.scale.y;

	Registry::Get().GetComponent<Component::Animation>(tranquilizerWave).Enabled = false;
	Registry::Get().GetComponent<Component::CollisionBox>(tranquilizerWave).Enabled = true;
	Registry::Get().GetComponent<Component::SpriteRenderer>(tranquilizerWave).Enabled = true;
	Registry::Get().GetComponent<Component::SpriteRenderer>(tranquilizerWave).texture = "res/textures/TranquilizerGun.png";

	// Boss.
	Component::Transform& bossTransform = Registry::Get().GetComponent<Component::Transform>(boss);
	bossTransform.Enabled = true;
	Component::CollisionBox& bossCollisionBox = Registry::Get().GetComponent<Component::CollisionBox>(boss);
	bossCollisionBox.Enabled = true;
	Component::SpriteRenderer& bossMaterial = Registry::Get().GetComponent<Component::SpriteRenderer>(boss);
	Component::Animation& bossAnimation = Registry::Get().GetComponent<Component::Animation>(boss);
	bossTransform.scale = { 160.f, 160.f, 0.f };
	bossTransform.position.x = 63.f * tranquilizerTransform.scale.x;
	bossTransform.position.y = 54.f * tranquilizerTransform.scale.y;
	bossMaterial.texture = "res/textures/Boss.png";
	bossMaterial.coords = { 0.f, 0.f };
	bossMaterial.spriteSize = { 160.f, 160.f };

	MyComponent::BossBehaviour& bossBehaviour = Registry::Get().GetComponent<MyComponent::BossBehaviour>(boss);
	bossBehaviour.yellowGhosts = yellowEnemy;

	// Yellow ghosts.
	for (uint32_t i = 0; i < 150; i++)
	{
		Component::Transform& transform = Registry::Get().GetComponent<Component::Transform>(yellowEnemy[i]);
		transform.scale = { 30.f, 30.f, 0.f };
		transform.position.x = 63.f * transform.scale.x;
		transform.position.y = 54.f * transform.scale.y;
		transform.Static = false;
		transform.Enabled = true;
		Registry::Get().GetComponent<Component::CollisionBox>(yellowEnemy[i]).Trigger = true;
		Component::SpriteRenderer& enemyMaterial = Registry::Get().GetComponent<Component::SpriteRenderer>(yellowEnemy[i]);
		Component::Animation& enemyAnimation = Registry::Get().GetComponent<Component::Animation>(yellowEnemy[i]);

		enemyMaterial.Enabled = true;
		enemyMaterial.texture = "res/textures/GhostSheet.png";
		enemyMaterial.coords = { 0.f, 0.f };
		enemyMaterial.spriteSize = { 30.f, 30.f };

		enemyAnimation.animations.push_back({ "RegularAnim", &enemyMaterial, { 0.0f, 1.0f }, 0.0, 0.5, 1, 1, true, true });
		enemyAnimation.animations.push_back({ "StunnedAnim", &enemyMaterial, { 0.0f, 0.0f }, 0.0, 0.5, 1, 1, true, false });
	}

	// Player.
	Component::Transform& playerTransform = Registry::Get().GetComponent<Component::Transform>(player);
	Component::SpriteRenderer& playerMaterial = Registry::Get().GetComponent<Component::SpriteRenderer>(player);

	playerTransform.scale.x = 29.0f;
	playerTransform.scale.y = 29.0f;
	playerTransform.position.x = 49.f * playerTransform.scale.x;
	playerTransform.position.y = 2.f * playerTransform.scale.y;
	playerTransform.Static = false;
	playerTransform.Enabled = true;

	Registry::Get().GetComponent<Component::CollisionBox>(player).Enabled = true;

	playerMaterial.Enabled = true;
	playerMaterial.texture = "res/textures/HeroSheet.png";
	playerMaterial.spriteSize = { 30.f, 30.f };
	playerMaterial.coords = { 0.f, 0.f };

	Registry::Get().GetComponent<Component::Animation>(player).Enabled = true;
	Registry::Get().GetComponent<MyComponent::PlayerHandler>(player).Enabled = true;
}

void Level1::HandleEntityTiles()
{
	int rows = SceneManager::Get().m_WorldSize.x;
	int collumns = SceneManager::Get().m_WorldSize.y;

	int wallIndex = 0;
	int floorIndex = 0;
	int lavaIndex = 0;
	int doorWayIndex = 0;

	for (int i = 0; i < m_LevelTiles.size(); i++)
	{
		for (int j = 0; j < m_LevelTiles[i].size(); j++)
		{
			if (m_LevelTiles[i][j] == 2)
			{
				Component::Transform& tr = Registry::Get().GetComponent<Component::Transform>(lava[lavaIndex]);
				Component::SpriteRenderer& sp = Registry::Get().GetComponent<Component::SpriteRenderer>(lava[lavaIndex]);

				tr.scale = { SceneManager::Get().m_TileSize, SceneManager::Get().m_TileSize, 0.f };
				tr.position.x = j * tr.scale.x;
				int f = glm::abs(i - ((int)m_LevelTiles.size() - 1));
				tr.position.y = f * tr.scale.y;

				Registry::Get().GetComponent<Component::CollisionBox>(lava[lavaIndex]).Enabled = true;
				Registry::Get().GetComponent<Component::CollisionBox>(lava[lavaIndex]).Trigger = true;
				tr.Enabled = true;
				Registry::Get().GetComponent<MyComponent::Lava>(lava[lavaIndex]).Enabled = true;

				sp.Enabled = true;
				sp.color = { 1.f, 1.f, 1.f, 1.f };
				sp.texture = "res/textures/LavaSheet.png";
				sp.spriteSize = { SceneManager::Get().m_TileSize, SceneManager::Get().m_TileSize };
				sp.coords = { 0.f, 0.f };

				Registry::Get().GetComponent<Component::Animation>(lava[lavaIndex]).Enabled = true;
				Registry::Get().GetComponent<Component::Animation>(lava[lavaIndex]).animations.push_back({ "RegularAnim", &sp, { 0.0f, 0.0f }, 0.0, 0.5, 1, 1, true, true });

				lavaIndex++;
			}
			else if (m_LevelTiles[i][j] == 25)
			{
				Component::Transform& tr = Registry::Get().GetComponent<Component::Transform>(floor[floorIndex]);
				tr.scale = { SceneManager::Get().m_TileSize, SceneManager::Get().m_TileSize, 0.f };
				tr.position.x = j * tr.scale.x;
				int f = glm::abs(i - ((int)m_LevelTiles.size() - 1));
				tr.position.y = f * tr.scale.y;

				Registry::Get().GetComponent<Component::Transform>(floor[floorIndex]).Enabled = true;

				Registry::Get().GetComponent<Component::SpriteRenderer>(floor[floorIndex]).Enabled = true;
				Registry::Get().GetComponent<Component::SpriteRenderer>(floor[floorIndex]).color = { 1.f, 1.f, 1.f, 1.f };
				Registry::Get().GetComponent<Component::SpriteRenderer>(floor[floorIndex]).texture = "res/textures/Zelda-II-Parapa-Palace-Tileset-Enigma.png";
				Registry::Get().GetComponent<Component::SpriteRenderer>(floor[floorIndex]).spriteSize = { SceneManager::Get().m_TileSize, SceneManager::Get().m_TileSize };
				Registry::Get().GetComponent<Component::SpriteRenderer>(floor[floorIndex]).coords = { 1.f, 6.f };

				floorIndex++;
			}
			else if (m_LevelTiles[i][j] == 90)
			{
				Component::Transform& tr = Registry::Get().GetComponent<Component::Transform>(wall[wallIndex]);
				tr.scale = { SceneManager::Get().m_TileSize, SceneManager::Get().m_TileSize, 0.f };
				tr.position.x = j * tr.scale.x;
				int f = glm::abs(i - ((int)m_LevelTiles.size() - 1));
				tr.position.y = f * tr.scale.y;

				Registry::Get().GetComponent<Component::Transform>(wall[wallIndex]).Enabled = true;
				Registry::Get().GetComponent<Component::CollisionBox>(wall[wallIndex]).Enabled = true;

				Registry::Get().GetComponent<Component::SpriteRenderer>(wall[wallIndex]).Enabled = true;
				Registry::Get().GetComponent<Component::SpriteRenderer>(wall[wallIndex]).texture = "res/textures/Zelda-II-Parapa-Palace-Tileset-Enigma.png";
				Registry::Get().GetComponent<Component::SpriteRenderer>(wall[wallIndex]).spriteSize = { SceneManager::Get().m_TileSize, SceneManager::Get().m_TileSize };
				Registry::Get().GetComponent<Component::SpriteRenderer>(wall[wallIndex]).coords = { 0.f, 0.f };
				Registry::Get().GetComponent<Component::Shadow>(wall[wallIndex]).Enabled = true;

				wallIndex++;
			}
			else if (m_LevelTiles[i][j] == 46)
			{
				Component::Transform& tr = Registry::Get().GetComponent<Component::Transform>(doorWay[doorWayIndex]);
				tr.scale = { SceneManager::Get().m_TileSize, SceneManager::Get().m_TileSize, 0.f };
				tr.position.x = j * tr.scale.x;
				int f = glm::abs(i - ((int)m_LevelTiles.size() - 1));
				tr.position.y = f * tr.scale.y;

				Registry::Get().GetComponent<Component::Transform>(doorWay[doorWayIndex]).Enabled = true;

				Registry::Get().GetComponent<Component::SpriteRenderer>(doorWay[doorWayIndex]).Enabled = true;
				Registry::Get().GetComponent<Component::SpriteRenderer>(doorWay[doorWayIndex]).texture = "res/textures/Zelda-II-Parapa-Palace-Tileset-Enigma.png";
				Registry::Get().GetComponent<Component::SpriteRenderer>(doorWay[doorWayIndex]).spriteSize = { SceneManager::Get().m_TileSize, SceneManager::Get().m_TileSize };
				Registry::Get().GetComponent<Component::SpriteRenderer>(doorWay[doorWayIndex]).coords = { 6.f, 5.f };

				doorWayIndex++;
			}
		}
	}
}

void Level1::HandleEntities()
{
	int rows = SceneManager::Get().m_WorldSize.x;
	int collumns = SceneManager::Get().m_WorldSize.y;

	int keyIndex = 0;
	int doorIndex = 0;
	int enemyIndex = 0;
	int movingEnemyIndex = 0;
	int patrolEnemyIndex = 0;
	int territoryIndex = 0;
	int collectibleIndex = 0;

	for (int i = 0; i < m_EntityTiles.size(); i++)
	{
		for (int j = 0; j < m_EntityTiles[i].size(); j++)
		{
			// Enemies.
			if (m_EntityTiles[i][j] == 40)
			{
				Component::Transform& enemyTransform = Registry::Get().GetComponent<Component::Transform>(enemy[enemyIndex]);
				Component::SpriteRenderer& enemyMaterial = Registry::Get().GetComponent<Component::SpriteRenderer>(enemy[enemyIndex]);
				Component::CollisionBox& enemyCollisionBox = Registry::Get().GetComponent<Component::CollisionBox>(enemy[enemyIndex]);
				Component::Animation& enemyAnimation = Registry::Get().GetComponent<Component::Animation>(enemy[enemyIndex]);

				enemyTransform.scale = { SceneManager::Get().m_TileSize, SceneManager::Get().m_TileSize, 0.f };
				enemyTransform.position.x = j * enemyTransform.scale.x;
				int f = glm::abs(i - ((int)m_EntityTiles.size() - 1));
				enemyTransform.position.y = f * enemyTransform.scale.y;

				enemyTransform.Static = false;
				enemyTransform.Enabled = true;

				Registry::Get().GetComponent<MyComponent::GhostBehaviour>(enemy[enemyIndex]).basePosition = enemyTransform.position;

				Registry::Get().GetComponent<MyComponent::GhostBehaviour>(enemy[enemyIndex]).Enabled = true;
				Registry::Get().GetComponent<MyComponent::GhostStunner>(enemy[enemyIndex]).Enabled = true;
				enemyTransform.Static = false;
				enemyCollisionBox.Trigger = true;

				enemyMaterial.Enabled = true;
				enemyMaterial.texture = "res/textures/GhostSheet.png";
				enemyMaterial.coords = { 0.f, 0.f };
				enemyMaterial.spriteSize = { 30.f, 30.f };

				enemyAnimation.animations.push_back({ "RegularAnim", &enemyMaterial, { 0.0f, 4.0f }, 0.0, 0.5, 1, 1, true, true });
				enemyAnimation.animations.push_back({ "StunnedAnim", &enemyMaterial, { 0.0f, 3.0f }, 0.0, 0.5, 1, 1, true, false });

				if (enemyIndex >= 0 && enemyIndex <= 39)
				{
					Registry::Get().GetComponent<MyComponent::GhostBehaviour>(enemy[enemyIndex]).territory = &territory[0];
				}
				else if (enemyIndex >= 40 && enemyIndex <= 59)
				{
					Registry::Get().GetComponent<MyComponent::GhostBehaviour>(enemy[enemyIndex]).territory = &territory[1];
				}
				else if (enemyIndex >= 60 && enemyIndex <= 74)
				{
					Registry::Get().GetComponent<MyComponent::GhostBehaviour>(enemy[enemyIndex]).territory = &territory[2];
				}
				else if (enemyIndex >= 75 && enemyIndex <= 78)
				{
					Registry::Get().GetComponent<MyComponent::GhostBehaviour>(enemy[enemyIndex]).territory = &territory[3];
				}
				else if (enemyIndex == 79 || enemyIndex == 81)
				{
					Registry::Get().GetComponent<MyComponent::GhostBehaviour>(enemy[enemyIndex]).territory = &territory[5];
				}
				else if (enemyIndex == 80)
				{
					Registry::Get().GetComponent<MyComponent::GhostBehaviour>(enemy[enemyIndex]).territory = &territory[4];
				}

				enemyIndex++;
			}
			// Moving Enemies.
			if (m_EntityTiles[i][j] == 34)
			{
				Component::Transform& enemyTransform = Registry::Get().GetComponent<Component::Transform>(movingEnemy[movingEnemyIndex]);
				Component::SpriteRenderer& enemyMaterial = Registry::Get().GetComponent<Component::SpriteRenderer>(movingEnemy[movingEnemyIndex]);
				Component::CollisionBox& enemyCollisionBox = Registry::Get().GetComponent<Component::CollisionBox>(movingEnemy[movingEnemyIndex]);
				Component::Animation& enemyAnimation = Registry::Get().GetComponent<Component::Animation>(movingEnemy[movingEnemyIndex]);

				enemyTransform.scale = { SceneManager::Get().m_TileSize, SceneManager::Get().m_TileSize, 0.f };
				enemyTransform.position.x = j * enemyTransform.scale.x;
				int f = glm::abs(i - ((int)m_EntityTiles.size() - 1));
				enemyTransform.position.y = f * enemyTransform.scale.y;

				enemyTransform.Static = false;
				enemyTransform.Enabled = true;

				Registry::Get().GetComponent<MyComponent::MovingGhostBehaviour>(movingEnemy[movingEnemyIndex]).Enabled = true;

				enemyTransform.Static = false;
				enemyCollisionBox.Trigger = true;

				enemyMaterial.Enabled = true;
				enemyMaterial.texture = "res/textures/GhostSheet.png";
				enemyMaterial.coords = { 0.f, 2.f };
				enemyMaterial.spriteSize = { 30.f, 30.f };

				enemyAnimation.animations.push_back({ "RegularAnim", &enemyMaterial, { 0.0f, 2.0f }, 0.0, 0.5, 1, 1, true, true });

				movingEnemyIndex++;
			}
			// Patrol Enemies.
			if (m_EntityTiles[i][j] == 5)
			{
				Component::Transform& enemyTransform = Registry::Get().GetComponent<Component::Transform>(patrolEnemy[patrolEnemyIndex]);
				Component::SpriteRenderer& enemyMaterial = Registry::Get().GetComponent<Component::SpriteRenderer>(patrolEnemy[patrolEnemyIndex]);
				Component::CollisionBox& enemyCollisionBox = Registry::Get().GetComponent<Component::CollisionBox>(patrolEnemy[patrolEnemyIndex]);
				Component::Animation& enemyAnimation = Registry::Get().GetComponent<Component::Animation>(patrolEnemy[patrolEnemyIndex]);

				enemyTransform.scale = { SceneManager::Get().m_TileSize, SceneManager::Get().m_TileSize, 0.f };
				enemyTransform.position.x = j * enemyTransform.scale.x;
				int f = glm::abs(i - ((int)m_EntityTiles.size() - 1));
				enemyTransform.position.y = f * enemyTransform.scale.y;

				enemyTransform.Static = false;
				enemyTransform.Enabled = true;

				Registry::Get().GetComponent<MyComponent::PatrolGhostBehaviour>(patrolEnemy[patrolEnemyIndex]).Enabled = true;

				enemyTransform.Static = false;
				enemyCollisionBox.Trigger = true;

				enemyMaterial.Enabled = true;
				enemyMaterial.texture = "res/textures/GhostSheet.png";
				enemyMaterial.coords = { 0.f, 2.f };
				enemyMaterial.spriteSize = { 30.f, 30.f };

				enemyAnimation.animations.push_back({ "RegularAnim", &enemyMaterial, { 0.0f, 2.0f }, 0.0, 0.5, 1, 1, true, true });

				patrolEnemyIndex++;
			}
			// Collectibles.
			else if (m_EntityTiles[i][j] == 19)
			{
				Component::Transform& collectibleTransform = Registry::Get().GetComponent<Component::Transform>(collectible[collectibleIndex]);
				Component::SpriteRenderer& collectibleMaterial = Registry::Get().GetComponent<Component::SpriteRenderer>(collectible[collectibleIndex]);
				Component::CollisionBox& collectibleCollisionBox = Registry::Get().GetComponent<Component::CollisionBox>(collectible[collectibleIndex]);

				collectibleTransform.scale = { SceneManager::Get().m_TileSize, SceneManager::Get().m_TileSize, 0.f };
				collectibleTransform.position.x = j * collectibleTransform.scale.x;
				int f = glm::abs(i - ((int)m_EntityTiles.size() - 1));
				collectibleTransform.position.y = f * collectibleTransform.scale.y;

				collectibleTransform.Enabled = true;
				collectibleCollisionBox.Enabled = true;
				collectibleMaterial.Enabled = true;
				Registry::Get().GetComponent<MyComponent::Collectible>(collectible[collectibleIndex]).Enabled = true;

				collectibleCollisionBox.Trigger = true;
				collectibleMaterial.texture = "res/textures/Coin.png";

				collectibleIndex++;
			}
			// GhostTeritories.
			else if (m_EntityTiles[i][j] == 23)
			{
				Component::Transform& territoryTransform = Registry::Get().GetComponent<Component::Transform>(territory[territoryIndex]);
				Component::SpriteRenderer& territoryMaterial = Registry::Get().GetComponent<Component::SpriteRenderer>(territory[territoryIndex]);
				Component::CollisionBox& territoryCollisionBox = Registry::Get().GetComponent<Component::CollisionBox>(territory[territoryIndex]);

				territoryTransform.position.x = j * SceneManager::Get().m_TileSize;
				int f = glm::abs(i - ((int)m_EntityTiles.size() - 1));
				territoryTransform.position.y = f * SceneManager::Get().m_TileSize;

				if (territoryIndex == 0)
				{
					territoryTransform.scale = { SceneManager::Get().m_TileSize * 8.f, SceneManager::Get().m_TileSize * 40.f, 0.f };
				}
				if (territoryIndex == 1)
				{
					territoryTransform.scale = { SceneManager::Get().m_TileSize * 24.f, SceneManager::Get().m_TileSize * 9.f, 0.f };
				}
				else if (territoryIndex == 2)
				{
					territoryTransform.scale = { SceneManager::Get().m_TileSize * 20.f, SceneManager::Get().m_TileSize * 12.5f, 0.f };
				}
				else if (territoryIndex == 3)
				{
					territoryTransform.scale = { SceneManager::Get().m_TileSize * 18.f, SceneManager::Get().m_TileSize * 40.f, 0.f };
				}
				else if (territoryIndex == 4)
				{
					territoryTransform.scale = { SceneManager::Get().m_TileSize * 21.f, SceneManager::Get().m_TileSize * 17.f, 0.f };
				}
				else if (territoryIndex == 5)
				{
					territoryTransform.scale = { SceneManager::Get().m_TileSize * 27.f, SceneManager::Get().m_TileSize * 5.f, 0.f };
				}

				territoryTransform.Enabled = true;
				territoryCollisionBox.Enabled = true;
				//territoryMaterial.Enabled = true;
				territoryCollisionBox.Trigger = true;

				territoryIndex++;
			}
			// Door.
			else if (m_EntityTiles[i][j] == 47)
			{
				Component::Transform& doorTransform = Registry::Get().GetComponent<Component::Transform>(door[doorIndex]);
				Component::SpriteRenderer& doorMaterial = Registry::Get().GetComponent<Component::SpriteRenderer>(door[doorIndex]);
				Component::CollisionBox& doorCollisionBox = Registry::Get().GetComponent<Component::CollisionBox>(door[doorIndex]);
				Component::Shadow& doorShadow = Registry::Get().GetComponent<Component::Shadow>(door[doorIndex]);
				Registry::Get().GetComponent<MyComponent::Door>(door[doorIndex]).Enabled = true;

				doorTransform.position.x = j * SceneManager::Get().m_TileSize;
				int f = glm::abs(i - ((int)m_EntityTiles.size() - 1));
				doorTransform.position.y = f * SceneManager::Get().m_TileSize;

				if (doorIndex == 0)
				{
					doorTransform.scale = { SceneManager::Get().m_TileSize * 3.f, SceneManager::Get().m_TileSize * 1.f, 0.f };
				}
				else if (doorIndex == 1)
				{
					doorTransform.scale = { SceneManager::Get().m_TileSize * 1.f, SceneManager::Get().m_TileSize * 3.f, 0.f };
				}
				else if (doorIndex == 2)
				{
					doorTransform.scale = { SceneManager::Get().m_TileSize * 7.f, SceneManager::Get().m_TileSize * 1.f, 0.f };
				}

				doorTransform.Enabled = true;
				doorCollisionBox.Enabled = true;
				doorMaterial.Enabled = true;
				doorShadow.Enabled = true;

				doorIndex++;
			}
			// Key.
			else if (m_EntityTiles[i][j] == 33)
			{
				Component::Transform& keyTransform = Registry::Get().GetComponent<Component::Transform>(key[keyIndex]);
				Component::SpriteRenderer& keyMaterial = Registry::Get().GetComponent<Component::SpriteRenderer>(key[keyIndex]);
				Component::CollisionBox& keyCollisionBox = Registry::Get().GetComponent<Component::CollisionBox>(key[keyIndex]);

				keyTransform.scale = { SceneManager::Get().m_TileSize, SceneManager::Get().m_TileSize, 0.f };
				keyTransform.position.x = j * keyTransform.scale.x;
				int f = glm::abs(i - ((int)m_EntityTiles.size() - 1));
				keyTransform.position.y = f * keyTransform.scale.y;

				keyTransform.Enabled = true;
				keyCollisionBox.Enabled = true;
				keyMaterial.Enabled = true;

				keyMaterial.texture = "res/textures/Key.png";

				keyIndex++;
			}
		}
	}
}
