#pragma once

using namespace HBL;

class PatrolGhostBehaviourSystem final : public ISystem
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
		Registry::Get().Group<Component::Transform, MyComponent::PatrolGhostBehaviour>().ForEach([&](IEntity& entt)
		{
			MyComponent::PatrolGhostBehaviour& patrolGhostBehaviour = Registry::Get().GetComponent<MyComponent::PatrolGhostBehaviour>(entt);

			if (patrolGhostBehaviour.Enabled)
			{
				Component::Transform& transform = Registry::Get().GetComponent<Component::Transform>(entt);

				if (transform.position.x <= 1440.f && !patrolGhostBehaviour.phaseA)
				{
					patrolGhostBehaviour.phaseA = true;
					patrolGhostBehaviour.phaseB = false;
				}

				if (transform.position.x >= 2340.f && !patrolGhostBehaviour.phaseB)
				{
					patrolGhostBehaviour.phaseA = false;
					patrolGhostBehaviour.phaseB = true;
				}

				if (patrolGhostBehaviour.phaseA)
					transform.position.x += 200.f * dt;

				if (patrolGhostBehaviour.phaseB)
					transform.position.x -= 200.f * dt;

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
		Registry::Get().ClearArray<MyComponent::PatrolGhostBehaviour>();
	}
};