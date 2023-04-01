#include "SpriteRendererSystem.h"

void HBL::SpriteRendererSystem::Start()
{
	FUNCTION_PROFILE();

	std::string shaderName = "";

	if (SceneManager::Get().GetCurrentScene() == 1)
	{
		shaderName = "res/shaders/BasicLighting.shader";
	}
	else
	{
		shaderName = "res/shaders/Basic.shader";
	}

	Renderer::Get().AddBatch(shaderName, (Registry::Get().GetEntities().size() * 4), SceneManager::Get().GetMainCamera());
	
	TextureManager::Get().InitTransparentTexture();

	Registry::Get().Group<Component::Transform, Component::SpriteRenderer>().ForEach([&](IEntity& entt)
	{
		Component::Transform& transform = Registry::Get().GetComponent<Component::Transform>(entt);
		Component::SpriteRenderer& sprite = Registry::Get().GetComponent<Component::SpriteRenderer>(entt);

		if (transform.Enabled)
		{
			sprite.bufferIndex = Renderer::Get().GetVertexBuffer(0).m_Index;
			transform.bufferIndex = Renderer::Get().GetVertexBuffer(0).m_Index;
			Renderer::Get().RegisterQuad(0, transform);
		}

		if (sprite.texture != "-")
		{
			if (sprite.pixelData != nullptr)
				TextureManager::Get().Find(sprite.texture, &sprite);
			else
				TextureManager::Get().Find(sprite.texture);
		}
	}).Run();
}

void HBL::SpriteRendererSystem::Run(float dt)
{
	//FUNCTION_PROFILE();

	Registry::Get().View<Component::SpriteRenderer>().ForEach([&](Component::SpriteRenderer& sprite)
	{
		if (sprite.Enabled)
		{
			if (sprite.pixelData != nullptr)
			{
				Renderer::Get().UpdateQuad(0, sprite.bufferIndex, sprite.color, TextureManager::Get().Find(sprite.texture, &sprite));
			}
			else if (sprite.coords == glm::vec2(-1.0f, -1.0f) && sprite.spriteSize == glm::vec2(-1.0f, -1.0f))
			{
				Renderer::Get().UpdateQuad(0, sprite.bufferIndex, sprite.color, TextureManager::Get().Find(sprite.texture));
			}
			else
			{
				float id = TextureManager::Get().Find(sprite.texture);
				glm::vec2& textureCoords = TextureManager::Get().GetTextureSize().at(id);
				Renderer::Get().UpdateQuad(0, sprite.bufferIndex, sprite.color, id, sprite.coords, textureCoords, sprite.spriteSize);
			}
		}
		else
		{
			glm::vec4 transparentColor(1.f, 1.f, 1.f, 0.f);
			Renderer::Get().UpdateQuad(0, sprite.bufferIndex, transparentColor, TextureManager::Get().GetTextureSlot()[0]);
		}
	}).Run();

	for (uint32_t i = 0; i < TextureManager::Get().GetTextureIndex(); i++)
	{
		glBindTextureUnit(i, TextureManager::Get().GetTextureSlot()[i]);
	}
}

void HBL::SpriteRendererSystem::Clear()
{
	FUNCTION_PROFILE();

	TextureManager::Get().GetTextureMap().clear();
	TextureManager::Get().GetTextureSize().clear();

	TextureManager::Get().GetTextureIndex() = 0;

	Registry::Get().ClearArray<Component::SpriteRenderer>();
	glDeleteTextures(32, TextureManager::Get().GetTextureSlot());
}
