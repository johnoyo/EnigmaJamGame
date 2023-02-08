#pragma once

#include "Humble.h"

namespace HBL 
{
	class EnemyScript final : public IScript
	{
	public:
		EnemyScript() {}
		~EnemyScript() {}

		IEntity player;
		IEntity enemy;

		virtual void OnCreate() override 
		{
			player = (Registry::Get().FindEntityWithTag("Player"));
			enemy = (Registry::Get().FindEntityWithTag("Enemy"));

			Registry::Get().GetComponent<Component::SpriteRenderer>(enemy).texture = "res/textures/player_r.png";
		}

		virtual void OnUpdate(float dt) override 
		{
			Registry::Get().GetComponent<Component::Transform>(enemy).position.x -= 30.0f * dt;
		}

	};
}
