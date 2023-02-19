#pragma once

using namespace HBL;

class GhostStunnerSystem final : public ISystem
{
public:
	IEntity target;

	virtual void Start() override
	{
		FUNCTION_PROFILE();

		target = Registry::Get().FindEntityWithTag("TranquilizerWave");
	}

	virtual void Run(float dt) override
	{
		Registry::Get().Group<Component::Transform, Component::Animation, MyComponent::GhostStunner>().ForEach([&](IEntity& entt)
		{
			MyComponent::GhostStunner& ghostStunner = Registry::Get().GetComponent<MyComponent::GhostStunner>(entt);

			if (ghostStunner.Enabled)
			{
				Component::Transform& ghostTransform = Registry::Get().GetComponent<Component::Transform>(entt);
				Component::Animation& ghostAnimation = Registry::Get().GetComponent<Component::Animation>(entt);

				if (target != Registry::Get().InvalidEntity)
				{
					if (Systems::Collision.CollisionBetween(entt, target) && !ghostStunner.stunned)
					{
						// Play sound.
						SoundManager::Play("res/audio/freeze.wav", false, false);

   						ghostStunner.stunned = true;
						ghostStunner.stunTime = Systems::Window.GetTime();

						Systems::Animation.PlayAnimation(ghostAnimation, 1);
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