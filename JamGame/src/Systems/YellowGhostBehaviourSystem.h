#pragma once

using namespace HBL;

class YellowGhostBehaviourSystem final : public ISystem
{
public:
	IEntity target;

	virtual void Start() override
	{
		FUNCTION_PROFILE();

		target = Registry::Get().FindEntityWithTag("Player");
	}

	virtual void Run(float dt) override
	{
		Registry::Get().Group<Component::Transform, MyComponent::YellowGhostBehaviour>().ForEach([&](IEntity& entt)
		{
			Component::Transform& transform = Registry::Get().GetComponent<Component::Transform>(entt);
			MyComponent::YellowGhostBehaviour& yellowGhostBehaviour = Registry::Get().GetComponent<MyComponent::YellowGhostBehaviour>(entt);

			if (yellowGhostBehaviour.Enabled)
			{
				MyComponent::GhostStunner& ghostStunner = Registry::Get().GetComponent<MyComponent::GhostStunner>(entt);

				if (!ghostStunner.stunned)
				{
					Component::Transform& transformPlayer = Registry::Get().GetComponent<Component::Transform>(target);

					float xDistance = transformPlayer.position.x - transform.position.x;
					float yDistance = transformPlayer.position.y - transform.position.y;

					float hypotenuse = sqrt((xDistance * xDistance) + (yDistance * yDistance));

					// Go towards player.
					if (hypotenuse > yellowGhostBehaviour.minRange)
					{
						transform.position.x += dt * yellowGhostBehaviour.speed * (xDistance / hypotenuse);
						transform.position.y += dt * yellowGhostBehaviour.speed * (yDistance / hypotenuse);
					}

					if (Systems::Collision.CollisionBetween(entt, target))
					{
						ENGINE_LOG("CollisionBetween ghost and player.");

						// Play sound.

						// Lose health.
						Component::Text& text = Registry::Get().GetComponent<Component::Text>(target);
						MyComponent::PlayerHandler& playerHandler = Registry::Get().GetComponent<MyComponent::PlayerHandler>(target);

						playerHandler.fear += 20.f * dt;

						text.text = "FEAR: " + std::to_string((int)playerHandler.fear);
					}
				}
			}

		}).Run();
	}

	virtual void Clear() override
	{
		Registry::Get().ClearArray<MyComponent::YellowGhostBehaviour>();
	}
};