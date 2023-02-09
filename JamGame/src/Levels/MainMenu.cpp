#include "MainMenu.h"

void MainMenu::OnAttach()
{
	// Camera entity set up.
	Registry::Get().EnrollEntity(m_Camera, "Camera");
	Registry::Get().AddComponent<Component::Camera>(m_Camera);
	Registry::Get().GetComponent<Component::Camera>(m_Camera).projection = glm::ortho(0.0f, Systems::Window.GetWidth(), 0.0f, Systems::Window.GetHeight(), -1.0f, 1.0f);

	// PlayButton entity set up.
	Registry::Get().EnrollEntity(m_PlayButton, "PlayButton");
	Registry::Get().AddComponent<Component::Text>(m_PlayButton);
	Registry::Get().AddComponent<Component::Clickable>(m_PlayButton);
	Registry::Get().AddComponent<Component::SpriteRenderer>(m_PlayButton);

	Component::Transform& playButtonTransform = Registry::Get().GetComponent<Component::Transform>(m_PlayButton);
	playButtonTransform.position = { Systems::Window.GetWidth() / 2.f, Systems::Window.GetHeight() / 2.f, 0.f };
	playButtonTransform.scale = { 190.f, 70.f, 0.f };

	Registry::Get().GetComponent<Component::SpriteRenderer>(m_PlayButton).color = { 1.0f, 0.5f, 0.8f, 1.0f };

	Component::Text& playButtonText = Registry::Get().GetComponent<Component::Text>(m_PlayButton);
	playButtonText.text = "PLAY";
	playButtonText.position = { playButtonTransform.position.x - 55.f, playButtonTransform.position.y - 2.5f, 0.f };
	playButtonText.scale = { 1.f, 1.f, 0.f };

	Registry::Get().GetComponent<Component::Clickable>(m_PlayButton).OnClick = [&]() { SceneManager::Get().TriggerSceneChange(); };
}

void MainMenu::OnCreate()
{
}

void MainMenu::OnDetach()
{
}

