#pragma once

using namespace HBL;

class GhostStunnerSystem final : public ISystem
{
public:
	virtual void Start() override
	{
		FUNCTION_PROFILE();

		IEntity& target = Registry::Get().FindEntityWithTag("TranquilizerWave");

		Registry::Get().View<MyComponent::GhostStunner>().ForEach([&](MyComponent::GhostStunner& ghostStunner)
		{
			if (ghostStunner.Enabled)
			{
				if (target != Registry::InvalidEntity)
					ghostStunner.target = &target;
			}
		}).Run();
	}

	virtual void Run(float dt) override
	{
		Registry::Get().Group<Component::Transform, Component::Animation, MyComponent::GhostStunner>().ForEach([&](IEntity& entt)
		{
			Component::Transform& ghostTransform = Registry::Get().GetComponent<Component::Transform>(entt);
			Component::Animation& ghostAnimation = Registry::Get().GetComponent<Component::Animation>(entt);
			MyComponent::GhostStunner& ghostStunner = Registry::Get().GetComponent<MyComponent::GhostStunner>(entt);

			if (ghostStunner.Enabled)
			{
				if (ghostStunner.target != nullptr)
				{
					if (Systems::Collision.CollisionBetween(entt, *ghostStunner.target) && !ghostStunner.stunned)
					{
						// Play sound.
   						ghostStunner.stunned = true;
						ghostStunner.stunTime = Systems::Window.GetTime();

						Systems::Animation.PlayAnimation(ghostAnimation, 1);

						ENGINE_LOG("CollisionBetween ghost and tranquilizer.");
					}

					if (ghostStunner.stunned)
					{
						if (Systems::Window.GetTime() - ghostStunner.stunTime >= ghostStunner.stunDuration)
						{
							ghostStunner.stunned = false;
							Systems::Animation.PlayAnimation(ghostAnimation, 0);
						}
					}
				}
			}
		}).Run();
	}

	virtual void Clear() override
	{
		Registry::Get().ClearArray<MyComponent::GhostStunner>();
	}
};