#pragma once

using namespace HBL;

class GhostBehaviourSystem final : public ISystem
{
public:
	virtual void Start() override
	{
		FUNCTION_PROFILE();

		Registry::Get().View<MyComponent::GhostBehaviour>().ForEach([&](MyComponent::GhostBehaviour& ghostBehaviour)
		{
			IEntity& target = Registry::Get().FindEntityWithTag("Player");
			if (target != Registry::InvalidEntity)
				ghostBehaviour.target = &target;
		}).Run();
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
				if (ghostBehaviour.target != nullptr)
				{
					if (!ghostStaller.stunned)
					{
						Component::Transform& targetTransform = Registry::Get().GetComponent<Component::Transform>(*(ghostBehaviour.target));

						float xDistance = targetTransform.position.x - ghostTransform.position.x;
						float yDistance = targetTransform.position.y - ghostTransform.position.y;

						float hypotenuse = sqrt((xDistance * xDistance) + (yDistance * yDistance));

						if (hypotenuse < ghostBehaviour.range)
						{
							ghostTransform.position.x += dt * ghostBehaviour.speed * (xDistance / hypotenuse);
							ghostTransform.position.y += dt * ghostBehaviour.speed * (yDistance / hypotenuse);
						}

						if (Systems::Collision.CollisionBetween(entt, *ghostBehaviour.target))
						{
							// Play sound.
							// Lose health.
							ENGINE_LOG("CollisionBetween ghost and player.");
						}
					}
				}
			}
		}).Run();
	}

	virtual void Clear() override 
	{ 
	}
};