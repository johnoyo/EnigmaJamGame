#pragma once

using namespace HBL;

class BossBehaviourSystem final : public ISystem
{
public:
	IEntity m_Player;
	IEntity m_Tranquilizer;

	virtual void Start() override
	{
		FUNCTION_PROFILE();

		m_Player = Registry::Get().FindEntityWithTag("Player");
		m_Tranquilizer = Registry::Get().FindEntityWithTag("TranquilizerWave");

		Registry::Get().Group<Component::Transform, Component::SpriteRenderer, Component::Animation, MyComponent::BossBehaviour>().ForEach([&](IEntity& entt)
		{
			MyComponent::BossBehaviour& bossBehaviour = Registry::Get().GetComponent<MyComponent::BossBehaviour>(entt);

			if (bossBehaviour.Enabled)
			{
				Component::Transform& transform = Registry::Get().GetComponent<Component::Transform>(entt);
				Component::SpriteRenderer& spriteRenderer = Registry::Get().GetComponent<Component::SpriteRenderer>(entt);
				Component::Animation& animation = Registry::Get().GetComponent<Component::Animation>(entt);

				animation.animations.push_back({ "IdleAnim", &spriteRenderer, { 0.0f, 1.0f }, 0.0, 0.3, 2, 2, true, true });
				animation.animations.push_back({ "ProtectedAnim", &spriteRenderer, { 0.0f, 2.0f }, 0.0, 0.3, 2, 2, true, false });
				animation.animations.push_back({ "DamagedAnim", &spriteRenderer, { 0.0f, 0.0f }, 0.0, 0.3, 2, 2, true, false });

				bossBehaviour.time = Systems::Window.GetTime();
			}

		}).Run();
	}

	virtual void Run(float dt) override
	{
		Registry::Get().Group<Component::Transform, Component::CollisionBox, Component::SpriteRenderer, Component::Animation, MyComponent::BossBehaviour>().ForEach([&](IEntity& entt)
		{
			MyComponent::BossBehaviour& bossBehaviour = Registry::Get().GetComponent<MyComponent::BossBehaviour>(entt);

			if (bossBehaviour.Enabled)
			{
				Component::Transform& transform = Registry::Get().GetComponent<Component::Transform>(entt);
				Component::Animation& animation = Registry::Get().GetComponent<Component::Animation>(entt);
				Component::CollisionBox& collisionBox = Registry::Get().GetComponent<Component::CollisionBox>(entt);
				Component::SpriteRenderer& spriteRenderer = Registry::Get().GetComponent<Component::SpriteRenderer>(entt);

				if (m_Player != Registry::InvalidEntity)
				{
					if (glm::distance(transform.position, Registry::Get().GetComponent<Component::Transform>(m_Player).position) < 100.f)
					{
						Component::Text& text = Registry::Get().GetComponent<Component::Text>(m_Player);
						MyComponent::PlayerHandler& playerHandler = Registry::Get().GetComponent<MyComponent::PlayerHandler>(m_Player);

						playerHandler.fear += 100.f * dt;

						text.text = "FEAR: " + std::to_string((int)playerHandler.fear);
					}
				}

				if (m_Player != Registry::InvalidEntity && !bossBehaviour.agro)
				{
					if (glm::distance(transform.position, Registry::Get().GetComponent<Component::Transform>(m_Player).position) < 200.f)
					{
						SoundManager::Play("res/audio/i_see_you_voice.mp3");
						bossBehaviour.agro = true;
					}
				}

				if (bossBehaviour.agro)
				{
					if (Systems::Window.GetTime() - bossBehaviour.time >= bossBehaviour.duration)
					{
						bossBehaviour.protectedPhase = !bossBehaviour.protectedPhase;
						bossBehaviour.time = Systems::Window.GetTime();

						if (!bossBehaviour.protectedPhase)
							bossBehaviour.attackTime = Systems::Window.GetTime();
					}

					if (bossBehaviour.protectedPhase)
					{
						Systems::Animation.PlayAnimation(animation, 1);
					}
					else
					{
						if (!bossBehaviour.damaged)
							Systems::Animation.PlayAnimation(animation, 0);

						if (Systems::Window.GetTime() - bossBehaviour.attackTime >= bossBehaviour.attackFrequency)
						{
							if (bossBehaviour.index < 150)
							{
								SoundManager::Play("res/audio/porta.ogg");

								Registry::Get().GetComponent<MyComponent::YellowGhostBehaviour>(bossBehaviour.yellowGhosts[bossBehaviour.index]).Enabled = true;
								Registry::Get().GetComponent<MyComponent::GhostStunner>(bossBehaviour.yellowGhosts[bossBehaviour.index]).Enabled = true;

								bossBehaviour.index++;
							}
							else
							{
								bossBehaviour.index = 0;

								for (int i = 0; i < 150; i++)
								{
									Registry::Get().GetComponent<MyComponent::YellowGhostBehaviour>(bossBehaviour.yellowGhosts[i]).Enabled = false;
									Registry::Get().GetComponent<MyComponent::GhostStunner>(bossBehaviour.yellowGhosts[i]).Enabled = false;
									Registry::Get().GetComponent<Component::Transform>(bossBehaviour.yellowGhosts[i]).Enabled = true;
									Registry::Get().GetComponent<Component::SpriteRenderer>(bossBehaviour.yellowGhosts[i]).Enabled = true;
									Registry::Get().GetComponent<Component::CollisionBox>(bossBehaviour.yellowGhosts[i]).Enabled = true;

									Registry::Get().GetComponent<Component::Transform>(bossBehaviour.yellowGhosts[i]).position = transform.position;
								}
							}

							bossBehaviour.attackTime = Systems::Window.GetTime();
						}
					}
				}

				if (bossBehaviour.health <= 0)
				{
					for (int i = 0; i < 150; i++)
					{
						Registry::Get().GetComponent<MyComponent::YellowGhostBehaviour>(bossBehaviour.yellowGhosts[i]).Enabled = false;
						Registry::Get().GetComponent<MyComponent::GhostStunner>(bossBehaviour.yellowGhosts[i]).Enabled = false;
						Registry::Get().GetComponent<Component::Transform>(bossBehaviour.yellowGhosts[i]).Enabled = false;
						Registry::Get().GetComponent<Component::SpriteRenderer>(bossBehaviour.yellowGhosts[i]).Enabled = false;
						Registry::Get().GetComponent<Component::CollisionBox>(bossBehaviour.yellowGhosts[i]).Enabled = false;
					}

					transform.Enabled = false;
					collisionBox.Enabled = false;
					spriteRenderer.Enabled = false;
					bossBehaviour.Enabled = false;

					// Win Screen.
					SceneManager::Get().LoadScene(0);
				}
			}

		}).Run();
	}

	virtual void Clear() override
	{
		Registry::Get().ClearArray<MyComponent::BossBehaviour>();
	}
};