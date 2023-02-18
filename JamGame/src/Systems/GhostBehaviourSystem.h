#pragma once

using namespace HBL;

class GhostBehaviourSystem final : public ISystem
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
		Registry::Get().Group<Component::Transform, MyComponent::GhostBehaviour, MyComponent::GhostStunner>().ForEach([&](IEntity& entt)
		{
			Component::Transform& ghostTransform = Registry::Get().GetComponent<Component::Transform>(entt);
			MyComponent::GhostBehaviour& ghostBehaviour = Registry::Get().GetComponent<MyComponent::GhostBehaviour>(entt);
			MyComponent::GhostStunner& ghostStaller = Registry::Get().GetComponent<MyComponent::GhostStunner>(entt);

			if (ghostBehaviour.Enabled)
			{
				if (target != Registry::Get().InvalidEntity)
				{
					// Enable agro state and disable retreat.
					bool inTerritory = Systems::Collision.CollisionBetween(target, *ghostBehaviour.territory);

					if (inTerritory)
					{
						ghostBehaviour.agro = true;
						ghostBehaviour.retreat = false;
					}

					// Move towards the player(Agro).
					if (!ghostStaller.stunned && ghostBehaviour.agro && !ghostBehaviour.retreat)
					{
						Component::Transform& targetTransform = Registry::Get().GetComponent<Component::Transform>(target);

						float xDistance = targetTransform.position.x - ghostTransform.position.x;
						float yDistance = targetTransform.position.y - ghostTransform.position.y;

						float hypotenuse = sqrt((xDistance * xDistance) + (yDistance * yDistance));

						if (hypotenuse < ghostBehaviour.range || inTerritory)
						{
							// Follow player
							if (hypotenuse > ghostBehaviour.minRange)
							{
								ghostTransform.position.x += dt * ghostBehaviour.speed * (xDistance / hypotenuse);
								ghostTransform.position.y += dt * ghostBehaviour.speed * (yDistance / hypotenuse);
							}
						}	
						else
						{
							// Player out of range. Trigger retreat.
							ghostBehaviour.agro = false;
							ghostBehaviour.retreat = true;
						}
					}
					// Move back to base position(retreat).
					else if (ghostBehaviour.retreat)
					{
						float xDistance = ghostBehaviour.basePosition.x - ghostTransform.position.x;
						float yDistance = ghostBehaviour.basePosition.y - ghostTransform.position.y;

						float hypotenuse = sqrt((xDistance * xDistance) + (yDistance * yDistance));

						// Go towards base location.
						ghostTransform.position.x += dt * ghostBehaviour.speed * (xDistance / hypotenuse);
						ghostTransform.position.y += dt * ghostBehaviour.speed * (yDistance / hypotenuse);

						// Reset retreat after arriving.
						if (glm::distance(ghostTransform.position, ghostBehaviour.basePosition) < 5.f)
						{
							ghostBehaviour.retreat = false;
						}
					}

					if (Systems::Collision.CollisionBetween(entt, target))
					{
						ENGINE_LOG("CollisionBetween ghost and player.");

						ghostBehaviour.attacking = true;

						// Play sound.

						// Lose health.
						Component::Text& text = Registry::Get().GetComponent<Component::Text>(target);
						MyComponent::PlayerHandler& playerHandler = Registry::Get().GetComponent<MyComponent::PlayerHandler>(target);

						playerHandler.fear += 20.f * dt;

						text.text = "FEAR: " + std::to_string((int)playerHandler.fear);
					}
					else
					{
						ghostBehaviour.attacking = false;
					}
				}
			}
		}).Run();
	}

	virtual void Clear() override 
	{ 
		Registry::Get().ClearArray<MyComponent::GhostBehaviour>();
	}
};