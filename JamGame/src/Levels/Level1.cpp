#include "Level1.h"

using namespace HBL;

void Level1::OnAttach()
{
	// Enroll entities.
	for (uint32_t i = 0; i < 1000; i++)
		Registry::Get().EnrollEntity(wall[i]);

	for (uint32_t i = 0; i < 4000; i++)
		Registry::Get().EnrollEntity(floor[i]);

	Registry::Get().EnrollEntity(player, "Player");
	Registry::Get().EnrollEntity(enemy, "Enemy");
	Registry::Get().EnrollEntity(tranquilizer, "Tranquilizer");
	Registry::Get().EnrollEntity(tranquilizerWave, "TranquilizerWave");
	Registry::Get().EnrollEntity(camera, "Camera");

	// Add components.
	for (uint32_t i = 0; i < 1000; i++)
	{
		Registry::Get().AddComponent<Component::CollisionBox>(wall[i]);
		Registry::Get().AddComponent<Component::SpriteRenderer>(wall[i]);
		Registry::Get().AddComponent<Component::Shadow>(wall[i]);
	}

	for (uint32_t i = 0; i < 4000; i++)
	{
		Registry::Get().AddComponent<Component::SpriteRenderer>(floor[i]);
	}

	Registry::Get().AddComponent<Component::Script>(player);
	Registry::Get().AddComponent<Component::SpriteRenderer>(player);
	Registry::Get().AddComponent<Component::CollisionBox>(player);
	Registry::Get().AddComponent<Component::Animation>(player);
	Registry::Get().AddComponent<MyComponent::PlayerDirection>(player);

	Registry::Get().AddComponent<Component::Script>(enemy);
	Registry::Get().AddComponent<Component::SpriteRenderer>(enemy);
	Registry::Get().AddComponent<Component::CollisionBox>(enemy);
	Registry::Get().AddComponent<MyComponent::GhostBehaviour>(enemy);
	Registry::Get().AddComponent<MyComponent::GhostStunner>(enemy);

	Registry::Get().AddComponent<Component::Camera>(camera);

	Registry::Get().AddComponent<Component::SpriteRenderer>(tranquilizer);
	Registry::Get().AddComponent<Component::CollisionBox>(tranquilizer);

	Registry::Get().AddComponent<Component::SpriteRenderer>(tranquilizerWave);
	Registry::Get().AddComponent<Component::CollisionBox>(tranquilizerWave);
	Registry::Get().AddComponent<Component::Script>(tranquilizerWave);

	// Initialize components.
	Registry::Get().GetComponent<Component::Script>(tranquilizerWave).script.push_back(new TranquilizerWaveScript());
	Registry::Get().GetComponent<Component::Script>(player).script.push_back(new PlayerScript());
	Registry::Get().GetComponent<Component::Script>(enemy).script.push_back(new EnemyScript());

	Registry::Get().GetComponent<Component::Transform>(player).Static = false;
	Registry::Get().GetComponent<Component::Transform>(enemy).Static = false;
	Registry::Get().GetComponent<Component::CollisionBox>(enemy).Trigger = true;

	Registry::Get().GetComponent<Component::Transform>(tranquilizer).Static = false;
	Registry::Get().GetComponent<Component::CollisionBox>(tranquilizer).Trigger = true;

	Registry::Get().GetComponent<Component::Transform>(tranquilizerWave).Static = false;
	Registry::Get().GetComponent<Component::CollisionBox>(tranquilizerWave).Trigger = true;

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

	for (uint32_t i = 0; i < 4000; i++)
	{
		Registry::Get().GetComponent<Component::Transform>(floor[i]).Static = true;
		Registry::Get().GetComponent<Component::Transform>(floor[i]).Enabled = false;
		Registry::Get().GetComponent<Component::SpriteRenderer>(floor[i]).Enabled = false;
	}

	CSVImporter("res/levels/testMap.csv");
}

void Level1::OnCreate()
{
}

void Level1::OnDetach()
{
}

