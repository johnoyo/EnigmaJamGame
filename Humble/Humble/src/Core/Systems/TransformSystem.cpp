#include "TransformSystem.h"

namespace HBL {

	void TransformSystem::Start()
	{
	}

	void TransformSystem::Run(VertexBuffer& buffer)
	{
		//ENGINE_PROFILE("TransformSystem::Run");

		for (uint32_t i = 0; i < Transform.size(); i++) {
			if (Transform.at(i).Static == false) {
				buffer.Update_Position_On_Quad(Transform.at(i).bufferIndex, Transform.at(i));
			}
		}
	}

	void TransformSystem::Update(VertexBuffer& buffer, std::vector<int>& entities_to_be_updated)
	{
		for (uint32_t i = 0; i < entities_to_be_updated.size(); i++) {
			buffer.Update_Position_On_Quad(Transform.at(entities_to_be_updated.at(i)).bufferIndex, Transform.at(entities_to_be_updated.at(i)));
		}
		entities_to_be_updated.clear();
	}

	void TransformSystem::Clear()
	{
		Transform.clear();
	}

}