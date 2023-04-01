#pragma once

#include "Humble.h"
#include "..\MyComponents.h"

using namespace HBL;

class EndScreen final : public IScene
{
public:
	virtual void OnAttach() override;
	virtual void OnCreate() override;
	virtual void OnDetach() override;

private:
	IEntity m_Camera;
	IEntity m_Background;
};
