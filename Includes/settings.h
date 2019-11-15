#ifndef __SETTINGS_H
#define __SETTINGS_H

#include <string>
#include <stdio.h>
#include <map>

class Settings {
    std::map<std::string, std::string> settings;
    void readSettings(FILE* f);
public:
    Settings();

    std::string getString(std::string key);
    int getInt(std::string key);
};

#endif
