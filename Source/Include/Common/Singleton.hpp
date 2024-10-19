/*
 * @Author: Vanish
 * @Date: 2024-10-11 17:57:19
 * @LastEditTime: 2024-10-11 18:18:53
 * Also View: http://vanishing.cc
 * Copyright@ https://creativecommons.org/licenses/by/4.0/deed.zh-hans
 */
#pragma once

template<typename T>
class Singleton
{
public:
    static T& Instance()
    {
        static T instance;
        return instance;
    }

protected:
    Singleton() = default; // 默认构造函数
    Singleton(const Singleton<T>&) = delete; // 拷贝构造函数
    Singleton<T>& operator=(const Singleton<T>&) = delete; // 拷贝赋值函数
    ~Singleton() = default; // 析构函数
};