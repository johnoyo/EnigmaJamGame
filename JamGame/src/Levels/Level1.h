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
	HBL::IEntity key;
	HBL::IEntity door;
	HBL::IEntity tranquilizerWave;

	HBL::IEntity wall[2000];
	HBL::IEntity lava[500];
	HBL::IEntity floor[8000];
	HBL::IEntity enemy[200];
	HBL::IEntity collectible[200];
	HBL::IEntity territory[20];

	std::vector<std::vector<int>> m_LevelTiles;
	std::vector<std::vector<int>> m_EntityTiles;
};