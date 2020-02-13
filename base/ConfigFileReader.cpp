/**
 *      @desc:  配置文件读取类
 *      @author:jiacobi
 *      @date:  2020.2.7
 **/

#include "ConfigFileReader.h"
#include <stdio.h>
#include <string.h>

CConfigFileReader::CConfigFileReader(const char *fileName) 
{
    loadFile(fileName);
}

CConfigFileReader::~CConfigFileReader()
{
}

char* CConfigFileReader::getConfigName(const char *fileName)
{
    if (!m_load_ok) {
        return NULL;
    }

    char *value = NULL;
    std::map<std::string, std::string>::iterator it = m_config_map.find(fileName);
    if (it != m_config_map.end()) {
        value = (char*)it->second.c_str();
    }
    return value;
}

int CConfigFileReader::setConfigValue(const char *key, const char * value)
{
    if (!m_load_ok) {
        return NULL;
    }

    std::map<std::string, std::string>::iterator it = m_config_map.find(key);
    if (it != m_config_map.end()) {
        it->second = value;
    } else {
        m_config_map.insert(std::make_pair(key, value));
    }
    return writeFile();
}

int CConfigFileReader::writeFile(const char *fileName)
{
    FILE *fp = NULL;
    if (fileName == NULL) {
        fp = fopen(m_config_file.c_str(), "w");
    } else {
        fp = fopen(fileName, "w");
    }
    if (fp == NULL) {
        return -1;
    }

    char szPaire[256];
    std::map<std::string, std::string>::iterator it = m_config_map.begin();
    for (; it != m_config_map.end(); it++) {
       memset(szPaire, 0, sizeof(szPaire));
       snprintf(szPaire, sizeof(szPaire), "%s=%s\n", it->first.c_str(), it->second.c_str());
       size_t ret =  fwrite(szPaire, strlen(szPaire),1,fp);
       if(ret != 1) {
           fclose(fp);
           return -1;
       }
    }
    fclose(fp);
    return 0;
}

void CConfigFileReader::loadFile(const char *fileName)
{
    m_config_file.clear();
    m_config_file.append(fileName);
    FILE *fp = fopen(fileName, "r");
    if (!fp) {
        return;
    }

    char buf[256];
    for (;;) {
        //从fp中读取一行到buf
        char *p = fgets(buf, 256, fp);
        if (!p) {
            break;
        }

        //移除换行符‘\n’
        size_t len = strlen(buf);
        if (buf[len - 1] == '\n') {
            buf[len - 1] = 0;
        }

        //移除以‘#’开头的字符串
        char *ch = strchr(buf, '#');
        if (ch) {
            *ch = 0;
        }

        if (strlen(buf) == 0) {
            continue;
        }

        parseLine(buf);
    }
    fclose(fp);
    m_load_ok = true;
}

void CConfigFileReader::parseLine(char *line) 
{
    //找到第一次出现‘=’的位置，截断字符串，前面为key，后面为value
    char *p = strchr(line, '=');
    if (p == NULL) {
        return;
    }

    *p = 0;
    char *key = trimSpace(line);
    char *value = trimSpace(p + 1);
    if (key && value) {
        m_config_map.insert(std::make_pair(key, value));
    }
}

char* CConfigFileReader::trimSpace(char *name) 
{
    //移除字符串开头的空格或Tab
    char *start_pos = name;
    while ((*start_pos == ' ') || (*start_pos == '\t') || (*start_pos == '\r')) {
        start_pos++;
    }
    if (strlen(start_pos) == 0) {
        return NULL;
    }

    //移除字符串结尾的空格或Tab
    char *end_pos = name + strlen(name) - 1;
    while ((*end_pos == ' ') || (*end_pos == '\t') || (*end_pos == '\r')) {
        *end_pos = 0;
        end_pos--;
    }
    int len = (end_pos - start_pos) + 1;
    if (len <= 0) {
        return NULL;
    }
    return start_pos;
}