#pragma once
#include "Math.h"
#include "Misc.h"
namespace UniEngine {
	struct FixedData {

	};
	struct Translation : FixedData {
		float3 value;
	};
	struct Scale : FixedData {
		float3 value;
	};
	struct Rotation : FixedData {
		float4 value;
	};
	struct LocalPosition : FixedData
	{
		float3 value;
	};
	struct LocalScale : FixedData {
		float3 value;
	};
	struct LocalRotation : FixedData {
		float4 value;
	};
	struct LocalToWorld : FixedData {
		float4x4 value;
	};
	struct LocalToParent : FixedData {
		float4x4 value;
	};
}