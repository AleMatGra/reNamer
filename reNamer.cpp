#include "ReNamer.h"

int ReNamer::counter{0};

ReNamer::ReNamer()
{
    size_t counter{0}; // to give all spacings a "random" value
    this->configData.push_back(std::make_pair("config intro", 
    "# \"reNamer\" by AMG; the configuration is listed in order of execution.\n"
    "# When you are using it the first time enable the 'logging' setting.\n"
    "# If something goes wrong it is the best way to recover, if a name is completely wiped (empty),\n"
    "# it will be assigned the name 'file<number>' (number increments) so you will not end up with a bunch of files named ' .txt'.\n"
    "# If this file gets messed up just delete it and run the .exe again!\n\n"
    "### CONFIG ###\n"));
    this->configData.push_back(std::make_pair("extension", "# extension of the files to be changed, the default value will cause the program to fail:"));
    this->configData.push_back(std::make_pair(std::to_string(counter++), "\n"));
    this->configData.push_back(std::make_pair("extension value", ".extensionGoesHere"));
    this->configData.push_back(std::make_pair(std::to_string(counter++), "\n"));
    this->configData.push_back(std::make_pair("remove symbol", "# remove symbols from the name, beginning at the end (default is 0):"));
    this->configData.push_back(std::make_pair(std::to_string(counter++), "\n"));
    this->configData.push_back(std::make_pair("remove symbol value", "0"));
    this->configData.push_back(std::make_pair(std::to_string(counter++), "\n"));
    this->configData.push_back(std::make_pair("string pairs", "# string pairs, written as: old;new seperated by the ';', the 'old' will be replaced by 'new', each couple in a new line:"));
    this->configData.push_back(std::make_pair(std::to_string(counter++), "\n"));
    this->configData.push_back(std::make_pair("remove keywords", "# remove keywords from the name, each keyword in a new line:"));
    this->configData.push_back(std::make_pair(std::to_string(counter++), "\n"));
    this->configData.push_back(std::make_pair("replace symbol", "# the symbol in the next line will be used as replacement, default is ' ' be careful to not overwrite it:"));
    this->configData.push_back(std::make_pair(std::to_string(counter++), "\n"));
    this->configData.push_back(std::make_pair("replace symbol value", " ")); //default should be ' '
    this->configData.push_back(std::make_pair(std::to_string(counter++), "\n"));
    this->configData.push_back(std::make_pair("replace symbols", "# list of symbols that will be replaced with the one above, each symbol in a new line:"));
    this->configData.push_back(std::make_pair(std::to_string(counter++), "\n"));
    this->configData.push_back(std::make_pair("remove symbols", "# list of symbols that will be removed, each symbol in a new line:"));
    this->configData.push_back(std::make_pair(std::to_string(counter++), "\n"));
    this->configData.push_back(std::make_pair("config end", "### END OF CONFIG ###"));
    this->configData.push_back(std::make_pair(std::to_string(counter++), "\n"));
    this->configData.push_back(std::make_pair("settings intro",
    "\n\n\n### SETTINGS ###\n"
    "# to set them, change the next lines to (true/false)\n"
    "# to permanently set them, the .exe needs to be re-compiled, change them in the reNamer ctor.\n\n"));
    this->configData.push_back(std::make_pair("auto delete", "# enable auto delete of reNamerConfig.txt"));
    this->configData.push_back(std::make_pair(std::to_string(counter++), "\n"));
    this->configData.push_back(std::make_pair("auto delete value", "true\n")); //change to true if wanted
    this->configData.push_back(std::make_pair("logging", "# enable logging to reNamerLog.txt (will be created)"));
    this->configData.push_back(std::make_pair(std::to_string(counter++), "\n"));
    this->configData.push_back(std::make_pair("logging value", "false\n")); //change to true if wanted
    this->configData.push_back(std::make_pair("print", "# enable to print each change to the console"));
    this->configData.push_back(std::make_pair(std::to_string(counter++), "\n"));
    this->configData.push_back(std::make_pair("print value", "false\n")); //change to true if wanted
    this->configData.push_back(std::make_pair("stop", "# enable to place a stop in the config file, the .exe cannot be run again until it is removed"));
    this->configData.push_back(std::make_pair(std::to_string(counter++), "\n"));
    this->configData.push_back(std::make_pair("stop value", "false\n")); //change to true if wanted
    this->configData.push_back(std::make_pair("settings end", "### END OF SETTINGS ###"));
    this->configData.push_back(std::make_pair(std::to_string(counter++), "\n"));
    this->configData.push_back(std::make_pair("license", 
    "\n\n\nLicense\n\n"
    "Copyright (c) 2023 Alexander Grath\n"
    "Permission is hereby granted, free of charge, to any person obtaining a copy\n"
    "of this software and associated documentation files (the \"Software\"), to deal\n"
    "in the Software without restriction, including without limitation the rights\n"
    "to use, copy, modify, merge, publish, distribute, and/or sublicense the Software,\n"
    "and to permit persons to whom the Software is furnished to do so, subject to the\n"
    "following conditions:\n\n"
    "The above copyright notice and this permission notice shall be included in all\n"
    "copies or substantial portions of the Software.\n\n"
    "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
    "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
    "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
    "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
    "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
    "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
    "SOFTWARE."
));

    for(const auto& entry : this->configData)
        this->configMap.insert(entry);
}

