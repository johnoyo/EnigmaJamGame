#pragma once

using namespace HBL;

class TranquilizerWaveScript final : public IScript
{
public:
	TranquilizerWaveScript() {}
	~TranquilizerWaveScript() {}

	IEntity player;
	IEntity tranquilizerWave;

	virtual void OnCreate() override
	{
		player = (Registry::Get().FindEntityWithTag("Player"));
		tranquilizerWave = (Registry::Get().FindEntityWithTag("TranquilizerWave"));

		Component::Transform& pTr = Registry::Get().GetComponent<Component::Transform>(player);
		Component::Transform& trTr = Registry::Get().GetComponent<Component::Transform>(tranquilizerWave);

		trTr.position.x = pTr.position.x + 50.f;
		trTr.position.y = pTr.position.y;
		trTr.scale = { 90.f, 30.f, 0.f };

		Registry::Get().GetComponent<Component::CollisionBox>(tranquilizerWave).Enabled = false;
		Registry::Get().GetComponent<Component::SpriteRenderer>(tranquilizerWave).Enabled = false;
	}

	virtual void OnUpdate(float dt) override
	{
		MyComponent::PlayerDirection& pDir = Registry::Get().GetComponent<MyComponent::PlayerDirection>(player);
		Component::Transform& pTr = Registry::Get().GetComponent<Component::Transform>(player);
		Component::Transform& trTr = Registry::Get().GetComponent<Component::Transform>(tranquilizerWave);

		if (HBL::InputManager::GetKeyDown(GLFW_KEY_SPACE))
		{
			if (pDir.Left)
			{
				trTr.position.x = pTr.position.x - 70.f;
				trTr.position.y = pTr.position.y;
				trTr.scale.x = 90.f;
				trTr.scale.y = 30.f;
			}
			else if (pDir.Right)
			{
				trTr.position.x = pTr.position.x + 70.f;
				trTr.position.y = pTr.position.y;
				trTr.scale.x = 90.f;
				trTr.scale.y = 30.f;
			}
			else if (pDir.Down)
			{
				trTr.position.x = pTr.position.x;
				trTr.position.y = pTr.position.y - 70.f;
				trTr.scale.x = 30.f;
				trTr.scale.y = 90.f;
			}
			else if (pDir.Up)
			{
				trTr.position.x = pTr.position.x;
				trTr.position.y = pTr.position.y + 70.f;
				trTr.scale.x = 30.f;
				trTr.scale.y = 90.f;
			}

			Registry::Get().GetComponent<Component::CollisionBox>(tranquilizerWave).Enabled = true;
			Registry::Get().GetComponent<Component::SpriteRenderer>(tranquilizerWave).Enabled = true;
		}
		else
		{
			Registry::Get().GetComponent<Component::CollisionBox>(tranquilizerWave).Enabled = false;
			Registry::Get().GetComponent<Component::SpriteRenderer>(tranquilizerWave).Enabled = false;
		}
	}
};