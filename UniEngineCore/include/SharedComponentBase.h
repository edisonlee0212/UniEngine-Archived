#pragma once
#include "Misc.h"
namespace UniEngine {
	class Entity;
	class SharedComponentBase {
	public:
		virtual size_t GetHashCode() = 0;
	};
}