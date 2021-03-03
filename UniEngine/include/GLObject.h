#pragma once
#include "UniEngineAPI.h"
namespace UniEngine {
	class UNIENGINE_API GLObject
	{
	protected:
		GLuint m_id = 0;
	public:
		[[nodiscard]] GLuint Id() const;
		virtual ~GLObject();
	};
}