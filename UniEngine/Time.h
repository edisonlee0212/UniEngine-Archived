#pragma once
namespace UniEngine {
	class Time
	{
	private:
		static double _WorldTime;
		static double _FixedDeltaTime;
		static double _DeltaTime;
		static double _LastFrameTime;
		friend class TimeSystem;
		friend class World;
		static void AddWorldTime(double value);
		static void AddFixedDeltaTime(double value);
		static void SetWorldTime(double value);
		static void SetFixedDeltaTime(double value);
		static void SetDeltaTime(double value);
		static void SetLastFrameTime(double value);
	public:
		static double WorldTime();
		static double FixedDeltaTime();
		static double DeltaTime();
		static double LastFrameTime();
	};

}