#include "EndScreen.h"

extern bool Won;

void EndScreen::OnAttach()
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

	if (Won)
		backgroundSpriteRenderer.texture = "res/textures/Win.jpg";
	else
		backgroundSpriteRenderer.texture = "res/textures/GameOver.jpg";
}

void EndScreen::OnCreate()
{
	SoundManager::Play("res/audio/the_field_of_dreams.mp3", true);
}

void EndScreen::OnDetach()
{
	SoundManager::Stop("res/audio/the_field_of_dreams.mp3");
}
