#pragma once

using namespace HBL;

class MenuSystem final : public ISystem
{
public:
	IEntity m_AboutScreen;
	IEntity m_PlayButton;
	IEntity m_AboutButton;
	IEntity m_ExitButton;

	virtual void Start() override
	{
		FUNCTION_PROFILE();

		m_AboutScreen = Registry::Get().FindEntityWithTag("AboutScreen");
		m_PlayButton = Registry::Get().FindEntityWithTag("PlayButton");
		m_AboutButton = Registry::Get().FindEntityWithTag("AboutButton");
		m_ExitButton = Registry::Get().FindEntityWithTag("ExitButton");

		if (m_AboutScreen != Registry::InvalidEntity)
		{
			Registry::Get().GetComponent<Component::Transform>(m_AboutScreen).Enabled = false;
			Registry::Get().GetComponent<Component::SpriteRenderer>(m_AboutScreen).Enabled = false;
		}
	}

	virtual void Run(float dt) override
	{
		Registry::Get().Group<Component::Transform, MyComponent::Menu>().ForEach([&](IEntity& entt)
		{
			MyComponent::Menu& menu = Registry::Get().GetComponent<MyComponent::Menu>(entt);
			Component::Transform& transform = Registry::Get().GetComponent<Component::Transform>(entt);

			if (menu.Enabled)
			{
				if (InputManager::GetKeyPress(GLFW_KEY_DOWN) && menu.index < 2 && !menu.aboutScreen)
				{
					menu.index++;
					transform.position.y -= 100.f;
				}
				else if (InputManager::GetKeyPress(GLFW_KEY_UP) && menu.index > 0 && !menu.aboutScreen)
				{
					menu.index--;
					transform.position.y += 100.f;
				}
				else if (InputManager::GetKeyPress(GLFW_KEY_ENTER) || InputManager::GetKeyPress(GLFW_KEY_SPACE) && !menu.aboutScreen)
				{
					if (menu.index == 0)
					{
						SceneManager::Get().LoadNextScene();
					}
					else if (menu.index == 1)
					{
						menu.aboutScreen = true;

						Registry::Get().GetComponent<Component::Text>(m_PlayButton).color = { 0.0f, 0.0f, 0.0f, 0.0f };
						Registry::Get().GetComponent<Component::Text>(m_AboutButton).color = { 0.0f, 0.0f, 0.0f, 0.0f };
						Registry::Get().GetComponent<Component::Text>(m_ExitButton).color = { 0.0f, 0.0f, 0.0f, 0.0f };
					}
					else if (menu.index == 2)
					{
						Systems::Window.Close();
					}
				}

				if (menu.aboutScreen)
				{
					if (m_AboutScreen != Registry::InvalidEntity)
					{
						Registry::Get().GetComponent<Component::Transform>(m_AboutScreen).Enabled = true;
						Registry::Get().GetComponent<Component::SpriteRenderer>(m_AboutScreen).Enabled = true;
					}

					if (InputManager::GetKeyPress(GLFW_KEY_BACKSPACE) || InputManager::GetKeyPress(GLFW_KEY_ESCAPE))
					{
						menu.aboutScreen = false;
						if (m_AboutScreen != Registry::InvalidEntity)
						{
							Registry::Get().GetComponent<Component::Transform>(m_AboutScreen).Enabled = false;
							Registry::Get().GetComponent<Component::SpriteRenderer>(m_AboutScreen).Enabled = false;
						}

						Registry::Get().GetComponent<Component::Text>(m_PlayButton).color = { 1.0f, 1.0f, 1.0f, 1.0f };
						Registry::Get().GetComponent<Component::Text>(m_AboutButton).color = { 1.0f, 1.0f, 1.0f, 1.0f };
						Registry::Get().GetComponent<Component::Text>(m_ExitButton).color = { 1.0f, 1.0f, 1.0f, 1.0f };
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