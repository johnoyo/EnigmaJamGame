#pragma once

#include "UUID.h"

#include <stdint.h>

namespace HBL
{
	struct IEntity
	{
		UUID uuid = 0LU;
		bool Enabled = true;
	};
}