#include <iostream>

#include "ReNamer.h"

int main()
{
    std::cout << "reNamer by AMG," << '\n' << "Please read the reNamerConfig.txt!" << '\n'; 
    
    ReNamer renamer;

    if(!renamer.checkForConfigFile())
    {
        renamer.createConfigFile();
        return 0;
    }

    if(!renamer.readConfigFile())
    {
        std::cerr << "Failed to read config file, invalid configuration or STOP encountered!" << '\n';
        return 0;
    }

    if(!renamer.readSettings())
    {
        std::cerr << "Failed to read config file, invalid settings!" << '\n';
        return 0;
    }

    if(!renamer.renameFiles())
    {
        std::cerr << "Failed to rename files!" << '\n';
        return 0;
    }

    renamer.executeSettings();
    
    return 0;
}