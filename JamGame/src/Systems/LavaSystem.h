#pragma once

using namespace HBL;

class LavaSystem final : public ISystem
{
public:
	std::vector<IEntity> m_Ghosts;
	IEntity m_Target;

	virtual void Start() override
	{
		FUNCTION_PROFILE();

		m_Ghosts = Registry::Get().FindEntitiesWithTag("Ghost");

		m_Target = Registry::Get().FindEntityWithTag("Player");
	}

	virtual void Run(float dt) override
	{
		Registry::Get().Group<Component::CollisionBox, MyComponent::Lava>().ForEach([&](IEntity& entt)
		{
			MyComponent::Lava& lava = Registry::Get().GetComponent<MyComponent::Lava>(entt);
			Component::CollisionBox& collisionBox = Registry::Get().GetComponent<Component::CollisionBox>(entt);

			if (lava.Enabled)
			{
				if (m_Target != Registry::InvalidEntity)
				{
					if (Systems::Collision.CollisionBetween(entt, m_Target))
					{
						ENGINE_LOG("Gameover: CollisionBetween lava and player.");

						// Increase fear.
						Component::Text& text = Registry::Get().GetComponent<Component::Text>(m_Target);
						MyComponent::PlayerHandler& playerHandler = Registry::Get().GetComponent<MyComponent::PlayerHandler>(m_Target);

						playerHandler.fear += 30.f * dt;

						text.text = "FEAR: " + std::to_string((int)playerHandler.fear);
					}
				}

				for (IEntity& ghost : m_Ghosts)
				{
					Component::Transform& ghostTransform = Registry::Get().GetComponent<Component::Transform>(ghost);

					if (ghostTransform.Enabled)
					{
						if (Systems::Collision.CollisionBetween(entt, ghost))
						{
							// Dead.
							ghostTransform.Enabled = false;
							Registry::Get().GetComponent<Component::CollisionBox>(ghost).Enabled = false;
							Registry::Get().GetComponent<Component::SpriteRenderer>(ghost).Enabled = false;
							
							if (Registry::Get().HasComponent<MyComponent::GhostStunner>(ghost))
								Registry::Get().GetComponent<MyComponent::GhostStunner>(ghost).Enabled = false;

							if (Registry::Get().HasComponent<MyComponent::GhostBehaviour>(ghost))
								Registry::Get().GetComponent<MyComponent::GhostBehaviour>(ghost).Enabled = false;

							if (Registry::Get().HasComponent<MyComponent::YellowGhostBehaviour>(ghost))
								Registry::Get().GetComponent<MyComponent::YellowGhostBehaviour>(ghost).Enabled = false;
						}
					}
				}
			}

		}).Scedule();
	}

	virtual void Clear() override
	{
		Registry::Get().ClearArray<MyComponent::Lava>();
	}
};