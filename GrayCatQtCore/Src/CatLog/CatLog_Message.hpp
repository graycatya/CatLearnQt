#ifndef CATLOG_MESSAGE_H
#define CATLOG_MESSAGE_H

#include<iostream>
#include<sstream>
#include<string>
#include<chrono>
#include<thread>
#include<initializer_list>
#include<time.h>


#define DEBUG_LOG(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_DEBUG, TID::OFF>::Log_Head({ _MSG }) )
#define INFO_LOG(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_INFO, TID::OFF>::Log_Head({ _MSG }) )
#define WARN_LOG(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_WARN, TID::OFF>::Log_Head({ _MSG }) )
#define ERROR_LOG(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_ERROR, TID::OFF>::Log_Head({ _MSG }) )
#define ALARM_LOG(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_ALARM, TID::OFF>::Log_Head({ _MSG }) )
#define FATAL_LOG(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_FATAL, TID::OFF>::Log_Head({ _MSG }) )

#define DEBUG_LOG_T(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_DEBUG, TID::YES>::Log_Head({ _MSG }) )
#define INFO_LOG_T(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_INFO, TID::YES>::Log_Head({ _MSG }) )
#define WARN_LOG_T(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_WARN, TID::YES>::Log_Head({ _MSG }) )
#define ERROR_LOG_T(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_ERROR, TID::YES>::Log_Head({ _MSG }) )
#define ALARM_LOG_T(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_ALARM, TID::YES>::Log_Head({ _MSG }) )
#define FATAL_LOG_T(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_FATAL, TID::YES>::Log_Head({ _MSG }) )

#define _DEBUG_HEAD ( LOG_MESSAGE<CATLOG_LEVEL::CAT_DEBUG, TID::OFF>::Log_Head({ __FUNCTION__, std::to_string(__LINE__) }) )
#define _INFO_HEAD ( LOG_MESSAGE<CATLOG_LEVEL::CAT_INFO, TID::OFF>::Log_Head({ __FUNCTION__, std::to_string(__LINE__) }) )
#define _WARN_HEAD ( LOG_MESSAGE<CATLOG_LEVEL::CAT_WARN, TID::OFF>::Log_Head({ __FUNCTION__, std::to_string(__LINE__) }) )
#define _ERROR_HEAD ( LOG_MESSAGE<CATLOG_LEVEL::CAT_ERROR, TID::OFF>::Log_Head({ __FUNCTION__, std::to_string(__LINE__) }) )
#define _ALARM_HEAD ( LOG_MESSAGE<CATLOG_LEVEL::CAT_ALARM, TID::OFF>::Log_Head({ __FUNCTION__, std::to_string(__LINE__) }) )
#define _FATAL_HEAD ( LOG_MESSAGE<CATLOG_LEVEL::CAT_FATAL, TID::OFF>::Log_Head({ __FUNCTION__, std::to_string(__LINE__) }) )

#define _DEBUG_HEAD_T ( LOG_MESSAGE<CATLOG_LEVEL::CAT_DEBUG, TID::YES>::Log_Head({ __FUNCTION__, std::to_string(__LINE__) }) )
#define _INFO_HEAD_T ( LOG_MESSAGE<CATLOG_LEVEL::CAT_INFO, TID::YES>::Log_Head({ __FUNCTION__, std::to_string(__LINE__) }) )
#define _WARN_HEAD_T ( LOG_MESSAGE<CATLOG_LEVEL::CAT_WARN, TID::YES>::Log_Head({ __FUNCTION__, std::to_string(__LINE__) }) )
#define _ERROR_HEAD_T ( LOG_MESSAGE<CATLOG_LEVEL::CAT_ERROR, TID::YES>::Log_Head({ __FUNCTION__, std::to_string(__LINE__) }) )
#define _ALARM_HEAD_T ( LOG_MESSAGE<CATLOG_LEVEL::CAT_ALARM, TID::YES>::Log_Head({ __FUNCTION__, std::to_string(__LINE__) }) )
#define _FATAL_HEAD_T ( LOG_MESSAGE<CATLOG_LEVEL::CAT_FATAL, TID::YES>::Log_Head({ __FUNCTION__, std::to_string(__LINE__) }) )

