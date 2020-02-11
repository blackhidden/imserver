/**
 * 
 * zhangyl 2018.05.16
 */
/**
 *      @desc:  URL编解码工具
 *      @author:jiacobi
 *      @date:  2020.2.11
 **/
#include "URLEncodeUtil.h"

bool URLEncodeUtil::encode(const std::string& src, std::string& dst)
{
    if (src.size() == 0)
        return false;

    char hex[] = "0123456789ABCDEF";
    size_t size = src.size();
    for (size_t i = 0; i < size; ++i)
    {
        unsigned char cc = src[i];
        if (isascii(cc))
        {
            //��������ûдȫ������ֻת���˵�˫���š��ո񡢷�б�ܡ� & ������ַ���ʵ��Ӧ�õ�ʱ����Ҫ��ȫ
            if (cc == '"')
            {
                dst += "%22";
            }
            else if (cc == '\'')
            {
                dst += "%27";
            }
            else if (cc == ' ')
            {
                dst += "%20";
            }
            else if (cc == '/')
            {
                dst += "%2f";
            }
            else if (cc == '&')
            {
                dst += "%26";
            }
            else
                dst += cc;
        }
        else
        {
            unsigned char c = static_cast<unsigned char>(src[i]);
            dst += '%';
            dst += hex[c / 16];
            dst += hex[c % 16];
        }
    }
    return true;
}

bool URLEncodeUtil::decode(const std::string& src, std::string& dst)
{
    if (src.size() == 0)
        return false;

    int hex = 0;
    for (size_t i = 0; i < src.length(); ++i)
    {
        switch (src[i])
        {
        case '+':
            dst += ' ';
            break;
        case '%':
        {
            if (isxdigit(src[i + 1]) && isxdigit(src[i + 2]))
            {
                std::string hexStr = src.substr(i + 1, 2);
                hex = strtol(hexStr.c_str(), 0, 16);
                //��ĸ������[0-9a-zA-Z]��һЩ�������[$-_.+!*'(),] ���Լ�ĳЩ������[$&+,/:;=?@]
                //���Բ���������ֱ������URL
                if (!((hex >= 48 && hex <= 57) || //0-9
                    (hex >= 97 && hex <= 122) ||   //a-z
                    (hex >= 65 && hex <= 90) ||    //A-Z
                    //һЩ������ż�������[$-_.+!*'(),]  [$&+,/:;=?@]
                    hex == 0x21 || hex == 0x24 || hex == 0x26 || hex == 0x27 || hex == 0x28 || hex == 0x29
                    || hex == 0x2a || hex == 0x2b || hex == 0x2c || hex == 0x2d || hex == 0x2e || hex == 0x2f
                    || hex == 0x3A || hex == 0x3B || hex == 0x3D || hex == 0x3f || hex == 0x40 || hex == 0x5f
                    ))
                {
                    dst += char(hex);
                    i += 2;
                }
                else
                    dst += '%';
            }
            else
                dst += '%';
        }
        break;
        default:
            dst += src[i];
            break;
        }
    }

    return true;
}
