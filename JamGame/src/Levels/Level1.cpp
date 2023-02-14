#include "Level1.h"

using namespace HBL;

void Level1::OnAttach()
{
	// Enroll entities.
	for (uint32_t i = 0; i < 1000; i++)
		Registry::Get().EnrollEntity(wall[i]);

	for (uint32_t i = 0; i < 12000; i++)
		Registry::Get().EnrollEntity(floor[i]);

	for (uint32_t i = 0; i < 20; i++)
		Registry::Get().EnrollEntity(territory[i]);

	for (uint32_t i = 0; i < 200; i++)
		Registry::Get().EnrollEntity(enemy[i]);

	for (uint32_t i = 0; i < 200; i++)
		Registry::Get().EnrollEntity(collectible[i]);

	Registry::Get().EnrollEntity(player, "Player");
	Registry::Get().EnrollEntity(tranquilizer, "Tranquilizer");
	Registry::Get().EnrollEntity(tranquilizerWave, "TranquilizerWave");
	Registry::Get().EnrollEntity(tranquilizerUI, "TranquilizerUI");
	Registry::Get().EnrollEntity(camera, "Camera");

	// Add components.
	for (uint32_t i = 0; i < 1000; i++)
	{
		Registry::Get().AddComponent<Component::CollisionBox>(wall[i]);
		Registry::Get().AddComponent<Component::SpriteRenderer>(wall[i]);
		Registry::Get().AddComponent<Component::Shadow>(wall[i]);
	}

	for (uint32_t i = 0; i < 12000; i++)
	{
		Registry::Get().AddComponent<Component::SpriteRenderer>(floor[i]);
	}

	for (uint32_t i = 0; i < 20; i++)
	{
		Registry::Get().AddComponent<Component::SpriteRenderer>(territory[i]);
		Registry::Get().AddComponent<Component::CollisionBox>(territory[i]);
	}

	for (uint32_t i = 0; i < 200; i++)
	{
		Registry::Get().AddComponent<Component::SpriteRenderer>(enemy[i]);
		Registry::Get().AddComponent<Component::CollisionBox>(enemy[i]);
		Registry::Get().AddComponent<MyComponent::GhostBehaviour>(enemy[i]);
		Registry::Get().AddComponent<MyComponent::GhostStunner>(enemy[i]);
	}

	for (uint32_t i = 0; i < 200; i++)
	{
		Registry::Get().AddComponent<Component::SpriteRenderer>(collectible[i]);
		Registry::Get().AddComponent<Component::CollisionBox>(collectible[i]);
		Registry::Get().AddComponent<MyComponent::Collectible>(collectible[i]);
	}

	Registry::Get().AddComponent<Component::Script>(player);
	Registry::Get().AddComponent<Component::SpriteRenderer>(player);
	Registry::Get().AddComponent<Component::CollisionBox>(player);
	Registry::Get().AddComponent<Component::Animation>(player);
	Registry::Get().AddComponent<MyComponent::PlayerDirection>(player);

	Registry::Get().AddComponent<Component::Camera>(camera);

	Registry::Get().AddComponent<Component::SpriteRenderer>(tranquilizer);
	Registry::Get().AddComponent<Component::CollisionBox>(tranquilizer);

	Registry::Get().AddComponent<Component::SpriteRenderer>(tranquilizerWave);
	Registry::Get().AddComponent<Component::CollisionBox>(tranquilizerWave);
	Registry::Get().AddComponent<Component::Script>(tranquilizerWave);

	Registry::Get().AddComponent<Component::Text>(tranquilizerUI);

	// Initialize components.
	Registry::Get().GetComponent<Component::Script>(tranquilizerWave).script.push_back(new TranquilizerWaveScript());
	Registry::Get().GetComponent<Component::Script>(player).script.push_back(new PlayerScript());

	Registry::Get().GetComponent<Component::Transform>(player).Static = false;

	Registry::Get().GetComponent<Component::Transform>(tranquilizer).Static = false;
	Registry::Get().GetComponent<Component::CollisionBox>(tranquilizer).Trigger = true;

	Registry::Get().GetComponent<Component::Transform>(tranquilizerWave).Static = false;
	Registry::Get().GetComponent<Component::CollisionBox>(tranquilizerWave).Trigger = true;

	Registry::Get().GetComponent<Component::Text>(tranquilizerUI).text = "100";
	Registry::Get().GetComponent<Component::Text>(tranquilizerUI).color = { 1.0f, 0.8f, 0.5f, 1.0f};
	Registry::Get().GetComponent<Component::Text>(tranquilizerUI).screenSpace = true;
	Registry::Get().GetComponent<Component::Text>(tranquilizerUI).sreenSpaceOffset = { Systems::Window.GetWidth() - 125.f, Systems::Window.GetHeight() - 50.f };

	Registry::Get().GetComponent<Component::Camera>(camera).projection = glm::ortho(
		0.0f, Systems::Window.GetWidth(),
		0.0f, Systems::Window.GetHeight(),
		-1.0f, 1.0f);

	for (uint32_t i = 0; i < 1000; i++)
	{
		Registry::Get().GetComponent<Component::Transform>(wall[i]).Static = true;
		Registry::Get().GetComponent<Component::Transform>(wall[i]).Enabled = false;
		Registry::Get().GetComponent<Component::CollisionBox>(wall[i]).Enabled = false;
		Registry::Get().GetComponent<Component::SpriteRenderer>(wall[i]).Enabled = false;
		Registry::Get().GetComponent<Component::Shadow>(wall[i]).Enabled = false;
		Registry::Get().GetComponent<Component::Shadow>(wall[i]).source = &player;
	}

	for (uint32_t i = 0; i < 12000; i++)
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

	for (uint32_t i = 0; i < 200; i++)
	{
		Registry::Get().GetComponent<Component::Transform>(enemy[i]).Static = true;
		Registry::Get().GetComponent<Component::Transform>(enemy[i]).Enabled = false;
		Registry::Get().GetComponent<Component::SpriteRenderer>(enemy[i]).Enabled = false;
		Registry::Get().GetComponent<MyComponent::GhostBehaviour>(enemy[i]).Enabled = false;
		Registry::Get().GetComponent<MyComponent::GhostStunner>(enemy[i]).Enabled = false;
	}

	for (uint32_t i = 0; i < 200; i++)
	{
		Registry::Get().GetComponent<Component::Transform>(collectible[i]).Static = true;
		Registry::Get().GetComponent<Component::Transform>(collectible[i]).Enabled = false;
		Registry::Get().GetComponent<Component::SpriteRenderer>(collectible[i]).Enabled = false;
		Registry::Get().GetComponent<MyComponent::Collectible>(collectible[i]).Enabled = false;
	}

	InitializeLevel("res/levels/testMap_Tile Layer 1.csv", "res/levels/testMap_Tile Layer 2.csv");
}

