#pragma once

namespace MyComponent 
{
	struct PlayerDirection 
	{
		bool Right = false;
		bool Left = false;
		bool Up = false;
		bool Down = true;
		bool Enabled = true;
	};

	struct GhostBehaviour
	{
		float speed = 150.f;
		float range = 400.f;
		bool agro = false;
		bool retreat = false;
		glm::vec3 basePosition = { 0.f, 0.f, 0.f };
		HBL::IEntity* target = nullptr;
		HBL::IEntity* territory = nullptr;
		bool Enabled = true;
	};

	struct GhostStunner
	{
		bool stunned = false;
		double stunTime = 0.0;
		double stunDuration = 5.0;
		HBL::IEntity* target = nullptr;
		bool Enabled = true;
	};

	struct Collectible
	{
		uint32_t points = 10;
		HBL::IEntity* target = nullptr;
		bool Enabled = true;
	};
}