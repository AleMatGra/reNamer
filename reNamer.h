#ifndef RENAMER
#define RENAMER

#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <map>
#include <vector>
#include <regex>

#include "OrderedMap.h"

struct Config
{
    std::string extension;
    std::size_t removeLastCount{0};
    std::map<std::string, std::string> replacePairs;
    std::set<std::string> keyWords;
    char replacementSymbol{' '};
    std::set<char> replaceChars;
    std::set<char> removeChars;
    std::size_t leadingZeroesNumber{0};
};

struct Settings
{
    bool autoDelete{false};
    bool logging{true};
    bool printing{false};
    bool safety{false};
    const std::string safetyString{"■ ■ ■ STOP! Delete this line to enable functionality again. ■ ■ ■"};
};

class ReNamer
{
    private:
        std::map<std::string, std::string> log;
        Config config;
        Settings settings;
        // text to read and write reNamerConfig.txt
        OrderedMap<std::string, std::string> text;
        //savety counter
        static std::size_t counter;

    private:
        std::string readLine(std::fstream& file);
        void removeSubstring(std::string& fileName, const std::string& removeString);
        void replaceSubstring(std::string& fileName, const std::string& findString, const std::string& replaceString);
        std::string getNewName(const std::string& oldName);
        void createLogfile();
        void placeSafetyString();
        void addLeadingZeroes(std::string& fileName);

    public:
        ReNamer(); //sets up the configData
        bool readConfigFile();
        bool readSettings();
        bool renameFiles();
        bool checkForConfigFile();
        void createConfigFile();
        void executeSettings();
};

#endif