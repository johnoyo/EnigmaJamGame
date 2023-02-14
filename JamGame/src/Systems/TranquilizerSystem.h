#pragma once

#include <string>

using namespace HBL;

class TranquilizerSystem final : public HBL::ISystem
{
public:
	virtual void Start() override
	{
		FUNCTION_PROFILE();

		IEntity& owner = Registry::Get().FindEntityWithTag("Player");

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
		HBL::Registry::Get().Group<HBL::Component::Transform, HBL::Component::CollisionBox, Component::Text, Component::SpriteRenderer, MyComponent::Tranquilizer>().ForEach([&](HBL::IEntity& entt)
		{
			MyComponent::Tranquilizer& tranquilizer = HBL::Registry::Get().GetComponent<MyComponent::Tranquilizer>(entt);

			if (tranquilizer.Enabled)
			{
				if (tranquilizer.owner != nullptr)
				{
					Component::Text& text = HBL::Registry::Get().GetComponent<Component::Text>(entt);
					Component::Transform& transform = HBL::Registry::Get().GetComponent<Component::Transform>(entt);
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
							transform.scale.x = 90.f;
							transform.scale.y = 30.f;
						}
						else if (tranquilizer.Right)
						{
							transform.position.x = ownerTransform.position.x + 70.f;
							transform.position.y = ownerTransform.position.y;
							transform.scale.x = 90.f;
							transform.scale.y = 30.f;
						}
						else if (tranquilizer.Up)
						{
							transform.position.x = ownerTransform.position.x;
							transform.position.y = ownerTransform.position.y + 70.f;
							transform.scale.x = 30.f;
							transform.scale.y = 90.f;
						}
						else if (tranquilizer.Down)
						{
							transform.position.x = ownerTransform.position.x;
							transform.position.y = ownerTransform.position.y - 70.f;
							transform.scale.x = 30.f;
							transform.scale.y = 90.f;
						}

						// Discharge if not overheated.
						if (!tranquilizer.overheat)
						{
							if (tranquilizer.remaining > 0.f)
								tranquilizer.remaining = tranquilizer.remaining - tranquilizer.dischargeSpeed * dt;
							else
								tranquilizer.remaining = 0.f;
						}

						text.text = std::to_string((int)tranquilizer.remaining);

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
						// Recharge if not overheated.
						if (!tranquilizer.overheat)
						{
							if (tranquilizer.remaining < 100.f)
								tranquilizer.remaining = tranquilizer.remaining + tranquilizer.chargeSpeed * dt;
							else
								tranquilizer.remaining = 100.f;
						}

						text.text = std::to_string((int)tranquilizer.remaining);

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
				}
			}
		}).Run();
	}
	virtual void Clear() override { }
};