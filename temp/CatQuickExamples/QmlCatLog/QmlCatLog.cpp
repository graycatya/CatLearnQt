#include "QmlCatLog.h"

QMLCATLOG::CatLog* QMLCATLOG::CatLog::_instance = nullptr;
std::mutex* QMLCATLOG::CatLog::m_pMutex = new std::mutex;