#include "pch.h"
#include "ILogger.h"
#include "TLogger.h"

LOGGER_DLL ILogger* CreateLoger()
{
	return new TLogger();
}
