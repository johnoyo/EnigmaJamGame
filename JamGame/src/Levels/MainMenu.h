#pragma once

#include "Humble.h"
#include "..\MyComponents.h"

#include "..\Scripts\PlayerScript.h"
#include "..\Scripts\EnemyScript.h"

namespace HBL 
{
	class MainMenu final : public IScene
	{
	public:
		virtual void OnAttach() override;
		virtual void OnCreate() override;
		virtual void OnDetach() override;

	private:
		HBL::IEntity m_Camera;
		HBL::IEntity m_PlayButton;
	};
}

