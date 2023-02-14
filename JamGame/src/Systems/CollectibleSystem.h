#pragma once

using namespace HBL;

class CollectibleSystem final : public ISystem
{
public:
	virtual void Start() override
	{
		FUNCTION_PROFILE();

		IEntity& target = Registry::Get().FindEntityWithTag("Player");

		Registry::Get().View<MyComponent::Collectible>().ForEach([&](MyComponent::Collectible& collectible)
		{
			if (collectible.Enabled)
			{
				if (target != Registry::InvalidEntity)
					collectible.target = &target;
			}
		}).Run();
	}

	virtual void Run(float dt) override
	{
		Registry::Get().Group < Component::SpriteRenderer, Component::CollisionBox, MyComponent::Collectible > ().ForEach([&](IEntity& entt)
		{
			MyComponent::Collectible& collectible = Registry::Get().GetComponent<MyComponent::Collectible>(entt);
			Component::CollisionBox& collision = Registry::Get().GetComponent<Component::CollisionBox>(entt);
			Component::SpriteRenderer& sprite = Registry::Get().GetComponent<Component::SpriteRenderer>(entt);

			if (collectible.Enabled)
			{
				if (collectible.target != nullptr)
				{
					if (Systems::Collision.CollisionBetween(entt, *collectible.target))
					{
						ENGINE_LOG("CollisionBetween collectible and player.");

						// Play sound.
						SoundManager::Play("res/audio/coin02.wav", false, false);

						// Increase score.

						// Disable sprite and collision box.
						sprite.Enabled = false;
						collision.Enabled = false;
					}
				}
			}
		
		}).Run();
	}

	virtual void Clear() override
	{
	}
};