#define _DEBUG_LOG(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_DEBUG, TID::OFF>::Log_Head({ __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define _INFO_LOG(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_INFO, TID::OFF>::Log_Head({ __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define _WARN_LOG(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_WARN, TID::OFF>::Log_Head({ __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define _ERROR_LOG(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_ERROR, TID::OFF>::Log_Head({ __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define _ALARM_LOG(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_ALARM, TID::OFF>::Log_Head({ __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define _FATAL_LOG(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_FATAL, TID::OFF>::Log_Head({ __FUNCTION__, std::to_string(__LINE__), _MSG }) )

#define _DEBUG_LOG_T(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_DEBUG, TID::YES>::Log_Head({ __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define _INFO_LOG_T(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_INFO, TID::YES>::Log_Head({ __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define _WARN_LOG_T(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_WARN, TID::YES>::Log_Head({ __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define _ERROR_LOG_T(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_ERROR, TID::YES>::Log_Head({ __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define _ALARM_LOG_T(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_ALARM, TID::YES>::Log_Head({ __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define _FATAL_LOG_T(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_FATAL, TID::YES>::Log_Head({ __FUNCTION__, std::to_string(__LINE__), _MSG }) )

#define __DEBUG_HEAD ( LOG_MESSAGE<CATLOG_LEVEL::CAT_DEBUG, TID::OFF>::Log_Head({ __FILE__,  __FUNCTION__, std::to_string(__LINE__) }) )
#define __INFO_HEAD ( LOG_MESSAGE<CATLOG_LEVEL::CAT_INFO, TID::OFF>::Log_Head({ __FILE__,  __FUNCTION__, std::to_string(__LINE__) }) )
#define __WARN_HEAD ( LOG_MESSAGE<CATLOG_LEVEL::CAT_WARN, TID::OFF>::Log_Head({ __FILE__,  __FUNCTION__, std::to_string(__LINE__) }) )
#define __ERROR_HEAD ( LOG_MESSAGE<CATLOG_LEVEL::CAT_ERROR, TID::OFF>::Log_Head({ __FILE__,  __FUNCTION__, std::to_string(__LINE__) }) )
#define __ALARM_HEAD ( LOG_MESSAGE<CATLOG_LEVEL::CAT_ALARM, TID::OFF>::Log_Head({ __FILE__,  __FUNCTION__, std::to_string(__LINE__) }) )
#define __FATAL_HEAD ( LOG_MESSAGE<CATLOG_LEVEL::CAT_FATAL, TID::OFF>::Log_Head({ __FILE__,  __FUNCTION__, std::to_string(__LINE__) }) )

#define __DEBUG_HEAD_T ( LOG_MESSAGE<CATLOG_LEVEL::CAT_DEBUG, TID::YES>::Log_Head({ __FILE__,  __FUNCTION__, std::to_string(__LINE__) }) )
#define __INFO_HEAD_T ( LOG_MESSAGE<CATLOG_LEVEL::CAT_INFO, TID::YES>::Log_Head({ __FILE__,  __FUNCTION__, std::to_string(__LINE__) }) )
#define __WARN_HEAD_T ( LOG_MESSAGE<CATLOG_LEVEL::CAT_WARN, TID::YES>::Log_Head({ __FILE__,  __FUNCTION__, std::to_string(__LINE__) }) )
#define __ERROR_HEAD_T ( LOG_MESSAGE<CATLOG_LEVEL::CAT_ERROR, TID::YES>::Log_Head({ __FILE__,  __FUNCTION__, std::to_string(__LINE__) }) )
#define __ALARM_HEAD_T ( LOG_MESSAGE<CATLOG_LEVEL::CAT_ALARM, TID::YES>::Log_Head({ __FILE__,  __FUNCTION__, std::to_string(__LINE__) }) )
#define __FATAL_HEAD_T ( LOG_MESSAGE<CATLOG_LEVEL::CAT_FATAL, TID::YES>::Log_Head({ __FILE__,  __FUNCTION__, std::to_string(__LINE__) }) )

