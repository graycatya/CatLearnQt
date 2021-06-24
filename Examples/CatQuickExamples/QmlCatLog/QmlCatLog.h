#pragma once
#include "CatLog_Sington.h"
#include <QObject>
#include <QString>

namespace QMLCATLOG
{

    class CatLog : public QObject
    {
        Q_OBJECT
        public:
            static CatLog* Instance() noexcept
            {
                if(_instance == nullptr)
                {
                    std::unique_lock<std::mutex>lock(*m_pMutex);
                    if(_instance == nullptr)
                    {
                        _instance = new CatLog();
                        CATLOG::CatLog::Instance();
                    }
                }
                return _instance;
            }

            static void Delete( void ) noexcept
            {
                if(_instance != nullptr)
                {
                    CATLOG::CatLog::Delete();
                    delete _instance;
                    _instance = nullptr;
                }
            }
            Q_INVOKABLE void debug_file(QString path_file, QString msg = "") noexcept
            {
                QString file = path_file;
                CATLOG::CatLog::__Write_Log(path_file.toStdString(), DEBUG_LOG_T(msg.toStdString()));
            }

            Q_INVOKABLE void info_file(QString path_file, QString msg = "") noexcept
            {
                QString file = path_file;
                CATLOG::CatLog::__Write_Log(path_file.toStdString(), INFO_LOG_T(msg.toStdString()));
            }

            Q_INVOKABLE void warn_file(QString path_file, QString msg = "") noexcept
            {
                QString file = path_file;
                CATLOG::CatLog::__Write_Log(path_file.toStdString(), WARN_LOG_T(msg.toStdString()));
            }

            Q_INVOKABLE void error_file(QString path_file, QString msg = "") noexcept
            {
                QString file = path_file;
                CATLOG::CatLog::__Write_Log(path_file.toStdString(), ERROR_LOG_T(msg.toStdString()));
            }

            Q_INVOKABLE void alarm_file(QString path_file, QString msg = "") noexcept
            {
                QString file = path_file;
                CATLOG::CatLog::__Write_Log(path_file.toStdString(), ALARM_LOG_T(msg.toStdString()));
            }

            Q_INVOKABLE void fatal_file(QString path_file, QString msg = "") noexcept
            {
                QString file = path_file;
                CATLOG::CatLog::__Write_Log(path_file.toStdString(), FATAL_LOG_T(msg.toStdString()));
            }

            Q_INVOKABLE void debug_print(QString msg = "") noexcept
            {
                CATLOG::CatLog::__Write_Log(DEBUG_LOG_T(msg.toStdString()));
            }

            Q_INVOKABLE void info_print(QString msg = "") noexcept
            {
                CATLOG::CatLog::__Write_Log(INFO_LOG_T(msg.toStdString()));
            }

            Q_INVOKABLE void warn_print(QString msg = "") noexcept
            {
                CATLOG::CatLog::__Write_Log(WARN_LOG_T(msg.toStdString()));
            }

            Q_INVOKABLE void error_print(QString msg = "") noexcept
            {
                CATLOG::CatLog::__Write_Log(ERROR_LOG_T(msg.toStdString()));
            }

            Q_INVOKABLE void alarm_print(QString msg = "") noexcept
            {
                CATLOG::CatLog::__Write_Log(ALARM_LOG_T(msg.toStdString()));
            }

            Q_INVOKABLE void fatal_print(QString msg = "") noexcept
            {
                CATLOG::CatLog::__Write_Log(FATAL_LOG_T(msg.toStdString()));
            }

        private: 
            CatLog() {}
            ~CatLog() {}
            CatLog(const CatLog*)  = delete;

        private:
            static CatLog* _instance;
            static std::mutex* m_pMutex;

    };

};
