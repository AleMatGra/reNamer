#include <iostream>

#include "ReNamer.h"

int main()
{
    std::cout << "reNamer by AMG," << '\n' << "Setup and settings will be taken from the config.txt, please read the instructions!" << '\n'; 
    
    ReNamer renamer;

    if(!renamer.checkForConfigFile())
    {
        renamer.createConfigFile();
        return 0;
    }

    if(!renamer.readConfigFile())
    {
        std::cout << "failed to read config file, invalid configuration / STOP encountered" << '\n';
        return 0;
    }

    if(!renamer.readSettings())
    {
        std::cout << "failed to read config file, invalid settings" << '\n';
        return 0;
    }

    if(!renamer.renameFiles())
    {
        std::cout << "failed to rename files" << '\n';
        return 0;
    }

    renamer.executeSettings();
    
    return 0;
}