#define __DEBUG_LOG(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_DEBUG, TID::OFF>::Log_Head({ __FILE__, __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define __INFO_LOG(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_INFO, TID::OFF>::Log_Head({ __FILE__, __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define __WARN_LOG(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_WARN, TID::OFF>::Log_Head({ __FILE__, __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define __ERROR_LOG(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_ERROR, TID::OFF>::Log_Head({ __FILE__, __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define __ALARM_LOG(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_ALARM, TID::OFF>::Log_Head({ __FILE__, __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define __FATAL_LOG(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_FATAL, TID::OFF>::Log_Head({ __FILE__, __FUNCTION__, std::to_string(__LINE__), _MSG }) )

#define __DEBUG_LOG_T(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_DEBUG, TID::YES>::Log_Head({ __FILE__, __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define __INFO_LOG_T(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_INFO, TID::YES>::Log_Head({ __FILE__, __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define __WARN_LOG_T(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_WARN, TID::YES>::Log_Head({ __FILE__, __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define __ERROR_LOG_T(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_ERROR, TID::YES>::Log_Head({ __FILE__, __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define __ALARM_LOG_T(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_ALARM, TID::YES>::Log_Head({ __FILE__, __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define __FATAL_LOG_T(_MSG) ( LOG_MESSAGE<CATLOG_LEVEL::CAT_FATAL, TID::YES>::Log_Head({ __FILE__, __FUNCTION__, std::to_string(__LINE__), _MSG }) )

enum class CATLOG_LEVEL : int { CAT_DEBUG = 0, CAT_INFO, CAT_WARN, CAT_ERROR, CAT_ALARM, CAT_FATAL };
enum class TID : int { OFF = 0, YES };

template<CATLOG_LEVEL level, TID tid>
struct LOG_MESSAGE{
    static std::string Get_Level() noexcept
    {
        std::string leve = "";
        switch(level)
        {
            case CATLOG_LEVEL::CAT_DEBUG:
                leve = "DEBUG"; break;
            case CATLOG_LEVEL::CAT_INFO:
                leve = "INFO"; break;
            case CATLOG_LEVEL::CAT_WARN:
                leve = "WARN"; break;
            case CATLOG_LEVEL::CAT_ERROR:
                leve = "ERROR"; break;
            case CATLOG_LEVEL::CAT_ALARM:
                leve = "ALARM"; break;
            case CATLOG_LEVEL::CAT_FATAL:
                leve = "FATAL"; break;
        }
        return leve;
    }

    static std::string Log_Head(std::initializer_list<std::string> log_msg) noexcept
    {
            std::string log_head = "";
            auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            struct tm ptm;
#if !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
    localtime_s(&ptm, &tt);
#else
    ptm = *std::localtime(&tt);
#endif

            char date[60] = {0};
            sprintf(date, "%d-%02d-%02d %02d:%02d:%02d",
                ptm.tm_year + 1900, ptm.tm_mon + 1, ptm.tm_mday,
                ptm.tm_hour, ptm.tm_min, ptm.tm_sec);
            log_head = std::string(date) + " | " + Get_Level();
            switch (tid) {
                case TID::YES:{
                    std::ostringstream id;
                    id << "tid: " << std::this_thread::get_id();
                    log_head = log_head + " | " + id.str();
                    break;
                }
                default:{
                    break;
                }
            }
            for(auto &msg : log_msg)
            {
                log_head += " | ";
                log_head += msg;
            }
            return log_head;
    }
};

#endif
