#pragma once

#include <string>

using namespace HBL;

class TranquilizerSystem final : public HBL::ISystem
{
public:
	IEntity m_Boss;
	virtual void Start() override
	{
		FUNCTION_PROFILE();

		IEntity& owner = Registry::Get().FindEntityWithTag("Player");
		m_Boss = Registry::Get().FindEntityWithTag("Boss");

		HBL::Registry::Get().View<MyComponent::Tranquilizer>().ForEach([&](MyComponent::Tranquilizer& tranquilizer)
		{
			if (tranquilizer.Enabled)
			{
				if (owner != Registry::InvalidEntity)
					tranquilizer.owner = &owner;
			}
		}).Run();
	}

	virtual void Run(float dt) override
	{
		HBL::Registry::Get().Group<HBL::Component::Transform, HBL::Component::CollisionBox, Component::Text, Component::SpriteRenderer, Component::Animation, MyComponent::Tranquilizer>().ForEach([&](HBL::IEntity& entt)
		{
			MyComponent::Tranquilizer& tranquilizer = HBL::Registry::Get().GetComponent<MyComponent::Tranquilizer>(entt);

			if (tranquilizer.Enabled)
			{
				// Aqcuire tranquilizer wave gun upon collision.
				if (tranquilizer.owner != nullptr && !tranquilizer.acquired)
				{
					if (Systems::Collision.CollisionBetween(*tranquilizer.owner, entt))
					{
						ENGINE_LOG("Player collided with tranquilizer gun!!!");

						Component::SpriteRenderer& spriteRenderer = HBL::Registry::Get().GetComponent<Component::SpriteRenderer>(entt);
						spriteRenderer.texture = "res/textures/TranquilizerSheet.png";
						spriteRenderer.coords = { 0.f, 0.f };
						spriteRenderer.spriteSize = { 90.f, 30.f };

						Component::Animation& animation = HBL::Registry::Get().GetComponent<Component::Animation>(entt);
						animation.animations.push_back({ "WaveAnim", &spriteRenderer, { 0.0f, 0.0f }, 0.0, 0.1, 2, 2, true, true });

						animation.Enabled = true;

						tranquilizer.acquired = true;
						Registry::Get().GetComponent<MyComponent::PlayerHandler>(*tranquilizer.owner).hasGun = true;
					}
				}

				if (tranquilizer.owner != nullptr && tranquilizer.acquired)
				{
					Component::Text& text = HBL::Registry::Get().GetComponent<Component::Text>(entt);
					Component::Transform& transform = HBL::Registry::Get().GetComponent<Component::Transform>(entt);
					Component::Animation& animation = HBL::Registry::Get().GetComponent<Component::Animation>(entt);
					Component::CollisionBox& collisionBox = HBL::Registry::Get().GetComponent<Component::CollisionBox>(entt);
					Component::SpriteRenderer& spriteRenderer = HBL::Registry::Get().GetComponent<Component::SpriteRenderer>(entt);

					Component::Transform& ownerTransform = HBL::Registry::Get().GetComponent<Component::Transform>(*tranquilizer.owner);

					// Set up current direction.
					if (HBL::InputManager::GetKeyDown(GLFW_KEY_A))
					{
						tranquilizer.Right = false;
						tranquilizer.Left = true;
						tranquilizer.Up = false;
						tranquilizer.Down = false;
					}
					else if (HBL::InputManager::GetKeyDown(GLFW_KEY_D))
					{
						tranquilizer.Right = true;
						tranquilizer.Left = false;
						tranquilizer.Up = false;
						tranquilizer.Down = false;
					}
					else if (HBL::InputManager::GetKeyDown(GLFW_KEY_W))
					{
						tranquilizer.Right = false;
						tranquilizer.Left = false;
						tranquilizer.Up = true;
						tranquilizer.Down = false;
						
					}
					else if (HBL::InputManager::GetKeyDown(GLFW_KEY_S))
					{
						tranquilizer.Right = false;
						tranquilizer.Left = false;
						tranquilizer.Up = false;
						tranquilizer.Down = true;
					}

					// Teak transform for each direction.
					if (HBL::InputManager::GetKeyDown(GLFW_KEY_SPACE))
					{
						if (tranquilizer.Left)
						{
							transform.position.x = ownerTransform.position.x - 70.f;
							transform.position.y = ownerTransform.position.y;
							transform.scale = { 90.f, 30.f, 0.f };

							MyComponent::BossBehaviour& bossbehaviour = Registry::Get().GetComponent<MyComponent::BossBehaviour>(m_Boss);
							if (glm::distance(transform.position, Registry::Get().GetComponent<Component::Transform>(m_Boss).position) < 90.f && !tranquilizer.overheat && !bossbehaviour.protectedPhase)
							{
								if (bossbehaviour.damaged = false)
									SoundManager::Play("res/audio/growl_0.flac");

								bossbehaviour.health -= 20 * dt;
								bossbehaviour.damaged = true;
								Systems::Animation.PlayAnimation(Registry::Get().GetComponent<Component::Animation>(m_Boss), 2);
							}
						}
						else if (tranquilizer.Right)
						{
							transform.position.x = ownerTransform.position.x + 70.f;
							transform.position.y = ownerTransform.position.y;
							transform.scale = { 90.f, 30.f, 0.f };

							MyComponent::BossBehaviour& bossbehaviour = Registry::Get().GetComponent<MyComponent::BossBehaviour>(m_Boss);
							if (glm::distance(transform.position, Registry::Get().GetComponent<Component::Transform>(m_Boss).position) < 90.f && !tranquilizer.overheat && !bossbehaviour.protectedPhase)
							{
								if (bossbehaviour.damaged = false)
									SoundManager::Play("res/audio/growl_0.flac");

								bossbehaviour.health -= 20 * dt;
								bossbehaviour.damaged = true;
								Systems::Animation.PlayAnimation(Registry::Get().GetComponent<Component::Animation>(m_Boss), 2);
							}
						}
						else if (tranquilizer.Up)
						{
							transform.position.x = ownerTransform.position.x;
							transform.position.y = ownerTransform.position.y + 70.f;
							transform.scale = { 30.f, 90.f, 0.f };

							MyComponent::BossBehaviour& bossbehaviour = Registry::Get().GetComponent<MyComponent::BossBehaviour>(m_Boss);
							if (glm::distance(transform.position, Registry::Get().GetComponent<Component::Transform>(m_Boss).position) < 90.f && !tranquilizer.overheat && !bossbehaviour.protectedPhase)
							{
								if (bossbehaviour.damaged = false)
									SoundManager::Play("res/audio/growl_0.flac");

								bossbehaviour.health -= 20 * dt;
								bossbehaviour.damaged = true;
								Systems::Animation.PlayAnimation(Registry::Get().GetComponent<Component::Animation>(m_Boss), 2);
							}
						}
						else if (tranquilizer.Down)
						{
							transform.position.x = ownerTransform.position.x;
							transform.position.y = ownerTransform.position.y - 70.f;
							transform.scale = { 30.f, 90.f, 0.f };

							MyComponent::BossBehaviour& bossbehaviour = Registry::Get().GetComponent<MyComponent::BossBehaviour>(m_Boss);
							if (glm::distance(transform.position, Registry::Get().GetComponent<Component::Transform>(m_Boss).position) < 90.f && !tranquilizer.overheat && !bossbehaviour.protectedPhase)
							{
								if (bossbehaviour.damaged = false)
									SoundManager::Play("res/audio/growl_0.flac");

								bossbehaviour.health -= 20 * dt;
								bossbehaviour.damaged = true;
								Systems::Animation.PlayAnimation(Registry::Get().GetComponent<Component::Animation>(m_Boss), 2);
							}
						}

						// Discharge if not overheated.
						if (!tranquilizer.overheat)
						{
							if (tranquilizer.remaining > 0.f)
								tranquilizer.remaining = tranquilizer.remaining - tranquilizer.dischargeSpeed * dt;
							else
								tranquilizer.remaining = 0.f;
						}

						text.text = "CHARGE: " + std::to_string((int)tranquilizer.remaining);

						if (tranquilizer.remaining > 10 && !tranquilizer.overheat)
						{
							collisionBox.Enabled = true;
							spriteRenderer.Enabled = true; 
						}
						else
						{
							// Enable overheat state. Turn text red.
							text.color = { 1.0f, 0.f, 0.f, 1.f };
							tranquilizer.overheat = true;
							collisionBox.Enabled = false;
							spriteRenderer.Enabled = false;
						}
					}
					// Recharge when not pressing SPACE.
					else
					{
						MyComponent::BossBehaviour& bossbehaviour = Registry::Get().GetComponent<MyComponent::BossBehaviour>(m_Boss);
						bossbehaviour.damaged = false;

						// Recharge if not overheated.
						if (!tranquilizer.overheat)
						{
							if (tranquilizer.remaining < 100.f)
								tranquilizer.remaining = tranquilizer.remaining + tranquilizer.chargeSpeed * dt;
							else
								tranquilizer.remaining = 100.f;
						}

						text.text = "CHARGE: " + std::to_string((int)tranquilizer.remaining);

						// Disable sprite and collision box.
						collisionBox.Enabled = false;
						spriteRenderer.Enabled = false;
					}

					// Handle overheat state.
					if (tranquilizer.overheat)
					{
						// Recharge.
						tranquilizer.remaining = tranquilizer.remaining + tranquilizer.overheatChargeSpeed * dt;

						if (tranquilizer.remaining > 50.f)
						{
							// Disable overheat state. Turn text color back to normal.
							text.color = { 1.0f, 0.8f, 0.5f, 1.f };
							tranquilizer.overheat = false;
						}
					}

					// Play tranquilizer wave sound if not overheated.
					if (HBL::InputManager::GetKeyPress(GLFW_KEY_SPACE) && !tranquilizer.overheat)
					{
						SoundManager::Play("res/audio/burst fire.mp3", false, false);
					}
				}
			}
		}).Run();
	}
	virtual void Clear() override 
	{
		Registry::Get().ClearArray<MyComponent::Tranquilizer>();
	}
};