void Level1::OnCreate()
{
}

void Level1::OnDetach()
{
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

	// Tranquilizer
	Component::Transform& tranquilizerTransform = Registry::Get().GetComponent<Component::Transform>(tranquilizer);
	Component::SpriteRenderer& tranquilizerMaterial = Registry::Get().GetComponent<Component::SpriteRenderer>(tranquilizer);

	tranquilizerTransform.scale.x = 30.0f;
	tranquilizerTransform.scale.y = 30.0f;
	tranquilizerTransform.position.x = 55.f * tranquilizerTransform.scale.x;
	tranquilizerTransform.position.y = 5.f * tranquilizerTransform.scale.y;

	// Update the position of the player last
	Component::Transform& playerTransform = Registry::Get().GetComponent<Component::Transform>(player);
	Component::SpriteRenderer& playerMaterial = Registry::Get().GetComponent<Component::SpriteRenderer>(player);

	playerTransform.scale.x = 29.0f;
	playerTransform.scale.y = 29.0f;
	playerTransform.position.x = 49.f * playerTransform.scale.x;
	playerTransform.position.y = 2.f * playerTransform.scale.y;
	playerTransform.Static = false;
	playerTransform.Enabled = true;

	Registry::Get().GetComponent<Component::CollisionBox>(player).Enabled = true;
	Registry::Get().GetComponent<Component::Script>(player).Enabled = true;

	playerMaterial.Enabled = true;
	playerMaterial.texture = "res/textures/hero-1.png";

	Registry::Get().GetComponent<Component::Animation>(player).Enabled = true;
}

