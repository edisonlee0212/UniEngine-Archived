#pragma once
namespace UniEngine {
	class SystemBase
	{
	public:
		SystemBase() { _Enabled = false; }
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnStartRunning() {}
		virtual void OnStopRuning() {}
		virtual void Update() {};
		virtual void FixedUpdate() {};
		void Enable() {
			if (!_Enabled) {
				_Enabled = true;
				OnStartRunning();
			}
		}
		void Disable() {
			if (_Enabled) {
				_Enabled = false;
				OnStopRuning();
			}
		}

		bool IsEnabled() {
			return _Enabled;
		}

	public:
		bool _Enabled;
	};
}