std::string ReNamer::readLine(std::fstream& file)
{
    std::string line;
    std::getline(file, line);
    return line;
}

void ReNamer::removeSubstring(std::string& fileName, const std::string& removeString) 
{
    size_t pos = fileName.find(removeString);
    if (pos != std::string::npos) 
        fileName.erase(pos, removeString.length());
}

void ReNamer::replaceSubstring(std::string& fileName, const std::string& findString, const std::string& replaceString)
{
    size_t pos = fileName.find(findString);
    if(pos != std::string::npos)
        fileName.replace(pos, findString.length(), replaceString);
}

bool ReNamer::readConfigFile()
{
    std::fstream config;
    config.open("reNamerConfig.txt", std::ios::in);
    if(config.is_open())
    {
        if(this->readLine(config) == safetyString)
        {
            std::cout << safetyString << '\n';
            return false;
        }

        //read through intro
        for(std::string line{}; std::getline(config, line);)
            if(line == this->configMap.at("extension"))
                break;

        //read in extension, there can only ever be one, we don't want to change multiple types at the same time
        this->extension = this->readLine(config);
        if(this->extension == this->configMap.at("extension value"))
            std::cout << "Please set a valid extension!" << '\n';

        //move to next setting:
        if(this->readLine(config) != this->configMap.at("remove symbol"))
            return false;

        //number of symbols to be removed at the end
        try
        {
            int temp = std::stoi(this->readLine(config));
            if(temp < 0)
            {
                std::cout << "Invalid number for symbol removal!" << '\n';
                return false;
            }
            else
                this->removeLastCount = temp;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
        
        //move to next setting:
        if(this->readLine(config) != this->configMap.at("string pairs"))
            return false;

        //read in string pairs
        for(std::string line{}; std::getline(config, line);)
        {
            //read in until next setting
            if(line == this->configMap.at("remove keywords"))
                break;

            size_t delimiterPos = line.find(';');
            if(delimiterPos != std::string::npos)
            {
                std::string key = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 1);
                this->replacePairs.insert(std::make_pair(key,value));
            }
            else
                return false;
        }

        //read in all keywords
        for(std::string line{}; std::getline(config, line);)
        {
            //read in until next setting
            if(line == this->configMap.at("replace symbol"))
                break;

            this->keyWords.insert(line);
        }

        this->replacementSymbol = this->readLine(config).at(0);

        //move to next setting:
        if(this->readLine(config) != this->configMap.at("replace symbols"))
            return false;

        //read in all symbols to replace
        for(std::string line{}; std::getline(config, line);)
        {
            //read in until next setting
            if(line == this->configMap.at("remove symbols"))
                break;

            this->replaceChars.insert(line.at(0));
        }

        //read in all symbols to remove
        for(std::string line{}; std::getline(config, line);)
        {
            //read in until next setting
            if(line == this->configMap.at("config end"))
                break;
            this->removeChars.insert(line.at(0));
        }

        return true;
    }
    else
        return false;
}

bool ReNamer::readSettings()
{
    std::fstream config;
    config.open("reNamerConfig.txt", std::ios::in);
    if(config.is_open())
    {
        //skip to settings:
        for(std::string line{}; std::getline(config, line);)
            if(line == this->configMap.at("auto delete"))
                break;

        this->autoDelete = (this->readLine(config) == "true");

        if(this->readLine(config) != this->configMap.at("logging"))
            return false;
        this->logging = (this->readLine(config) == "true");

        if(this->readLine(config) != this->configMap.at("print"))
            return false;
        this->printing = (this->readLine(config) == "true");

        if(this->readLine(config) != this->configMap.at("stop"))
            return false;
        this->safety = (this->readLine(config) == "true");

        return true;
    }
    else
        return false;
}