void Level1::HandleEntityTiles()
{
	int rows = SceneManager::Get().m_WorldSize.x;
	int collumns = SceneManager::Get().m_WorldSize.y;

	int wallIndex = 0;
	int floorIndex = 0;

	for (int i = 0; i < m_LevelTiles.size(); i++)
	{
		for (int j = 0; j < m_LevelTiles[i].size(); j++)
		{
			if (m_LevelTiles[i][j] == 25)
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
				float x = glm::floor((100 - m_LevelTiles[i][j]) % 10);
				float y = glm::floor((100 - m_LevelTiles[i][j]) / 10);
				Registry::Get().GetComponent<Component::SpriteRenderer>(floor[floorIndex]).coords = { 5.f, 7.f };

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
				float x = glm::floor((100 - m_LevelTiles[i][j]) % 10);
				float y = glm::floor((100 - m_LevelTiles[i][j]) / 10);
				Registry::Get().GetComponent<Component::SpriteRenderer>(floor[floorIndex]).coords = { 0.f, 0.f };
				//Registry::Get().GetComponent<Component::Shadow>(wall[wallIndex]).Enabled = true;

				wallIndex++;
			}
		}
	}
}

void Level1::HandleEntities()
{
	int rows = SceneManager::Get().m_WorldSize.x;
	int collumns = SceneManager::Get().m_WorldSize.y;

	int enemyIndex = 0;
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
				enemyMaterial.texture = "res/textures/enemy.png";

				if (enemyIndex >= 0 && enemyIndex <= 6)
				{
					Registry::Get().GetComponent<MyComponent::GhostBehaviour>(enemy[enemyIndex]).territory = &territory[0];
				}
				else if (enemyIndex >= 7 && enemyIndex <= 10)
				{
					Registry::Get().GetComponent<MyComponent::GhostBehaviour>(enemy[enemyIndex]).territory = &territory[1];
				}
				else if (enemyIndex == 11 || enemyIndex == 13)
				{
					Registry::Get().GetComponent<MyComponent::GhostBehaviour>(enemy[enemyIndex]).territory = &territory[3];
				}
				else if (enemyIndex == 12)
				{
					Registry::Get().GetComponent<MyComponent::GhostBehaviour>(enemy[enemyIndex]).territory = &territory[2];
				}

				enemyIndex++;
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
				collectibleMaterial.texture = "res/textures/coinA.png";

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
					territoryTransform.scale = { SceneManager::Get().m_TileSize * 13.f, SceneManager::Get().m_TileSize * 13.f, 0.f };

					territoryTransform.Enabled = true;
					territoryCollisionBox.Enabled = true;
					territoryMaterial.Enabled = true;
					territoryCollisionBox.Trigger = true;
				}
				else if (territoryIndex == 1)
				{
					territoryTransform.scale = { SceneManager::Get().m_TileSize * 20.f, SceneManager::Get().m_TileSize * 40.f, 0.f };

					territoryTransform.Enabled = true;
					territoryCollisionBox.Enabled = true;
					territoryMaterial.Enabled = true;
					territoryCollisionBox.Trigger = true;
				}
				else if (territoryIndex == 2)
				{
					territoryTransform.scale = { SceneManager::Get().m_TileSize * 21.f, SceneManager::Get().m_TileSize * 17.f, 0.f };

					territoryTransform.Enabled = true;
					territoryCollisionBox.Enabled = true;
					territoryMaterial.Enabled = true;
					territoryCollisionBox.Trigger = true;
				}
				else if (territoryIndex == 3)
				{
					territoryTransform.scale = { SceneManager::Get().m_TileSize * 27.f, SceneManager::Get().m_TileSize * 5.f, 0.f };

					territoryTransform.Enabled = true;
					territoryCollisionBox.Enabled = true;
					//territoryMaterial.Enabled = true;
					territoryCollisionBox.Trigger = true;
				}

				territoryIndex++;
			}
		}
	}
}
