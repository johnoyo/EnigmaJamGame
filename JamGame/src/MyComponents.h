#pragma once

namespace MyComponent 
{
	struct Tranquilizer
	{
		float remaining = 100.f;
		float chargeSpeed = 7.5f;
		float overheatChargeSpeed = 3.5f;
		float dischargeSpeed = 100.f;
		bool overheat = false;
		bool Right = false;
		bool Left = false;
		bool Up = false;
		bool Down = true;
		HBL::IEntity* owner = nullptr;
		bool acquired = false;
		bool Enabled = true;
	};

	struct GhostBehaviour
	{
		float speed = 150.f;
		float range = 450.f;
		float minRange = 15.f;
		bool agro = false;
		bool retreat = false;
		bool attacking = false;
		glm::vec3 basePosition = { 0.f, 0.f, 0.f };
		HBL::IEntity* territory = nullptr;
		bool Enabled = true;
	};

	struct GhostStunner
	{
		bool stunned = false;
		double stunTime = 0.0;
		double stunDuration = 5.0;
		bool Enabled = true;
	};

	struct Collectible
	{
		uint32_t points = 10U;
		HBL::IEntity* target = nullptr;
		bool Enabled = true;
	};

	struct Lava
	{
		HBL::IEntity* target = nullptr;
		bool Enabled = true;
	};

	struct PlayerHandler
	{
		float fear = 0.f;
		bool hasGun = false;
		bool Enabled = true;
	};

	struct Door
	{
		bool locked = true;
		bool Enabled = true;
	};

	struct Menu
	{
		uint32_t index = 0;
		bool Enabled = true;
	};

	struct MovingGhostBehaviour
	{
		bool phaseA = false;
		bool phaseB = false;
		bool Enabled = true;
	};
}