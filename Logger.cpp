#include "Logger.h"
#include <debugapi.h>

namespace {
	void Log(const std::string& message)
	{
		OutputDebugStringA(message.c_str());
	}
}