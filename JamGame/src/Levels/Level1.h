#pragma once

#include "Humble.h"
#include "..\MyComponents.h"

#include "..\Scripts\PlayerScript.h"
#include "..\Scripts\EnemyScript.h"

namespace HBL 
{
	class Level1 final : public IScene
	{
	public:
		virtual void OnAttach() override;
		virtual void OnCreate() override;
		virtual void OnDetach() override;

		void CSVImporter(const std::string& levelPath);

	private:
		HBL::IEntity background;
		HBL::IEntity player;
		HBL::IEntity enemy;
		HBL::IEntity wall[1000];
		HBL::IEntity floor[4000];
		HBL::IEntity camera;
	};
}