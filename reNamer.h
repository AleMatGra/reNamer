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

class ReNamer
{
    private:
        std::string extension;
        std::set<std::string> keyWords;
        std::set<char> replaceChars;
        std::set<char> removeChars;
        std::map<std::string, std::string> replacePairs;
        std::map<std::string, std::string> log;
        int removeLastCount{0};
        //settings:
        std::vector<std::pair<std::string, std::string>> configData;
        std::map<std::string, std::string> configMap;
        bool autoDelete{false};
        bool logging{false};
        bool printing{false};
        bool safety{false};
        char replacementSymbol{' '};
        const std::string safetyString{"### STOP, delete this line to enable functionality again ###"};
        //savety counter
        static int counter;

    private:
        std::string readLine(std::fstream& file);
        void removeSubstring(std::string& fileName, const std::string& removeString);
        void replaceSubstring(std::string& fileName, const std::string& findString, const std::string& replaceString);
        std::string getNewName(const std::string& oldName);
        void createLogfile();
        void placeSafetyString();

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