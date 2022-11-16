#pragma once

#include "../HumbleAPI.h"
#include "../ECS/ISystem.h"

#include "../Core.h"
#include "../Utilities.h"
#include "../ECS/Group.h"
#include "../GlobalArrays.h"
#include "../ECS/Components.h"
#include "../Rendering/Renderer.h"
#include "../Managers/TextureManager.h"

#include <vector>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace HBL
{
	class HBL_API SpriteRendererSystem final : public ISystem
	{
	public:
		virtual void Start() override;
		virtual void Run(float dt) override;
		virtual void Clear() override;

		void InitVertexBuffer();
	};
}