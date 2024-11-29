/*
 * @Author: Vanish
 * @Date: 2024-11-29 15:47:34
 * @LastEditTime: 2024-11-29 15:50:11
 * Also View: http://vanishing.cc
 * Contract Me: http://qunchengxiao.me
 * Copyright@ http://www.wtfpl.net/
 */
#pragma once

#include <iostream>
#include <string>

#include<Common/Singleton.hpp>

using std::string;

class Logger
{
public:
    friend class Singleton<Logger>;

public:
    enum Level
    {
        DEBUG = 0,
        INFO,
        WARN,
        ERROR,
        FATAL,
        LEVEL_COUNT
    };
public:
    void SetMode(Level level);
public:
    void Log(Level level, const char* message,...);

private:
    Level m_mode = DEBUG;
};