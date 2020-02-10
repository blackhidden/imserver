/**
 *      @desc:  单例模式模板
 *      @author:jiacobi
 *      @date:  2020.2.7
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
        return *value_;
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
