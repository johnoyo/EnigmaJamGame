#pragma once

using namespace HBL;

class LavaSystem final : public ISystem
{
public:
	virtual void Start() override
	{
		FUNCTION_PROFILE();

		IEntity& target = Registry::Get().FindEntityWithTag("Player");

		Registry::Get().View<MyComponent::Lava>().ForEach([&](MyComponent::Lava& lava)
		{
			if (lava.Enabled)
			{
				if (target != Registry::InvalidEntity)
					lava.target = &target;
			}
		}).Run();
	}

	virtual void Run(float dt) override
	{
		Registry::Get().Group<Component::CollisionBox, MyComponent::Lava>().ForEach([&](IEntity& entt)
		{
			MyComponent::Lava& lava = Registry::Get().GetComponent<MyComponent::Lava>(entt);
			Component::CollisionBox& collisionBox = Registry::Get().GetComponent<Component::CollisionBox>(entt);

			if (lava.Enabled)
			{
				if (lava.target != nullptr)
				{
					if (Systems::Collision.CollisionBetween(entt, *lava.target))
					{
						ENGINE_LOG("Gameover: CollisionBetween lava and player.");

						// Play game over sound.
						SoundManager::Play("res/audio/coin02.wav", false, false);

						// Gameover.

					}
				}
			}

		}).Run();
	}

	virtual void Clear() override
	{
		Registry::Get().ClearArray<MyComponent::Lava>();
	}
};