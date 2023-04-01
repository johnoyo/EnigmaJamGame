#pragma once

using namespace HBL;

class EndScreenSystem final : public ISystem
{
public:

	virtual void Start() override
	{
		FUNCTION_PROFILE();
	}

	virtual void Run(float dt) override
	{
		if (SceneManager::Get().GetCurrentScene() == 2)
		{
			if (InputManager::GetKeyDown(GLFW_KEY_ENTER))
			{
				SceneManager::Get().LoadScene(0);
			}
		}
	}

	virtual void Clear() override
	{
		
	}
};