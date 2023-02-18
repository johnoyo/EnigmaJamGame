#pragma once

using namespace HBL;

class LavaSystem final : public ISystem
{
public:
	std::vector<IEntity> m_Ghosts;

	virtual void Start() override
	{
		FUNCTION_PROFILE();

		m_Ghosts = Registry::Get().FindEntitiesWithTag("Ghost");

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

						// Increase fear.
						Component::Text& text = Registry::Get().GetComponent<Component::Text>(*lava.target);
						MyComponent::PlayerHandler& playerHandler = Registry::Get().GetComponent<MyComponent::PlayerHandler>(*lava.target);

						playerHandler.fear += 20.f * dt;

						text.text = "FEAR: " + std::to_string((int)playerHandler.fear);
					}
				}

				for (IEntity& ghost : m_Ghosts)
				{
					Component::Transform& ghostTransform = Registry::Get().GetComponent<Component::Transform>(ghost);

					if (ghostTransform.Enabled)
					{
						Component::CollisionBox& ghostCollisionBox = Registry::Get().GetComponent<Component::CollisionBox>(ghost);
						Component::SpriteRenderer& ghostSpriteRenderer = Registry::Get().GetComponent<Component::SpriteRenderer>(ghost);

						MyComponent::GhostStunner& ghostStunner = Registry::Get().GetComponent<MyComponent::GhostStunner>(ghost);
						MyComponent::GhostBehaviour& ghostBehaviour = Registry::Get().GetComponent<MyComponent::GhostBehaviour>(ghost);

						if (Systems::Collision.CollisionBetween(entt, ghost))
						{
							ENGINE_LOG("Ghost died: CollisionBetween lava and ghost.");

							// Play sound.

							// Dead.
							ghostTransform.Enabled = false;
							ghostCollisionBox.Enabled = false;
							ghostSpriteRenderer.Enabled = false;
							
							ghostStunner.Enabled = false;
							ghostBehaviour.Enabled = false;

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