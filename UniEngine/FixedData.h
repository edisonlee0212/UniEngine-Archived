#pragma once
#include "Math.h"
#include "Misc.h"
namespace UniEngine {
	struct Translation {
		float3 value;
	};
	struct Scale {
		float3 value;
	};
	struct Rotation {
		float4 value;
	};
	struct LocalPosition
	{
		float3 value;
	};
	struct LocalScale {
		float3 value;
	};
	struct LocalRotation {
		float4 value;
	};
	struct LocalToWorld {
		float4x4 value;
	};
	struct LocalToParent {
		float4x4 value;
	};
}