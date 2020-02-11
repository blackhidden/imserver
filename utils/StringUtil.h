/**
 *      @desc:  字符串操作工具类
 *      @author:jiacobi
 *      @date:  2020.2.11
 **/
#pragma once

#include <string>
#include <vector>

class StringUtil
{
private:
    StringUtil() = delete;
    ~StringUtil() = delete;
    StringUtil(const StringUtil& rhs) = delete;
    StringUtil& operator=(const StringUtil& rhs) = delete;

public:
    static void split(const std::string& str, std::vector<std::string>& v, const char* delimiter = "|");
    //����delimiterָ�����ַ�������str�и������
    static void cut(const std::string& str, std::vector<std::string>& v, const char* delimiter = "|");
    static std::string& replace(std::string& str, const std::string& toReplaced, const std::string& newStr);

    static void trimLeft(std::string& str, char trimmed = ' ');
    static void trimRight(std::string& str, char trimmed = ' ');
    static void trim(std::string& str, char trimmed = ' ');
};
