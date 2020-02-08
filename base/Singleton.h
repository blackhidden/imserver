/**
 *      功能：单例模式模板
 *      作者：jiacobi
 *      日期：2020.2.8
 **/

#pragma once

template<typename T>
class Singleton
{
public:
    static T& Instance() {
        if (value_ == nullptr) {
            value_ = new T();
        }
        return value_;
    }

private:
    Singleton();
    ~Singleton() = default;

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static void init() {
        value_ = new T();
    }

    static void destroy() {
        delete value_;
    }

private:
    static T* value_;
};

template<typename T>
T* Singleton<T>::value_ = nullptr;