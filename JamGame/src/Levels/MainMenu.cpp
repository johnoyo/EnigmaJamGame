#include "MainMenu.h"

void MainMenu::OnAttach()
{
	// Camera entity set up.
	Registry::Get().EnrollEntity(m_Camera, "Camera");
	Registry::Get().AddComponent<Component::Camera>(m_Camera);
	Registry::Get().GetComponent<Component::Camera>(m_Camera).projection = glm::ortho(0.0f, Systems::Window.GetWidth(), 0.0f, Systems::Window.GetHeight(), -1.0f, 1.0f);

	// Background set up.
	Registry::Get().EnrollEntity(m_Background, "Background");
	Registry::Get().AddComponent<Component::SpriteRenderer>(m_Background);

	Component::Transform& backgroundTransform = Registry::Get().GetComponent<Component::Transform>(m_Background);
	backgroundTransform.position = { Systems::Window.GetWidth() / 2.f, Systems::Window.GetHeight() / 2.f, 0.f };
	backgroundTransform.scale = { 1920.f, 1080.f, 0.f };

	Component::SpriteRenderer& backgroundSpriteRenderer = Registry::Get().GetComponent<Component::SpriteRenderer>(m_Background);
	backgroundSpriteRenderer.texture = "res/textures/Background.png";

	// Buttons entity set up.
	Registry::Get().EnrollEntity(m_Buttons[0], "PlayButton");
	Registry::Get().AddComponent<Component::Text>(m_Buttons[0]);
	Registry::Get().AddComponent<Component::SpriteRenderer>(m_Buttons[0]);

	Registry::Get().EnrollEntity(m_Buttons[1], "AboutButton");
	Registry::Get().AddComponent<Component::Text>(m_Buttons[1]);
	Registry::Get().AddComponent<Component::SpriteRenderer>(m_Buttons[1]);

	Registry::Get().EnrollEntity(m_Buttons[2], "ExitButton");
	Registry::Get().AddComponent<Component::Text>(m_Buttons[2]);
	Registry::Get().AddComponent<Component::SpriteRenderer>(m_Buttons[2]);

	// Play button.
	{
		Component::Transform& playButtonTransform = Registry::Get().GetComponent<Component::Transform>(m_Buttons[0]);
		playButtonTransform.position = { Systems::Window.GetWidth() / 2.f, Systems::Window.GetHeight() / 2.f - 275.f, 0.f };
		playButtonTransform.scale = { 230.f, 70.f, 0.f };

		Registry::Get().GetComponent<Component::SpriteRenderer>(m_Buttons[0]).color = { 0.3f, 0.5f, 0.6f, 0.8f };

		Component::Text& playButtonText = Registry::Get().GetComponent<Component::Text>(m_Buttons[0]);
		playButtonText.text = "PLAY";
		playButtonText.position = { playButtonTransform.position.x - 55.f, playButtonTransform.position.y - 2.5f, 0.f };
		playButtonText.scale = { 1.f, 1.f, 0.f };
	}

	// About button.
	{
		Component::Transform& playButtonTransform = Registry::Get().GetComponent<Component::Transform>(m_Buttons[1]);
		playButtonTransform.position = { Systems::Window.GetWidth() / 2.f, Systems::Window.GetHeight() / 2.f - 375.f, 0.f };
		playButtonTransform.scale = { 230.f, 70.f, 0.f };

		Registry::Get().GetComponent<Component::SpriteRenderer>(m_Buttons[1]).color = { 0.3f, 0.5f, 0.6f, 0.8f };

		Component::Text& playButtonText = Registry::Get().GetComponent<Component::Text>(m_Buttons[1]);
		playButtonText.text = "ABOUT";
		playButtonText.position = { playButtonTransform.position.x - 80.f, playButtonTransform.position.y - 2.5f, 0.f };
		playButtonText.scale = { 1.f, 1.f, 0.f };
	}

	// Exit button.
	{
		Component::Transform& playButtonTransform = Registry::Get().GetComponent<Component::Transform>(m_Buttons[2]);
		playButtonTransform.position = { Systems::Window.GetWidth() / 2.f, Systems::Window.GetHeight() / 2.f - 475.f, 0.f };
		playButtonTransform.scale = { 230.f, 70.f, 0.f };

		Registry::Get().GetComponent<Component::SpriteRenderer>(m_Buttons[2]).color = { 0.3f, 0.5f, 0.6f, 0.8f };

		Component::Text& playButtonText = Registry::Get().GetComponent<Component::Text>(m_Buttons[2]);
		playButtonText.text = "EXIT";
		playButtonText.position = { playButtonTransform.position.x - 50.f, playButtonTransform.position.y - 2.5f, 0.f };
		playButtonText.scale = { 1.f, 1.f, 0.f };
	}

	// Cursor Set up.
	{
		Registry::Get().EnrollEntity(m_Cursor, "Cursor");
		Registry::Get().AddComponent<Component::SpriteRenderer>(m_Cursor);
		Registry::Get().AddComponent<MyComponent::Menu>(m_Cursor);

		Component::Transform& playButtonTransform = Registry::Get().GetComponent<Component::Transform>(m_Cursor);
		playButtonTransform.position = { Systems::Window.GetWidth() / 2.f, Systems::Window.GetHeight() / 2.f - 275.f, 0.f };
		playButtonTransform.scale = { 260.f, 100.f, 0.f };

		Registry::Get().GetComponent<Component::SpriteRenderer>(m_Cursor).color = { 1.0f, 1.0f, 1.0f, 0.3f };
	}

	// About screen set up.
	Registry::Get().EnrollEntity(m_AboutScreen, "AboutScreen");
	Registry::Get().AddComponent<Component::SpriteRenderer>(m_AboutScreen);

	Component::Transform& aboutScreenTransform = Registry::Get().GetComponent<Component::Transform>(m_AboutScreen);
	aboutScreenTransform.position = { Systems::Window.GetWidth() / 2.f, Systems::Window.GetHeight() / 2.f, 0.f };
	aboutScreenTransform.scale = { 1500.f, 1000.f, 0.f };
	aboutScreenTransform.Static = true;

	Component::SpriteRenderer& aboutScreenSpriteRenderer = Registry::Get().GetComponent<Component::SpriteRenderer>(m_AboutScreen);
	aboutScreenSpriteRenderer.texture = "res/textures/About.png";
	aboutScreenSpriteRenderer.color = { 0.3f, 0.5f, 0.6f, 1.0f };
}

void MainMenu::OnCreate()
{
	SoundManager::Play("res/audio/the_field_of_dreams.mp3", true);
}

void MainMenu::OnDetach()
{
	SoundManager::Stop("res/audio/the_field_of_dreams.mp3");
}