std::string ReNamer::getNewName(const std::string& oldName)
{
    std::string newFileName = oldName;

    //remove the extension to not cause problems (e.g., removing '.' from the filename)
    this->removeSubstring(newFileName, this->extension);

    //cut off chars at the end
    if(!newFileName.empty() && this->removeLastCount >= newFileName.size())
        newFileName.clear();
    else
        newFileName.erase(newFileName.size() - this->removeLastCount, this->removeLastCount);

    //swap replacement couples:
    if(!newFileName.empty() && !this->replacePairs.empty())
        for(const auto& pair: this->replacePairs)
            this->replaceSubstring(newFileName, pair.first, pair.second);

    //remove keywords:
    if(!newFileName.empty() && !this->keyWords.empty())
        for(const auto& keyWord : this->keyWords)
            this->removeSubstring(newFileName, keyWord);

    //replace symbols with replacementSymbol (default ' '):
    if(!newFileName.empty() && !this->replaceChars.empty())
        for(const auto& replaceChar : this->replaceChars)
            std::replace(newFileName.begin(), newFileName.end(), replaceChar, this->replacementSymbol);

    //remove symbols:
    if(!newFileName.empty() && !this->removeChars.empty())
        for(const auto& removeChar : this->removeChars)
        {
            auto remove = std::remove(newFileName.begin(), newFileName.end(), removeChar);
            newFileName.erase(remove, newFileName.end());
        }

    //remove leading spaces
    if(!newFileName.empty() && newFileName.at(0) == ' ')
        newFileName.erase(0, 1);

    //remove trailing spaces
    if(!newFileName.empty() && newFileName.at(newFileName.size() - 1) == ' ')
        newFileName.erase(newFileName.size() - 1, 1);

    //if a name got completely erased this allows us to keep track
    if(newFileName.empty())
        newFileName = "file" + std::to_string(counter++);

    if(this->printing)
        std::cout << "renamed: " << oldName << " to " << newFileName + this->extension << '\n';

    if(this->logging)
        this->log.insert(std::make_pair(oldName, newFileName + this->extension));

    return newFileName + this->extension;
}

bool ReNamer::renameFiles()
{
    for(const auto& dirEntry : std::filesystem::directory_iterator(std::filesystem::current_path()))
    {
        // check for correct extension
        if (std::filesystem::is_regular_file(dirEntry) && dirEntry.path().extension() == this->extension)
        {
            const std::string currentFileName{dirEntry.path().filename().string()};
            try
            {
                if(currentFileName == "reNamerConfig.txt" || currentFileName == "reNamerLog.txt")
                {
                    //do nothing, we don't want to change the reNamerConfig or reNamerLog file
                }
                else
                {
                    const std::string newFileName{this->getNewName(currentFileName)};
                    std::filesystem::rename(std::filesystem::current_path() / currentFileName, std::filesystem::current_path() / newFileName);
                }
            }
            catch (std::filesystem::filesystem_error const& error)
            {
                std::cout << error.code() << "\n" << error.what() << "\n";
                return false;
            }
        }
    }
    if(this->logging)
        this->createLogfile();

    if(this->safety)
        this->placeSafetyString();

    return true;
}

bool ReNamer::checkForConfigFile()
{

    std::cout << "We are at: " << std::filesystem::current_path() << '\n';

    for(const auto& dirEntry : std::filesystem::directory_iterator(std::filesystem::current_path()))
    {
        const std::string currentFileName{dirEntry.path().filename().string()};
        if(!currentFileName.compare("reNamerConfig.txt"))
            return true;
    }
    std::cout << "NO config file found!" << '\n';
    return false;
}

void ReNamer::createConfigFile()
{
    std::cout << "Creating a new config file." << '\n';

    std::ofstream config("reNamerConfig.txt");
    for(const auto& entry : this->configData)
        config << entry.second;
    config.close();
}

void ReNamer::executeSettings()
{
    if(this->autoDelete)
    {
        std::cout << "Autodelete!" << '\n';
        std::remove("reNamerConfig.txt");
        //if you want to add a .bat or something to auto delete the .exe too you can do that here
    }
}

void ReNamer::createLogfile()
{
    std::cout << "Create logfile: " << '\n';
    std::ofstream log("reNamerLog.txt");
    for(const auto& entry : this->log)
        log << entry.first << " got renamed to: " << entry.second << '\n';
    log.close();
}

void ReNamer::placeSafetyString()
{
    //read in all text in config file
    std::fstream config("reNamerConfig.txt", std::ios::in | std::ios::out);
    std::stringstream content;
    content << config.rdbuf();
    config.close();
    //add safety string and put back everthing else
    std::ofstream configOut("reNamerConfig.txt");
    configOut << this->safetyString << '\n';
    configOut << content.str();
    configOut.close();
}
