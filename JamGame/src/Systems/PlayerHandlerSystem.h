#pragma once

using namespace HBL;

class PlayerHandlerSystem final : public ISystem
{
public:

	IEntity camera = Registry::InvalidEntity;

	virtual void Start() override
	{
		FUNCTION_PROFILE();

		camera = Registry::Get().FindEntityWithTag("Camera");

		Registry::Get().Group<Component::SpriteRenderer, Component::Animation, MyComponent::PlayerHandler>().ForEach([&](IEntity& entt)
		{
			MyComponent::PlayerHandler& playerHandler = Registry::Get().GetComponent<MyComponent::PlayerHandler>(entt);

			if (playerHandler.Enabled)
			{
				Component::SpriteRenderer& sprite = Registry::Get().GetComponent<Component::SpriteRenderer>(entt);
				Component::Animation& animation = Registry::Get().GetComponent<Component::Animation>(entt);

				animation.animations.push_back({ "WalkRightGunAnim", &sprite, { 0.0f, 5.0f }, 0.0, 0.2, 2, 2, true, false });
				animation.animations.push_back({ "WalkRightAnim", &sprite, { 0.0f, 1.0f }, 0.0, 0.2, 2, 2, true, false });

				animation.animations.push_back({ "WalkLeftGunAnim", &sprite, { 0.0f, 4.0f }, 0.0, 0.2, 2, 2, true, false });
				animation.animations.push_back({ "WalkLeftAnim", &sprite, { 0.0f, 0.0f }, 0.0, 0.2, 2, 2, true, false });

				animation.animations.push_back({ "WalkDownGunAnim", &sprite, { 0.0f, 7.0f }, 0.0, 0.2, 2, 2, true, false });
				animation.animations.push_back({ "WalkDownAnim", &sprite, { 0.0f, 3.0f }, 0.0, 0.2, 2, 2, true, false });

				animation.animations.push_back({ "WalkUpGunAnim", &sprite, { 0.0f, 6.0f }, 0.0, 0.2, 2, 2, true, false });
				animation.animations.push_back({ "WalkUpAnim", &sprite, { 0.0f, 2.0f }, 0.0, 0.2, 2, 2, true, false });

				for (auto& anim : animation.animations)
					anim.Enabled = false;
			}
		}).Run();
	}

	virtual void Run(float dt) override
	{
		Registry::Get().Group<Component::Transform, Component::SpriteRenderer, Component::Animation, Component::CollisionBox, Component::Text, MyComponent::PlayerHandler>().ForEach([&](IEntity& entt)
		{
			MyComponent::PlayerHandler& playerHandler = Registry::Get().GetComponent<MyComponent::PlayerHandler>(entt);

			if (playerHandler.Enabled)
			{
				Component::Transform& transform = Registry::Get().GetComponent<Component::Transform>(entt);
				Component::Animation& animation = Registry::Get().GetComponent<Component::Animation>(entt);
				Component::SpriteRenderer& sprite = Registry::Get().GetComponent<Component::SpriteRenderer>(entt);
				Component::CollisionBox& collisionBox = Registry::Get().GetComponent<Component::CollisionBox>(entt);
				Component::Text& text = Registry::Get().GetComponent<Component::Text>(entt);

				if (camera != Registry::InvalidEntity)
				{
					Component::Transform& transform_cam = Registry::Get().GetComponent<Component::Transform>(camera);

					// Camera follow player.
					transform_cam.position.x = transform.position.x + (-Systems::Window.GetWidth() / 2.0f);
					transform_cam.position.y = transform.position.y + (-Systems::Window.GetHeight() / 2.0f);
				}

				// Player health.
				if (playerHandler.fear >= 100.f)
				{
					// Play Gameover sound.

					// Gameover.
					SceneManager::Get().LoadScene(0);
				}

				// Player movement.

				// Right.
				if (InputManager::GetKeyDown(GLFW_KEY_D))
				{
					transform.position.x += 210.0f * dt;
					if (playerHandler.hasGun)
						Systems::Animation.PlayAnimation(animation, 0);
					else
						Systems::Animation.PlayAnimation(animation, 1);
				}
				else
				{
					if (playerHandler.hasGun)
						Systems::Animation.StopAnimation(animation, 0);
					else 
						Systems::Animation.StopAnimation(animation, 1);
				}
				if (InputManager::GetKeyRelease(GLFW_KEY_D))
				{
					if (playerHandler.hasGun)
						Systems::Animation.ResetAnimation(animation, 0, 2);
					else
						Systems::Animation.ResetAnimation(animation, 1, 2);
				}

				// Left.
				if (InputManager::GetKeyDown(GLFW_KEY_A)) 
				{
					transform.position.x -= 210.0f * dt;
					if (playerHandler.hasGun)
						Systems::Animation.PlayAnimation(animation, 2);
					else
						Systems::Animation.PlayAnimation(animation, 3);
				}
				else
				{
					if (playerHandler.hasGun)
						Systems::Animation.StopAnimation(animation, 2);
					else
						Systems::Animation.StopAnimation(animation, 3);
				}
				if (InputManager::GetKeyRelease(GLFW_KEY_A))
				{
					if (playerHandler.hasGun)
						Systems::Animation.ResetAnimation(animation, 2, 2);
					else
						Systems::Animation.ResetAnimation(animation, 3, 2);
				}

				// Down.
				if (InputManager::GetKeyDown(GLFW_KEY_S))
				{
					transform.position.y -= 210.0f * dt;
					if (playerHandler.hasGun)
						Systems::Animation.PlayAnimation(animation, 4);
					else
						Systems::Animation.PlayAnimation(animation, 5);
				}
				else
				{
					if (playerHandler.hasGun)
						Systems::Animation.StopAnimation(animation, 4);
					else
						Systems::Animation.StopAnimation(animation, 5);
				}
				if (InputManager::GetKeyRelease(GLFW_KEY_S))
				{
					if (playerHandler.hasGun)
						Systems::Animation.ResetAnimation(animation, 4, 2);
					else
						Systems::Animation.ResetAnimation(animation, 5, 2);
				}

				// Up.
				if (InputManager::GetKeyDown(GLFW_KEY_W))
				{
					transform.position.y += 210.0f * dt;
					if (playerHandler.hasGun)
						Systems::Animation.PlayAnimation(animation, 6);
					else
						Systems::Animation.PlayAnimation(animation, 7);
				}
				else
				{
					if (playerHandler.hasGun)
						Systems::Animation.StopAnimation(animation, 6);
					else
						Systems::Animation.StopAnimation(animation, 7);
				}
				if (InputManager::GetKeyRelease(GLFW_KEY_W))
				{
					if (playerHandler.hasGun)
						Systems::Animation.ResetAnimation(animation, 6, 2);
					else
						Systems::Animation.ResetAnimation(animation, 7, 2);
				}
			}

		}).Run();
	}

	virtual void Clear() override
	{
		Registry::Get().ClearArray<MyComponent::PlayerHandler>();
	}
};