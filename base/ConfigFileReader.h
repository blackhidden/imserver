/**
 *      @desc:  配置文件读取类
 *      @author:jiacobi
 *      @date:  2020.2.7
 **/

#pragma once

#include <map>
#include <string>

class CConfigFileReader
{
public:
    CConfigFileReader(const char *fileName);
    ~CConfigFileReader();

    char* getConfigName(const char *key);
    int setConfigValue(const char *key, const char * value);

private:
    void loadFile(const char *fileName);
    int writeFile(const char *fileName = NULL);
    void parseLine(char *line);
    char* trimSpace(char *name);

    bool                                m_load_ok;
    std::map<std::string, std::string>  m_config_map;
    std::string                         m_config_file;
};

