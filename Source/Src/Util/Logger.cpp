/*
 * @Author: Vanish
 * @Date: 2024-11-29 15:47:41
 * @LastEditTime: 2024-11-29 16:00:43
 * Also View: http://vanishing.cc
 * Contract Me: http://qunchengxiao.me
 * Copyright@ http://www.wtfpl.net/
 */
#include "Util/Logger.hpp"

void Logger::Log(Level level, const char* message,...)
{
    if(level >= m_mode)
    {
        std::cout<<"["<<level<<"]"<<message<<std::endl;
    }
}