#pragma once

using namespace HBL;

class MenuSystem final : public ISystem
{
public:
	virtual void Start() override
	{
		FUNCTION_PROFILE();

		IEntity playButton = Registry::Get().FindEntityWithTag("PlayButton");
		IEntity helpButton = Registry::Get().FindEntityWithTag("HelpButton");
		IEntity exitButton = Registry::Get().FindEntityWithTag("ExitButton");

		Registry::Get().View<MyComponent::Menu>().ForEach([&](MyComponent::Menu& menu)
		{
			if (menu.Enabled)
			{

			}
		}).Run();
	}

	virtual void Run(float dt) override
	{
		Registry::Get().Group<Component::Transform, MyComponent::Menu>().ForEach([&](IEntity& entt)
		{
			MyComponent::Menu& menu = Registry::Get().GetComponent<MyComponent::Menu>(entt);
			Component::Transform& transform = Registry::Get().GetComponent<Component::Transform>(entt);

			if (menu.Enabled)
			{
				if (InputManager::GetKeyPress(GLFW_KEY_DOWN) && menu.index < 2)
				{
					menu.index++;
					transform.position.y -= 100.f;
				}
				else if (InputManager::GetKeyPress(GLFW_KEY_UP) && menu.index > 0)
				{
					menu.index--;
					transform.position.y += 100.f;
				}
				else if (InputManager::GetKeyPress(GLFW_KEY_ENTER) || InputManager::GetKeyPress(GLFW_KEY_SPACE))
				{
					if (menu.index == 0)
					{
						SceneManager::Get().LoadNextScene();
					}
					else if (menu.index == 1)
					{
						SceneManager::Get().LoadNextScene();
					}
					else if (menu.index == 2)
					{
						Systems::Window.Close();
					}
				}
			}

		}).Run();
	}

	virtual void Clear() override
	{
		Registry::Get().ClearArray<MyComponent::Menu>();
	}
};