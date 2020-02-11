/**
 *      @desc:  URL编解码工具
 *      @author:jiacobi
 *      @date:  2020.2.11
 **/
#pragma once

#include <string>

class URLEncodeUtil final
{
private:
    URLEncodeUtil() = delete;
    ~URLEncodeUtil() = delete;

    URLEncodeUtil(const URLEncodeUtil& rhs) = delete;
    URLEncodeUtil& operator =(const URLEncodeUtil& rhs) = delete;

public:
    static bool encode(const std::string& src, std::string& dst);
    static bool decode(const std::string& src, std::string& dst);

};

