#pragma once

class PlayerDirectionSystem final : public HBL::ISystem
{
public:
	virtual void Start() override
	{
		FUNCTION_PROFILE();
	}
	virtual void Run(float dt) override
	{
		HBL::Registry::Get().Group<HBL::Component::Transform, MyComponent::PlayerDirection>().ForEach([&](HBL::IEntity& entt)
		{
			MyComponent::PlayerDirection& playerDirection = HBL::Registry::Get().GetComponent<MyComponent::PlayerDirection>(entt);
			if (HBL::InputManager::GetKeyDown(GLFW_KEY_A))
			{
				playerDirection.Right = false;
				playerDirection.Left = true;
				playerDirection.Up = false;
				playerDirection.Down = false;
			}
			else if (HBL::InputManager::GetKeyDown(GLFW_KEY_D))
			{
				playerDirection.Right = true;
				playerDirection.Left = false;
				playerDirection.Up = false;
				playerDirection.Down = false;
			}
			else if (HBL::InputManager::GetKeyDown(GLFW_KEY_W))
			{
				playerDirection.Right = false;
				playerDirection.Left = false;
				playerDirection.Up = true;
				playerDirection.Down = false;
			}
			else if (HBL::InputManager::GetKeyDown(GLFW_KEY_S))
			{
				playerDirection.Right = false;
				playerDirection.Left = false;
				playerDirection.Up = false;
				playerDirection.Down = true;
			}
		}).Run();
	}
	virtual void Clear() override { }
};