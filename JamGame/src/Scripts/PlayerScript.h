#pragma once

#include "Humble.h"

using namespace HBL;

class PlayerScript final : public IScript
{
public:
	PlayerScript() {}
	~PlayerScript() {}

	IEntity player;
	IEntity tranquilizer;
	IEntity camera;

	virtual void OnCreate() override 
	{
		player = (Registry::Get().FindEntityWithTag("Player"));
		tranquilizer = (Registry::Get().FindEntityWithTag("Tranquilizer"));
		camera = (Registry::Get().FindEntityWithTag("Camera"));

		//Component::SpriteRenderer& sprite = Registry::Get().GetComponent<Component::SpriteRenderer>(player);
		//sprite.texture = "res/textures/super_mario_tiles.png";
		//sprite.coords = { 6.0f, 1.0f };
		//sprite.spriteSize = { 16.0f, 16.0f };

		//Component::Animation& animation = Registry::Get().GetComponent<Component::Animation>(player);

		//animation.animations.push_back({
		//	"WalkAnim",
		//	&sprite,
		//	{ 6.0f, 1.0f },
		//	0.0,
		//	0.5,
		//	5,
		//	5,
		//	true,
		//	false
		//});

		//animation.animations.push_back({
		//	"JumpAnim",
		//	&sprite,
		//	{ 5.0f, 2.0f },
		//	0.0,
		//	0.5,
		//	5,
		//	5,
		//	true,
		//	false
		//});

		//animation.animations[0].Enabled = false;
		//animation.animations[1].Enabled = false;
	}

	virtual void OnUpdate(float dt) override 
	{
		Component::Transform& transform_p = Registry::Get().GetComponent<Component::Transform>(player);
		//Component::Transform& transform_bg = Registry::Get().GetComponent<Component::Transform>(background);
		Component::Transform& transform_cam = Registry::Get().GetComponent<Component::Transform>(camera);
		Component::Animation& animation_p = Registry::Get().GetComponent<Component::Animation>(player);

		// Background follow player
		//transform_bg.position.x = transform_p.position.x;
		//transform_bg.position.y = transform_p.position.y;

		// Camera follow player
		transform_cam.position.x = transform_p.position.x + (-Systems::Window.GetWidth() / 2.0f);
		transform_cam.position.y = transform_p.position.y + (-Systems::Window.GetHeight() / 2.0f);

		// Player movement
		if (InputManager::GetKeyDown(GLFW_KEY_D)) 
		{
			transform_p.position.x += 210.0f * dt;
			//Systems::Animation.PlayAnimation(animation_p, 0);
		}
		else
		{
			//Systems::Animation.StopAnimation(animation_p, 0);
		}
		//if (InputManager::GetKeyRelease(GLFW_KEY_D))
		//	Systems::Animation.ResetAnimation(animation_p, 0, 5);

		if (InputManager::GetKeyPress(GLFW_KEY_SPACE))
			SoundManager::Play("res/audio/bleep.mp3", false, false);

		if (InputManager::GetKeyDown(GLFW_KEY_A)) {
			transform_p.position.x -= 210.0f * dt;
		}

		if (InputManager::GetKeyDown(GLFW_KEY_S))
			transform_p.position.y -= 210.0f * dt;

		if (InputManager::GetKeyDown(GLFW_KEY_W))
		{
			transform_p.position.y += 210.0f * dt;
		//	Systems::Animation.PlayAnimation(animation_p, 1);
		}
		else
		{
		//	Systems::Animation.StopAnimation(animation_p, 1);
		}
		//if (InputManager::GetKeyRelease(GLFW_KEY_W))
		//	Systems::Animation.ResetAnimation(animation_p, 1, 5);

		if (Systems::Collision.CollisionBetween(player, tranquilizer))
		{
			ENGINE_LOG("Player collided with tranquilizer gun!!!");
			Registry::Get().GetComponent<Component::CollisionBox>(tranquilizer).Enabled = false;
			Registry::Get().GetComponent<Component::SpriteRenderer>(tranquilizer).Enabled = false;
		}
	}
};