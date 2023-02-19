#pragma once

using namespace HBL;

class MovingEnemySystem final : public ISystem
{
public:
	IEntity player;

	virtual void Start() override
	{
		FUNCTION_PROFILE();

		player = Registry::Get().FindEntityWithTag("Player");
	}

	virtual void Run(float dt) override
	{
		Registry::Get().Group<Component::Transform, MyComponent::MovingGhostBehaviour>().ForEach([&](IEntity& entt)
		{
			MyComponent::MovingGhostBehaviour& movingGhostBehaviour = Registry::Get().GetComponent<MyComponent::MovingGhostBehaviour>(entt);

			if (movingGhostBehaviour.Enabled)
			{
				Component::Transform& transform = Registry::Get().GetComponent<Component::Transform>(entt);

				if (transform.position.y <= 2340.f && !movingGhostBehaviour.phaseA)
				{
					movingGhostBehaviour.phaseA = true;
					movingGhostBehaviour.phaseB = false;
				}
					
				if (transform.position.y >= 2550.f && !movingGhostBehaviour.phaseB)
				{
					movingGhostBehaviour.phaseA = false;
					movingGhostBehaviour.phaseB = true;
				}

				if (movingGhostBehaviour.phaseA)
					transform.position.y += 200.f * dt;

				if (movingGhostBehaviour.phaseB)
					transform.position.y -= 200.f * dt;

				if (Systems::Collision.CollisionBetween(entt, player))
				{
					// Lose health.
					Component::Text& text = Registry::Get().GetComponent<Component::Text>(player);
					MyComponent::PlayerHandler& playerHandler = Registry::Get().GetComponent<MyComponent::PlayerHandler>(player);

					playerHandler.fear += 60.f * dt;

					text.text = "FEAR: " + std::to_string((int)playerHandler.fear);
				}
			}

		}).Run();
	}

	virtual void Clear() override
	{
		Registry::Get().ClearArray<MyComponent::MovingGhostBehaviour>();
	}
};