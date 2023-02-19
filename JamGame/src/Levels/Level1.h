#pragma once

#include "Humble.h"
#include "..\MyComponents.h"

#include "..\Scripts\PlayerScript.h"
#include "..\Scripts\EnemyScript.h"

class Level1 final : public HBL::IScene
{
public:
	virtual void OnAttach() override;
	virtual void OnCreate() override;
	virtual void OnDetach() override;

	void CSVImporter(const std::string& levelPath, bool level);
	void InitializeLevel(const std::string& levelPath1, const std::string& levelPath2);
	void HandleEntityTiles();
	void HandleEntities();

private:
	HBL::IEntity player;
	HBL::IEntity camera;
	HBL::IEntity popUpMenu;
	HBL::IEntity tranquilizerWave;
	HBL::IEntity coinsCounter;
	HBL::IEntity boss;

	HBL::IEntity wall[1700];
	HBL::IEntity lava[500];
	HBL::IEntity floor[5500];
	HBL::IEntity enemy[200];
	HBL::IEntity patrolEnemy[6];
	HBL::IEntity movingEnemy[20];
	HBL::IEntity yellowEnemy[150];
	HBL::IEntity collectible[200];
	HBL::IEntity territory[20];
	HBL::IEntity doorWay[20];
	HBL::IEntity door[3];
	HBL::IEntity key[3];

	std::vector<std::vector<int>> m_LevelTiles;
	std::vector<std::vector<int>> m_EntityTiles;
};