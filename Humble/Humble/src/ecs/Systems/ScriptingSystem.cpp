#include "ScriptingSystem.h"

//void ScriptingSystem::Start(int current_level)
//{
//	ENGINE_PROFILE("ScriptingSystem::Start");
//
//	for (uint32_t i = 0; i < Script.size(); i++) {
//		if (Script.at(i).Enabled) {
//			if (current_level == 0) {
//				Script.at(i).init[0](1.0f);
//				continue;
//			}
//
//			int size = Script.at(i).init.size();
//			if (current_level < size)
//				Script.at(i).init[current_level](1.0f);
//			else
//				Script.at(i).init[size - 1](1.0f);
//		}
//	}
//}
//
//void ScriptingSystem::Run(int current_level)
//{
//	//ENGINE_PROFILE("ScriptingSystem::Run");
//
//	for (uint32_t i = 0; i < Script.size(); i++) {
//		if (Script.at(i).Enabled) {
//			int size = Script.at(i).update.size();
//			if (current_level <= size)
//				Script.at(i).update[current_level - 1](1.0f);
//			else
//				Script.at(i).update[size - 1](1.0f);
//		}
//	}
//}

void ScriptingSystem::Start(int current_level)
{
	ENGINE_PROFILE("ScriptingSystem::Start");

	for (uint32_t i = 0; i < Script.size(); i++) {
		if (Script.at(i).Enabled) {
			/*int size = Script.at(i).init.size();
			if (current_level < size)
				Script.at(i).init[current_level](1.0f);
			else
				Script.at(i).init[size - 1](1.0f);*/
			////////////////////////////////////////////
			int size = Script.at(i).script.size();
			if (current_level < size)
				Script.at(i).script[current_level]->Init();
			else
				Script.at(i).script[size - 1]->Init();
		}
	}
}

void ScriptingSystem::Run(int current_level)
{
	//ENGINE_PROFILE("ScriptingSystem::Run");

	for (uint32_t i = 0; i < Script.size(); i++) {
		if (Script.at(i).Enabled) {
			/*int size = Script.at(i).update.size();
			if (current_level < size)
				Script.at(i).update[current_level](1.0f);
			else
				Script.at(i).update[size - 1](1.0f);*/
			//////////////////////////////////////////////
			int size = Script.at(i).script.size();
			if (current_level < size)
				Script.at(i).script[current_level]->Update();
			else
				Script.at(i).script[size - 1]->Update();
		}
	}
}

void ScriptingSystem::Clear()
{
}
