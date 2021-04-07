#pragma once
#include "UniEngine.h"
using namespace UniEngine;
namespace Galaxy {
	/// <summary>
	/// The calculated precise position of the star.
	/// </summary>
	struct StarPosition : ComponentDataBase
	{
		glm::dvec3 Value;
	};
	struct SelectionStatus : ComponentDataBase
	{
		int Value;
	};
	/// <summary>
	/// The seed of the star, use this to calculate initial position.
	/// </summary>
	struct StarSeed : ComponentDataBase
	{

		float Value;
	};
	/// <summary>
	/// This keep track of the position of the star in the list.
	/// </summary>
	struct StarIndex : ComponentDataBase
	{
		int Value;
	};
	/// <summary>
	/// Original color of the star
	/// </summary>
	struct OriginalColor : ComponentDataBase
	{
		glm::vec4 Value;
	};
	/// <summary>
	/// The deviation of its orbit
	/// </summary>
	struct StarOrbitOffset : ComponentDataBase
	{
		glm::dvec3 Value;
	};
	/// <summary>
	/// This will help calculate the orbit. Smaller = close to center, bigger = close to disk
	/// </summary>
	struct StarOrbitProportion : ComponentDataBase
	{
		double Value;
	};
	/// <summary>
	/// This will help calculate the orbit. Smaller = close to center, bigger = close to disk
	/// </summary>
	struct SurfaceColor : ComponentDataBase
	{
		glm::vec4 Value;
	};
	/// <summary>
	/// The actual display color after selection system.
	/// </summary>
	struct DisplayColor : ComponentDataBase
	{
		glm::vec4 Value;
	};

	struct StarOrbit : ComponentDataBase
	{
		double A;
		double B;
		double TiltY;
		double TiltX;
		double TiltZ;
		double SpeedMultiplier;
		glm::dvec3 Center;
		[[nodiscard]] glm::dvec3 GetPoint(const glm::dvec3& orbitOffset, const double& time, const bool& isStar = true) const
		{
			const double angle = isStar ? time / glm::sqrt(A + B) * SpeedMultiplier : time;

			glm::dvec3 point;
			point.x = glm::sin(glm::radians(angle)) * A + orbitOffset.x;
			point.y = orbitOffset.y;
			point.z = glm::cos(glm::radians(angle)) * B + orbitOffset.z;
			
			point = Rotate(glm::angleAxis(glm::radians(TiltX), glm::dvec3(1, 0, 0)), point);
			point = Rotate(glm::angleAxis(glm::radians(TiltY), glm::dvec3(0, 1, 0)), point);
			point = Rotate(glm::angleAxis(glm::radians(TiltZ), glm::dvec3(0, 0, 1)), point);

			point.x += Center.x;
			point.y += Center.y;
			point.z += Center.z;
			return point;
		}

		static glm::dvec3 Rotate(const glm::qua<double>& rotation, const glm::dvec3& point)
		{
			const double x = rotation.x * 2.0;
			const double y = rotation.y * 2.0;
			const double z = rotation.z * 2.0;
			const double xx = rotation.x * x;
			const double yy = rotation.y * y;
			const double zz = rotation.z * z;
			const double xy = rotation.x * y;
			const double xz = rotation.x * z;
			const double yz = rotation.y * z;
			const double wx = rotation.w * x;
			const double wy = rotation.w * y;
			const double wz = rotation.w * z;
			glm::dvec3 res;
			res.x = (1.0 - (yy + zz)) * point.x + (xy - wz) * point.y + (xz + wy) * point.z;
			res.y = (xy + wz) * point.x + (1.0 - (xx + zz)) * point.y + (yz - wx) * point.z;
			res.z = (xz - wy) * point.x + (yz + wx) * point.y + (1.0 - (xx + yy)) * point.z;
			return res;
		}
	};
	/// <summary>
	/// The star cluster it actually belongs to.
	/// </summary>
	struct StarClusterIndex : ComponentDataBase
	{
		int Value;
	};

	class StarClusterPattern : public PrivateComponentBase
	{
	public:
		StarClusterIndex Index;
		double YSpread;
		double XZSpread;

		double DiskAB;
		double DiskEccentricity;
		double DiskA;
		double DiskB;

		double CoreProportion;
		double CoreAB;
		double CoreEccentricity;
		double CoreA;
		double CoreB;

		double CenterAB;
		double CenterEccentricity;
		double CenterA;
		double CenterB;


		double DiskSpeed;
		double CoreSpeed;
		double CenterSpeed;

		double DiskTiltX;
		double DiskTiltZ;
		double CoreTiltX;
		double CoreTiltZ;
		double CenterTiltX;
		double CenterTiltZ;

		glm::vec4 DiskColor;
		glm::vec4 CoreColor;
		glm::vec4 CenterColor;

