#pragma once
#include "Misc.h"
namespace UniEngine {
	class Entity;
	class UECORE_API SharedComponentBase {
	public:
		virtual size_t GetHashCode() = 0;
	};
}