void Level1::CSVImporter(const std::string& levelPath)
{
	std::fstream fin;
	fin.open(levelPath, std::ios::in);
	std::vector<int> row;
	std::string word, temp;

	std::vector<std::vector<int>> tiles;

	while (fin >> temp) 
	{
		row.clear();

		std::stringstream s(temp);

		while (std::getline(s, word, ',')) 
		{
			row.push_back(stoi(word));
		}

		tiles.push_back(row);
	}

	fin.close();
	
	int rows = tiles.size();
	int collumns = tiles[0].size();

	SceneManager::Get().m_WorldSize = { (float)rows, (float)collumns };
	SceneManager::Get().m_SectorSize = { 4.0f, 4.0f };
	SceneManager::Get().m_TileSize = 30.0f;

	int wallIndex = 0;
	int floorIndex = 0;

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			if (tiles[i][j] == 25)
			{
				Component::Transform& tr = Registry::Get().GetComponent<Component::Transform>(floor[floorIndex]);
				tr.scale = { SceneManager::Get().m_TileSize, SceneManager::Get().m_TileSize, 0.f };
				tr.position.x = j * tr.scale.x;
				int f = glm::abs(i - ((int)tiles.size() - 1));
				tr.position.y = f * tr.scale.y;

				Registry::Get().GetComponent<Component::Transform>(floor[floorIndex]).Enabled = true;

				Registry::Get().GetComponent<Component::SpriteRenderer>(floor[floorIndex]).Enabled = true;
				Registry::Get().GetComponent<Component::SpriteRenderer>(floor[floorIndex]).color = { 1.f, 1.f, 1.f, 1.f };
				Registry::Get().GetComponent<Component::SpriteRenderer>(floor[floorIndex]).texture = "res/textures/Zelda-II-Parapa-Palace-Tileset-Enigma.png";
				Registry::Get().GetComponent<Component::SpriteRenderer>(floor[floorIndex]).spriteSize = { SceneManager::Get().m_TileSize, SceneManager::Get().m_TileSize };
				float x = glm::floor((100 - tiles[i][j]) % 10);
				float y = glm::floor((100 - tiles[i][j]) / 10);
				Registry::Get().GetComponent<Component::SpriteRenderer>(floor[floorIndex]).coords = { 5.f, 7.f };
				
				floorIndex++;
			}
			else if (tiles[i][j] == 90)
			{
				Component::Transform& tr = Registry::Get().GetComponent<Component::Transform>(wall[wallIndex]);
				tr.scale = { SceneManager::Get().m_TileSize, SceneManager::Get().m_TileSize, 0.f };
				tr.position.x = j * tr.scale.x;
				int f = glm::abs(i - ((int)tiles.size() - 1));
				tr.position.y = f * tr.scale.y;

				Registry::Get().GetComponent<Component::Transform>(wall[wallIndex]).Enabled = true;
				Registry::Get().GetComponent<Component::CollisionBox>(wall[wallIndex]).Enabled = true;

				Registry::Get().GetComponent<Component::SpriteRenderer>(wall[wallIndex]).Enabled = true;
				Registry::Get().GetComponent<Component::SpriteRenderer>(wall[wallIndex]).texture = "res/textures/Zelda-II-Parapa-Palace-Tileset-Enigma.png";
				Registry::Get().GetComponent<Component::SpriteRenderer>(wall[wallIndex]).spriteSize = { SceneManager::Get().m_TileSize, SceneManager::Get().m_TileSize };
				float x = glm::floor((100 - tiles[i][j]) % 10);
				float y = glm::floor((100 - tiles[i][j]) / 10);
				Registry::Get().GetComponent<Component::SpriteRenderer>(floor[floorIndex]).coords = { 0.f, 0.f };
				Registry::Get().GetComponent<Component::Shadow>(wall[wallIndex]).Enabled = true;

				wallIndex++;
			}
		}
	}

	// Enemy
	Component::Transform& enemyTransform = Registry::Get().GetComponent<Component::Transform>(enemy);
	Component::SpriteRenderer& enemyMaterial = Registry::Get().GetComponent<Component::SpriteRenderer>(enemy);
	Component::CollisionBox& enemyCollisionBox = Registry::Get().GetComponent<Component::CollisionBox>(enemy);

	enemyTransform.scale.x = 30.0f;
	enemyTransform.scale.y = 30.0f;
	enemyTransform.position.x = 6.f * enemyTransform.scale.x;
	enemyTransform.position.y = 6.f * enemyTransform.scale.y;
	enemyTransform.Static = false;
	enemyTransform.Enabled = true;

	Registry::Get().GetComponent<Component::Script>(enemy).Enabled = true;

	enemyMaterial.Enabled = true;
	enemyMaterial.texture = "res/textures/enemy.png";

	// Tranquilizer
	Component::Transform& tranquilizerTransform = Registry::Get().GetComponent<Component::Transform>(tranquilizer);
	Component::SpriteRenderer& tranquilizerMaterial = Registry::Get().GetComponent<Component::SpriteRenderer>(tranquilizer);

	tranquilizerTransform.scale.x = 30.0f;
	tranquilizerTransform.scale.y = 30.0f;
	tranquilizerTransform.position.x = 35.f * tranquilizerTransform.scale.x;
	tranquilizerTransform.position.y = 5.f * tranquilizerTransform.scale.y;

	// Update the position of the player last
	Component::Transform& playerTransform = Registry::Get().GetComponent<Component::Transform>(player);
	Component::SpriteRenderer& playerMaterial = Registry::Get().GetComponent<Component::SpriteRenderer>(player);

	playerTransform.scale.x = 29.0f;
	playerTransform.scale.y = 29.0f;
	playerTransform.position.x = 29.f * playerTransform.scale.x;
	playerTransform.position.y = 2.f * playerTransform.scale.y;
	playerTransform.Static = false;
	playerTransform.Enabled = true;

	Registry::Get().GetComponent<Component::CollisionBox>(player).Enabled = true;
	Registry::Get().GetComponent<Component::Script>(player).Enabled = true;

	playerMaterial.Enabled = true;
	playerMaterial.texture = "res/textures/hero-1.png";

	Registry::Get().GetComponent<Component::Animation>(player).Enabled = true;
}
