#pragma once
#include "../Core.h"
#include "../Header.h"
#include "../Utilities.h"
#include "RenderingSystem.h"
#include <vector>
#include <iostream>
#include "stb_image/stb_image.h"

namespace HBL {

	class TextureSystem {
	public:
		void Start();
		void Run(VertexBuffer& buffer);
		void Clear();

	private:
		uint32_t texture_slot[32] = { 0 };

		uint32_t current_index = 0;
		std::vector<std::string> map;
		std::vector<glm::vec2> size;
		void Init_Transparent_Texture();
		void Load_Texture(const std::string& path);
		float Find(const std::string& path);


	};

}