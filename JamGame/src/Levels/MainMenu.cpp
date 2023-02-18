#include "MainMenu.h"

void MainMenu::OnAttach()
{
	// Camera entity set up.
	Registry::Get().EnrollEntity(m_Camera, "Camera");
	Registry::Get().AddComponent<Component::Camera>(m_Camera);
	Registry::Get().GetComponent<Component::Camera>(m_Camera).projection = glm::ortho(0.0f, Systems::Window.GetWidth(), 0.0f, Systems::Window.GetHeight(), -1.0f, 1.0f);

	// Buttons entity set up.
	Registry::Get().EnrollEntity(m_Buttons[0], "PlayButton");
	Registry::Get().AddComponent<Component::Text>(m_Buttons[0]);
	Registry::Get().AddComponent<Component::SpriteRenderer>(m_Buttons[0]);

	Registry::Get().EnrollEntity(m_Buttons[1], "HelpButton");
	Registry::Get().AddComponent<Component::Text>(m_Buttons[1]);
	Registry::Get().AddComponent<Component::SpriteRenderer>(m_Buttons[1]);

	Registry::Get().EnrollEntity(m_Buttons[2], "ExitButton");
	Registry::Get().AddComponent<Component::Text>(m_Buttons[2]);
	Registry::Get().AddComponent<Component::SpriteRenderer>(m_Buttons[2]);

	// Play button.
	{
		Component::Transform& playButtonTransform = Registry::Get().GetComponent<Component::Transform>(m_Buttons[0]);
		playButtonTransform.position = { Systems::Window.GetWidth() / 2.f, Systems::Window.GetHeight() / 2.f, 0.f };
		playButtonTransform.scale = { 190.f, 70.f, 0.f };

		Registry::Get().GetComponent<Component::SpriteRenderer>(m_Buttons[0]).color = { 1.0f, 0.5f, 0.8f, 1.0f };

		Component::Text& playButtonText = Registry::Get().GetComponent<Component::Text>(m_Buttons[0]);
		playButtonText.text = "PLAY";
		playButtonText.position = { playButtonTransform.position.x - 55.f, playButtonTransform.position.y - 2.5f, 0.f };
		playButtonText.scale = { 1.f, 1.f, 0.f };
	}

	// Help button.
	{
		Component::Transform& playButtonTransform = Registry::Get().GetComponent<Component::Transform>(m_Buttons[1]);
		playButtonTransform.position = { Systems::Window.GetWidth() / 2.f, Systems::Window.GetHeight() / 2.f - 100.f, 0.f };
		playButtonTransform.scale = { 190.f, 70.f, 0.f };

		Registry::Get().GetComponent<Component::SpriteRenderer>(m_Buttons[1]).color = { 1.0f, 0.5f, 0.8f, 1.0f };

		Component::Text& playButtonText = Registry::Get().GetComponent<Component::Text>(m_Buttons[1]);
		playButtonText.text = "HELP";
		playButtonText.position = { playButtonTransform.position.x - 55.f, playButtonTransform.position.y - 2.5f, 0.f };
		playButtonText.scale = { 1.f, 1.f, 0.f };
	}

	// Exit button.
	{
		Component::Transform& playButtonTransform = Registry::Get().GetComponent<Component::Transform>(m_Buttons[2]);
		playButtonTransform.position = { Systems::Window.GetWidth() / 2.f, Systems::Window.GetHeight() / 2.f - 200.f, 0.f };
		playButtonTransform.scale = { 190.f, 70.f, 0.f };

		Registry::Get().GetComponent<Component::SpriteRenderer>(m_Buttons[2]).color = { 1.0f, 0.5f, 0.8f, 1.0f };

		Component::Text& playButtonText = Registry::Get().GetComponent<Component::Text>(m_Buttons[2]);
		playButtonText.text = "EXIT";
		playButtonText.position = { playButtonTransform.position.x - 55.f, playButtonTransform.position.y - 2.5f, 0.f };
		playButtonText.scale = { 1.f, 1.f, 0.f };
	}

	// Cursor Set up.
	{
		Registry::Get().EnrollEntity(m_Cursor, "PlayButton");
		Registry::Get().AddComponent<Component::SpriteRenderer>(m_Cursor);
		Registry::Get().AddComponent<MyComponent::Menu>(m_Cursor);

		Component::Transform& playButtonTransform = Registry::Get().GetComponent<Component::Transform>(m_Cursor);
		playButtonTransform.position = { Systems::Window.GetWidth() / 2.f, Systems::Window.GetHeight() / 2.f, 0.f };
		playButtonTransform.scale = { 220.f, 100.f, 0.f };

		Registry::Get().GetComponent<Component::SpriteRenderer>(m_Cursor).color = { 1.0f, 1.0f, 1.0f, 0.2f };
	}
}

void MainMenu::OnCreate()
{
}

void MainMenu::OnDetach()
{
}

