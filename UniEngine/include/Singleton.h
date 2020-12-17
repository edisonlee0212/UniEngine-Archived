#pragma once
#include "UniEngineAPI.h"
namespace UniEngine
{
	template<typename T>
	class UNIENGINE_API Singleton
	{
	protected:
		Singleton() = default;
		Singleton(Singleton&&) = default;
		Singleton(const Singleton&) = default;
		Singleton& operator=(Singleton&&) = default;
		Singleton& operator=(const Singleton&) = default;
	public:
		static T& GetInstance()
		{
			static T instance;
			return instance;
		}
	};
}