		double Rotation;
		glm::dvec3 CenterPosition;
		void SetAB()
		{
			DiskA = DiskAB * DiskEccentricity;
			DiskB = DiskAB * (1 - DiskEccentricity);
			CenterA = CenterAB * CenterEccentricity;
			CenterB = CenterAB * (1 - CenterEccentricity);
			CoreAB = CenterAB / 2 + CenterAB / 2 +
				((DiskA + DiskB) - CenterAB / 2 - CenterAB / 2)
				* CoreProportion;
			CoreA = CoreAB * CoreEccentricity;
			CoreB = CoreAB * (1 - CoreEccentricity);


		}

		/// <summary>
		/// Set the ellipse by the proportion.
		/// </summary>
		/// <param name="proportion">
		/// The position of the ellipse in the density waves, range is from 0 to 1
		/// </param>
		/// <param name="orbit">
		/// The ellipse will be reset by the proportion and the density wave properties.
		/// </param>
		StarOrbit GetOrbit(double starOrbitProportion)
		{
			StarOrbit orbit;
			if (starOrbitProportion > CoreProportion)
			{
				//If the wave is outside the disk;
				double actualProportion = (starOrbitProportion - CoreProportion) / (1 - CoreProportion);
				orbit.A = (float)(CoreA + (DiskA - CoreA) * actualProportion);
				orbit.B = (float)(CoreB + (DiskB - CoreB) * actualProportion);
				orbit.TiltX = CoreTiltX - (CoreTiltX - DiskTiltX) * actualProportion;
				orbit.TiltZ = CoreTiltZ - (CoreTiltZ - DiskTiltZ) * actualProportion;
				orbit.SpeedMultiplier = CoreSpeed + (DiskSpeed - CoreSpeed) * actualProportion;
			}
			else
			{
				double actualProportion = starOrbitProportion / CoreProportion;
				orbit.A = (float)(CenterA + (CoreA - CenterA) * actualProportion);
				orbit.B = (float)(CenterB + (CoreB - CenterB) * actualProportion);
				orbit.TiltX = CenterTiltX - (CenterTiltX - CoreTiltX) * actualProportion;
				orbit.TiltZ = CenterTiltZ - (CenterTiltZ - CoreTiltZ) * actualProportion;
				orbit.SpeedMultiplier = CenterSpeed + (CoreSpeed - CenterSpeed) * actualProportion;
			}
			orbit.TiltY = -Rotation * starOrbitProportion;
			orbit.Center = CenterPosition * (1 - starOrbitProportion);
			return orbit;
		}

		StarOrbitOffset GetOrbitOffset(double proportion)
		{
			double offset;
			offset = glm::sqrt(1 - proportion);
			StarOrbitOffset orbitOffset;
			glm::dvec3 d3;
			d3.y = glm::gaussRand(0.0, 1.0) * (DiskA + DiskB) * YSpread;
			d3.x = glm::gaussRand(0.0, 1.0) * (DiskA + DiskB) * XZSpread;
			d3.z = glm::gaussRand(0.0, 1.0) * (DiskA + DiskB) * XZSpread;
			orbitOffset.Value = d3;
			return orbitOffset;
		}

		glm::vec4 GetColor(double proportion)
		{
			glm::vec4 color = glm::vec4();
			if (proportion > CoreProportion)
			{
				//If the wave is outside the disk;
				double actualProportion = (proportion - CoreProportion) / (1 - CoreProportion);
				color = CoreColor * (1 - (float)actualProportion) + DiskColor * (float)actualProportion;
			}
			else
			{
				double actualProportion = proportion / CoreProportion;
				color = CoreColor * (float)actualProportion + CenterColor * (1 - (float)actualProportion);
			}
			color = glm::normalize(color);
			return color;
		}

		StarOrbit GetOrbit(glm::vec3 position)
		{
			return StarOrbit();
		}
	};

	class StarClusterSystem :
		public SystemBase
	{
		EntityArchetype _StarClusterArchetype;
		Entity _StarClusterFront;
		Entity _StarClusterBack;
		std::vector<StarClusterPattern*> _Patterns;
		EntityQuery _StarQuery;
		EntityArchetype _StarArchetype;


		bool _UseFront = true;
		
		float _ApplyPositionTimer;
		float _CopyPositionTimer;
		float _CalcPositionTimer;
		float _CalcPositionResult;
		float _Speed = 0.0f;
		float _Size = 0.1f;
		float _GalaxyTime = 0.0f;
		std::future<void> _CurrentStatus;
		bool _FirstTime = true;
	public:
		void CalculateStarPositionAsync();
		void CalculateStarPositionSync();
		void SetRenderers();
		void LateUpdate() override;
		void OnCreate() override;
		void Update() override;
		void FixedUpdate() override;
		void OnStartRunning() override;
	};
}

