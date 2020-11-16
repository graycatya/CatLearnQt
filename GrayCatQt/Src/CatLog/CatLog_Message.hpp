#pragma once

#include<iostream>
#include<string>
#include<chrono>
#include<initializer_list>

#define DEBUG_LOG(_MSG) ( LOG_MESSAGE<LEVEL::DEBUG>::Log_Head({ _MSG }) )
#define INFO_LOG(_MSG) ( LOG_MESSAGE<LEVEL::INFO>::Log_Head({ _MSG }) )
#define WARN_LOG(_MSG) ( LOG_MESSAGE<LEVEL::WARN>::Log_Head({ _MSG }) )
#define ERROR_LOG(_MSG) ( LOG_MESSAGE<LEVEL::ERROR>::Log_Head({ _MSG }) )
#define ALARM_LOG(_MSG) ( LOG_MESSAGE<LEVEL::ALARM>::Log_Head({ _MSG }) )
#define FATAL_LOG(_MSG) ( LOG_MESSAGE<LEVEL::FATAL>::Log_Head({ _MSG }) )

#define _DEBUG_HEAD ( LOG_MESSAGE<LEVEL::DEBUG>::Log_Head({ __FUNCTION__, std::to_string(__LINE__) }) )
#define _INFO_HEAD ( LOG_MESSAGE<LEVEL::INFO>::Log_Head({ __FUNCTION__, std::to_string(__LINE__) }) )
#define _WARN_HEAD ( LOG_MESSAGE<LEVEL::WARN>::Log_Head({ __FUNCTION__, std::to_string(__LINE__) }) )
#define _ERROR_HEAD ( LOG_MESSAGE<LEVEL::ERROR>::Log_Head({ __FUNCTION__, std::to_string(__LINE__) }) )
#define _ALARM_HEAD ( LOG_MESSAGE<LEVEL::ALARM>::Log_Head({ __FUNCTION__, std::to_string(__LINE__) }) )
#define _FATAL_HEAD ( LOG_MESSAGE<LEVEL::FATAL>::Log_Head({ __FUNCTION__, std::to_string(__LINE__) }) )

#define _DEBUG_LOG(_MSG) ( LOG_MESSAGE<LEVEL::DEBUG>::Log_Head({ __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define _INFO_LOG(_MSG) ( LOG_MESSAGE<LEVEL::INFO>::Log_Head({ __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define _WARN_LOG(_MSG) ( LOG_MESSAGE<LEVEL::WARN>::Log_Head({ __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define _ERROR_LOG(_MSG) ( LOG_MESSAGE<LEVEL::ERROR>::Log_Head({ __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define _ALARM_LOG(_MSG) ( LOG_MESSAGE<LEVEL::ALARM>::Log_Head({ __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define _FATAL_LOG(_MSG) ( LOG_MESSAGE<LEVEL::FATAL>::Log_Head({ __FUNCTION__, std::to_string(__LINE__), _MSG }) )

#define __DEBUG_HEAD ( LOG_MESSAGE<LEVEL::DEBUG>::Log_Head({ __FILE__,  __FUNCTION__, std::to_string(__LINE__) }) )
#define __INFO_HEAD ( LOG_MESSAGE<LEVEL::INFO>::Log_Head({ __FILE__,  __FUNCTION__, std::to_string(__LINE__) }) )
#define __WARN_HEAD ( LOG_MESSAGE<LEVEL::WARN>::Log_Head({ __FILE__,  __FUNCTION__, std::to_string(__LINE__) }) )
#define __ERROR_HEAD ( LOG_MESSAGE<LEVEL::ERROR>::Log_Head({ __FILE__,  __FUNCTION__, std::to_string(__LINE__) }) )
#define __ALARM_HEAD ( LOG_MESSAGE<LEVEL::ALARM>::Log_Head({ __FILE__,  __FUNCTION__, std::to_string(__LINE__) }) )
#define __FATAL_HEAD ( LOG_MESSAGE<LEVEL::FATAL>::Log_Head({ __FILE__,  __FUNCTION__, std::to_string(__LINE__) }) )

#define __DEBUG_LOG(_MSG) ( LOG_MESSAGE<LEVEL::DEBUG>::Log_Head({ __FILE__, __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define __INFO_LOG(_MSG) ( LOG_MESSAGE<LEVEL::INFO>::Log_Head({ __FILE__, __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define __WARN_LOG(_MSG) ( LOG_MESSAGE<LEVEL::WARN>::Log_Head({ __FILE__, __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define __ERROR_LOG(_MSG) ( LOG_MESSAGE<LEVEL::ERROR>::Log_Head({ __FILE__, __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define __ALARM_LOG(_MSG) ( LOG_MESSAGE<LEVEL::ALARM>::Log_Head({ __FILE__, __FUNCTION__, std::to_string(__LINE__), _MSG }) )
#define __FATAL_LOG(_MSG) ( LOG_MESSAGE<LEVEL::FATAL>::Log_Head({ __FILE__, __FUNCTION__, std::to_string(__LINE__), _MSG }) )

enum class LEVEL : int { DEBUG = 0, INFO, WARN, ERROR, ALARM, FATAL };

template<LEVEL level>
struct LOG_MESSAGE{
    static std::string Get_Level() noexcept
    {
        std::string leve = "";
        switch(level)
        {
            case LEVEL::DEBUG:
                leve = "DEBUG"; break;
            case LEVEL::INFO:
                leve = "INFO"; break;
            case LEVEL::WARN:
                leve = "WARN"; break;
            case LEVEL::ERROR:
                leve = "ERROR"; break;
            case LEVEL::ALARM:
                leve = "ALARM"; break;
            case LEVEL::FATAL:
                leve = "FATAL"; break;
        }
        return leve;
    }

    static std::string Log_Head(std::initializer_list<std::string> log_msg) noexcept
    {
            std::string log_head = "";
            auto tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            struct tm ptm;
            localtime_s(&ptm, &tt);
            char date[60] = {0};
            sprintf(date, "%d-%02d-%02d %02d:%02d:%02d",
                ptm.tm_year + 1900, ptm.tm_mon + 1, ptm.tm_mday,
                ptm.tm_hour, ptm.tm_min, ptm.tm_sec);
            log_head = std::string(date) + " | " + Get_Level();
            for(auto &msg : log_msg)
            {
                log_head += " | ";
                log_head += msg;
            }
            return log_head;
    }
};
