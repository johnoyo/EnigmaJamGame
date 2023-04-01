#pragma once

#include "glm/gtc/type_ptr.hpp"

using namespace HBL;

class LightSystem final : public ISystem
{
public:
	IEntity target;

	virtual void Start() override
	{
		FUNCTION_PROFILE();

		target = Registry::Get().FindEntityWithTag("Player");
	}

	virtual void Run(float dt) override
	{
		Registry::Get().Group<Component::Transform, MyComponent::Light>().ForEach([&](IEntity& entt)
		{
			Component::Transform& transform = Registry::Get().GetComponent<Component::Transform>(entt);
			MyComponent::Light& light = Registry::Get().GetComponent<MyComponent::Light>(entt);
			Component::Transform& transformTarget = Registry::Get().GetComponent<Component::Transform>(target);

			if (light.Enabled)
			{
				transform.position = transformTarget.position;
			}

		}).Run();
	}

	virtual void Clear() override
	{
		Registry::Get().ClearArray<MyComponent::Light>();
	}
};