#pragma once

using namespace HBL;

class DoorSystem final : public ISystem
{
public:

	IEntity key[3] = { Registry::InvalidEntity, Registry::InvalidEntity, Registry::InvalidEntity };
	IEntity player = Registry::InvalidEntity;
	uint32_t index = 0;

	virtual void Start() override
	{
		FUNCTION_PROFILE();

		key[0] = Registry::Get().FindEntityWithTag("Key0");
		key[1] = Registry::Get().FindEntityWithTag("Key1");
		key[2] = Registry::Get().FindEntityWithTag("Key2");

		player = Registry::Get().FindEntityWithTag("Player");

		Registry::Get().Group<Component::SpriteRenderer, Component::Shadow, Component::CollisionBox, MyComponent::Door>().ForEach([&](IEntity& entt)
		{
			// Empty.
		}).Run();
	}

	virtual void Run(float dt) override
	{
		index = 0;

		Registry::Get().Group<Component::SpriteRenderer, Component::Shadow, Component::CollisionBox, MyComponent::Door>().ForEach([&](IEntity& entt)
		{
			MyComponent::Door& door = Registry::Get().GetComponent<MyComponent::Door>(entt);

			if (door.Enabled)
			{
				Component::Shadow& shadow = Registry::Get().GetComponent<Component::Shadow>(entt);
				Component::SpriteRenderer& sprite = Registry::Get().GetComponent<Component::SpriteRenderer>(entt);
				Component::CollisionBox& collisionBox = Registry::Get().GetComponent<Component::CollisionBox>(entt);

				if (Systems::Collision.CollisionBetween(key[index], player))
				{
					SoundManager::Play("res/audio/magical_1.ogg");

					Registry::Get().GetComponent<Component::SpriteRenderer>(key[index]).Enabled = false;
					Registry::Get().GetComponent<Component::CollisionBox>(key[index]).Enabled = false;

					door.locked = false;

					sprite.Enabled = false;
					shadow.Enabled = false;
					collisionBox.Enabled = false;
				}
			}

			index++;
		}).Run();
	}

	virtual void Clear() override
	{
		Registry::Get().ClearArray<MyComponent::Door>();
	}
};