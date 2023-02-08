#include "MainMenu.h"

void HBL::MainMenu::OnAttach()
{
	// Enroll entities.
	Registry::Get().EnrollEntity(m_Camera, "Camera");
	Registry::Get().EnrollEntity(m_PlayButton, "PlayButton");

	// Add components.
	Registry::Get().AddComponent<Component::Camera>(m_Camera);
	Registry::Get().AddComponent<Component::Text>(m_PlayButton);
	Registry::Get().AddComponent<Component::Clickable>(m_PlayButton);
	Registry::Get().AddComponent<Component::SpriteRenderer>(m_PlayButton);

	// Initialize components.
	Registry::Get().GetComponent<Component::Camera>(m_Camera).projection = glm::ortho(0.0f, Systems::Window.GetWidth(), 0.0f, Systems::Window.GetHeight(), -1.0f, 1.0f);
	Registry::Get().GetComponent<Component::Transform>(m_PlayButton).position = { Systems::Window.GetWidth() / 2.f, Systems::Window.GetHeight() / 2.f, 0.f };
	Registry::Get().GetComponent<Component::Transform>(m_PlayButton).scale = { 190.f, 70.f, 0.f };
	Registry::Get().GetComponent<Component::SpriteRenderer>(m_PlayButton).color = { 1.0f, 0.5f, 0.8f, 1.0f };
	Registry::Get().GetComponent<Component::Clickable>(m_PlayButton).OnClick = [&]() { SceneManager::Get().TriggerSceneChange(); };
	Registry::Get().GetComponent<Component::Text>(m_PlayButton).text = "PLAY";
	Registry::Get().GetComponent<Component::Text>(m_PlayButton).position = 
	{ Registry::Get().GetComponent<Component::Transform>(m_PlayButton).position.x - 55.f, Registry::Get().GetComponent<Component::Transform>(m_PlayButton).position.y - 2.5f, 0.f };
	Registry::Get().GetComponent<Component::Text>(m_PlayButton).scale = { 1.f, 1.f, 0.f };
}

void HBL::MainMenu::OnCreate()
{
}

void HBL::MainMenu::OnDetach()
{
}

