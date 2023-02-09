#pragma once

#include "Humble.h"

using namespace HBL;

class EnemyScript final : public IScript
{
public:
	EnemyScript() {}
	~EnemyScript() {}

	IEntity player;
	IEntity enemy;

	float XPos = 0.f;
	float YPos = 0.f;

	virtual void OnCreate() override 
	{
		player = (Registry::Get().FindEntityWithTag("Player"));
		enemy = (Registry::Get().FindEntityWithTag("Enemy"));

		Registry::Get().GetComponent<Component::SpriteRenderer>(enemy).texture = "res/textures/enemy.png";
	}

	virtual void OnUpdate(float dt) override 
	{
		/*Component::Transform& eTr = Registry::Get().GetComponent<Component::Transform>(enemy);
		Component::Transform& pTr = Registry::Get().GetComponent<Component::Transform>(player);

		float xDistance = pTr.position.x - eTr.position.x;
		float yDistance = pTr.position.y - eTr.position.y;

		float hypotenuse = sqrt((xDistance * xDistance) + (yDistance * yDistance));

		if (hypotenuse < 400 && hypotenuse > 20)
		{
			eTr.position.x += dt * 100 * (xDistance / hypotenuse);
			eTr.position.y += dt * 100 * (yDistance / hypotenuse);
		}*/
	}
};
