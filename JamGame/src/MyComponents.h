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
		float speed = 100.f;
		float range = 400.f;
		HBL::IEntity* target = nullptr;
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
}