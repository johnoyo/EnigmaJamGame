#pragma once

using namespace HBL;

class CollectibleSystem final : public ISystem
{
public:
	IEntity m_Player;
	IEntity m_Counter;
	int m_Collected = 0;

	virtual void Start() override
	{
		FUNCTION_PROFILE();

		m_Player = Registry::Get().FindEntityWithTag("Player");
		m_Counter = Registry::Get().FindEntityWithTag("CoinsCounter");
	}

	virtual void Run(float dt) override
	{
		Registry::Get().Group<Component::SpriteRenderer, Component::CollisionBox, MyComponent::Collectible>().ForEach([&](IEntity& entt)
		{
			MyComponent::Collectible& collectible = Registry::Get().GetComponent<MyComponent::Collectible>(entt);

			if (collectible.Enabled)
			{
				Component::CollisionBox& collision = Registry::Get().GetComponent<Component::CollisionBox>(entt);
				Component::SpriteRenderer& sprite = Registry::Get().GetComponent<Component::SpriteRenderer>(entt);

				if (m_Player != Registry::InvalidEntity)
				{
					if (Systems::Collision.CollisionBetween(entt, m_Player))
					{
						ENGINE_LOG("CollisionBetween collectible and player.");

						// Play sound.
						SoundManager::Play("res/audio/coin02.wav", false, false);

						// Increase score.
						m_Collected++;
						if (m_Counter != Registry::InvalidEntity)
						{
							Component::Text& coinCounter = Registry::Get().GetComponent<Component::Text>(m_Counter);
							coinCounter.text = "COINS: " + std::to_string(m_Collected) + "/12";
						}

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
		Registry::Get().ClearArray<MyComponent::Collectible>();
	}
};