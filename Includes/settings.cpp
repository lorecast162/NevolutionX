#include "settings.h"
#include <assert.h>
#include <vector>
#include "folderparse.h"


const
std::string USERDATAFOLDER = "E:\\UDATA\\";
const
std::string DEVFOLDER = USERDATAFOLDER + "44521818\\";
const
std::string TITLEMETAFILE = DEVFOLDER + "TitleMeta.xbx";
const
std::string SAVEFOLDER = DEVFOLDER + "DEADFACEBEEF\\";
const
std::string SAVEMETA = SAVEFOLDER + "SaveMeta.xbx";
const
std::string SETTINGSFILENAME = SAVEFOLDER + "DEADFACEBEEF";


void Settings::readSettings(FILE* f) {
    char readKey[20];
    char value[20];
    while (fscanf(f, " %s = %s", readKey, value) == 2) {
        settings[readKey] = value;
    }
}

Settings::Settings() {
    FILE *titleMeta = fopen(TITLEMETAFILE.c_str(), "r");
    if (!titleMeta) {
        std::vector<std::string> locs{"default", "EN", "JA", "DE", "FR",
                                      "ES", "IT", "KO", "TW", "BR"};
        titleMeta = fopen(TITLEMETAFILE.c_str(), "w");
        for (std::string s: locs) {
            fprintf(titleMeta, "[%s]\nTitleName=NevolutionX\n", s.c_str());
        }
    }
    fclose(titleMeta);

    FILE* settingsFile = fopen(SETTINGSFILENAME.c_str(), "r");
    if (!settingsFile) {
        if (!openFolder(DEVFOLDER.c_str())) {
            createFolder(DEVFOLDER.c_str());
        }
        if (!openFolder(SAVEFOLDER.c_str())) {
            createFolder(SAVEFOLDER.c_str());
        }

        FILE* saveMeta = fopen(SAVEMETA.c_str(), "r");
        if (!saveMeta) {
            saveMeta = fopen(SAVEMETA.c_str(), "w");
            fprintf(saveMeta, "Name=Settings\n");
        }
        fclose(saveMeta);

        settingsFile = fopen(SETTINGSFILENAME.c_str(), "w");
        if (!settingsFile) {
#ifdef DEBUG
            DbgPrint("");
#endif
            assert(false);
        }
        fprintf(settingsFile, "gamesPath = %s\n", "F:\\Games\\");
        fprintf(settingsFile, "appsPath = %s\n", "F:\\Apps\\");
        //fprintf(settingsFile, "gamesPath = %s\n", "F:\\Games\\");
        fclose(settingsFile);
        settingsFile = fopen(SETTINGSFILENAME.c_str(), "r");
    }
    readSettings(settingsFile);
    fclose(settingsFile);
}

std::string Settings::getString(std::string key) {
    return settings[key];
}

int Settings::getInt(std::string key) {
    return stoi(settings[key]);
}
