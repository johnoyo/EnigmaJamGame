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

		Registry::Get().Group<Component::Transform, Component::SpriteRenderer, Component::Animation, Component::CollisionBox, Component::Text, MyComponent::PlayerHandler>().ForEach([&](IEntity& entt)
		{
			MyComponent::PlayerHandler& playerHandler = Registry::Get().GetComponent<MyComponent::PlayerHandler>(entt);

			if (playerHandler.Enabled)
			{
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
		});
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
				if (InputManager::GetKeyDown(GLFW_KEY_D))
				{
					transform.position.x += 210.0f * dt;
					//Systems::Animation.PlayAnimation(animation_p, 0);
				}
				else
				{
					//Systems::Animation.StopAnimation(animation_p, 0);
				}
				//if (InputManager::GetKeyRelease(GLFW_KEY_D))
				//	Systems::Animation.ResetAnimation(animation_p, 0, 5);

				if (InputManager::GetKeyDown(GLFW_KEY_A)) {
					transform.position.x -= 210.0f * dt;
				}

				if (InputManager::GetKeyDown(GLFW_KEY_S))
					transform.position.y -= 210.0f * dt;

				if (InputManager::GetKeyDown(GLFW_KEY_W))
				{
					transform.position.y += 210.0f * dt;
					//	Systems::Animation.PlayAnimation(animation_p, 1);
				}
				else
				{
					//	Systems::Animation.StopAnimation(animation_p, 1);
				}
				//if (InputManager::GetKeyRelease(GLFW_KEY_W))
				//	Systems::Animation.ResetAnimation(animation_p, 1, 5);
			}

		}).Run();
	}

	virtual void Clear() override
	{
		Registry::Get().ClearArray<MyComponent::PlayerHandler>();
	}
};