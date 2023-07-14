#include "ReNamer.h"

std::size_t ReNamer::counter{0};

ReNamer::ReNamer()
{
    // if you want to permanently change the settings look a little further below:
    size_t counter{0};
    this->text.insert("config intro", 
    "■ \"reNamer\" by AMG. The configuration is listed in order of execution.\n"
    "■ When you are using it the first time, enable the 'logging' setting.\n"
    "■ If something goes wrong it is the best way to recover. If a name is completely wiped (empty),\n"
    "■ it will be assigned the name 'file<number++>' so you will not end up with a bunch of files named '.txt'.\n"
    "■ After everything from the config gets applied, leading/trailing spaces will also be removed.\n"
    "■ If this file gets messed up, just delete it and run the .exe again!\n\n"
    "CONFIG -----------------------------------------------------------------------------------------------------------------------\n");
    this->text.insert("extension", "■ Put the extension of the files you want to change here (only one type of file can be changed at the same time) ↩");
    this->text.insert("\\n" + std::to_string(counter++), "\n");
    this->text.insert("extension value", ".extensionGoesHere");
    this->text.insert("\\n" + std::to_string(counter++), "\n");
    this->text.insert("remove symbol", "■ Remove x symbols from the end of the name ↩");
    this->text.insert("\\n" + std::to_string(counter++), "\n");
    this->text.insert("remove symbol value", "0");
    this->text.insert("\\n" + std::to_string(counter++), "\n");
    this->text.insert("string pairs", "■ Replace keywords, written as: old;new (seperated by the ';'), each couple in a new line ↩");
    this->text.insert("\\n" + std::to_string(counter++), "\n");
    this->text.insert("remove keywords", "■ Remove keywords, each keyword in a new line ↩");
    this->text.insert("\\n" + std::to_string(counter++), "\n");
    this->text.insert("replace symbol", "■ Replacement symbol (default is ' ') ↩");
    this->text.insert("\\n" + std::to_string(counter++), "\n");
    this->text.insert("replace symbol value", " "); //default should be ' '
    this->text.insert("\\n" + std::to_string(counter++), "\n");
    this->text.insert("replace symbols", "■ Symbols to be replace by the one above, each symbol in a new line ↩");
    this->text.insert("\\n" + std::to_string(counter++), "\n");
    this->text.insert("remove symbols", "■ Symbols to be removed, each symbol in a new line ↩");
    this->text.insert("\\n" + std::to_string(counter++), "\n");
    this->text.insert("leading zeros", "■ Add leading 0's, enter number of maximum digits (3 = 999) ↩");
    this->text.insert("\\n" + std::to_string(counter++), "\n");
    this->text.insert("leading zeros value", "0"); //default is 0
    this->text.insert("\\n" + std::to_string(counter++), "\n");
    this->text.insert("config end", "END OF CONFIG ----------------------------------------------------------------------------------------------------------------");
    this->text.insert("\\n" + std::to_string(counter++), "\n");
    this->text.insert("settings intro",
    "\n\n\nSETTINGS ---------------------------------------------------------------------------------------------------------------------\n"
    "■ Set them to either true or false.\n"
    "■ To permanently set them, re-compile the .exe, (look at the ReNamer constructor).\n\n");
    this->text.insert("auto delete", "■ Auto delete of reNamerConfig.txt after running once ↩");
    this->text.insert("\\n" + std::to_string(counter++), "\n");
    this->text.insert("auto delete value", "false\n"); //change to true if wanted
    this->text.insert("logging", "■ Create a logfile ↩");
    this->text.insert("\\n" + std::to_string(counter++), "\n");
    this->text.insert("logging value", "false\n"); //change to true if wanted
    this->text.insert("print", "■ Print to console ↩");
    this->text.insert("\\n" + std::to_string(counter++), "\n");
    this->text.insert("print value", "false\n"); //change to true if wanted
    this->text.insert("stop", "■ Can only run once (safety mechanism) ↩");
    this->text.insert("\\n" + std::to_string(counter++), "\n");
    this->text.insert("stop value", "false\n"); //change to true if wanted
    this->text.insert("settings end", "END OF SETTINGS --------------------------------------------------------------------------------------------------------------");
    this->text.insert("\\n" + std::to_string(counter++), "\n");
    this->text.insert("license", 
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
    "SOFTWARE.");
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
    if(pos != std::string::npos) 
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
        if(this->readLine(config) == this->settings.safetyString)
        {
            std::cout << this->settings.safetyString << '\n';
            return false;
        }

        //read through intro
        for(std::string line{}; std::getline(config, line);)
            if(line == this->text.at("extension"))
                break;

        //read in extension, there can only ever be one, we don't want to change multiple types at the same time
        this->config.extension = this->readLine(config);
        if(this->config.extension == this->text.at("extension value") && this->settings.printing)
            std::cerr << "Please set a valid extension!" << '\n';

        //move to next setting:
        if(this->readLine(config) != this->text.at("remove symbol"))
            return false;

        //number of symbols to be removed at the end
        try
        {
            int temp = std::stoi(this->readLine(config));
            if(temp < 0)
            {
                if(this->settings.printing)
                    std::cerr << "Invalid number for symbol removal!" << '\n';
                return false;
            }
            else
                this->config.removeLastCount = static_cast<std::size_t>(temp);
        }
        catch(const std::exception& e)
        {
            if(this->settings.printing)
                std::cerr << e.what() << '\n';
            return false;
        }
        
        //move to next setting:
        if(this->readLine(config) != this->text.at("string pairs"))
            return false;

        //read in string pairs
        for(std::string line{}; std::getline(config, line);)
        {
            //read in until next setting
            if(line == this->text.at("remove keywords"))
                break;

            size_t delimiterPos = line.find(';');
            if(delimiterPos != std::string::npos)
            {
                std::string key = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 1);
                this->config.replacePairs.insert(std::make_pair(key,value));
            }
            else
                return false;
        }

        //read in all keywords
        for(std::string line{}; std::getline(config, line);)
        {
            //read in until next setting
            if(line == this->text.at("replace symbol"))
                break;

            this->config.keyWords.insert(line);
        }

        this->config.replacementSymbol = this->readLine(config).at(0);

        //move to next setting:
        if(this->readLine(config) != this->text.at("replace symbols"))
            return false;

        //read in all symbols to replace
        for(std::string line{}; std::getline(config, line);)
        {
            //read in until next setting
            if(line == this->text.at("remove symbols"))
                break;

            this->config.replaceChars.insert(line.at(0));
        }

        //read in all symbols to remove
        for(std::string line{}; std::getline(config, line);)
        {
            //read in until next setting
            if(line == this->text.at("leading zeros"))
                break;
            this->config.removeChars.insert(line.at(0));
        }

        //number of digits for fixing numbering
        try
        {
            int temp = std::stoi(this->readLine(config));
            if(temp < 0)
            {
                if(this->settings.printing)
                    std::cerr << "Invalid number for fixing numbering!" << '\n';
                return false;
            }
            else
                this->config.leadingZeroesNumber = static_cast<std::size_t>(temp);
        }
        catch(const std::exception& e)
        {
            if(this->settings.printing)
                std::cerr << e.what() << '\n';
            return false;
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
            if(line == this->text.at("auto delete"))
                break;

        this->settings.autoDelete = (this->readLine(config) == "true");

        if(this->readLine(config) != this->text.at("logging"))
            return false;
        this->settings.logging = (this->readLine(config) == "true");

        if(this->readLine(config) != this->text.at("print"))
            return false;
        this->settings.printing = (this->readLine(config) == "true");

        if(this->readLine(config) != this->text.at("stop"))
            return false;
        this->settings.safety = (this->readLine(config) == "true");

        return true;
    }
    else
        return false;
}

void ReNamer::addLeadingZeroes(std::string& fileName)
{
    std::regex pattern("\\b\\d{1," + std::to_string(this->config.leadingZeroesNumber) +"}\\b");
    std::smatch match;
    std::regex_search(fileName, match, pattern);
    if(!match.empty())
    {
        std::string temp = match.str();
        for(std::size_t foundSize = temp.size(); foundSize < this->config.leadingZeroesNumber; foundSize++)
            temp.insert(temp.begin(), '0');

        this->replaceSubstring(fileName, match.str(), temp);
    }
}

std::string ReNamer::getNewName(const std::string& oldName)
{
    std::string newFileName{oldName};
    this->removeSubstring(newFileName, this->config.extension);

    //cut off chars at the end
    if(!newFileName.empty() && this->config.removeLastCount >= newFileName.size())
        newFileName.clear();
    else
        newFileName.erase(newFileName.size() - this->config.removeLastCount, this->config.removeLastCount);

    //swap replacement couples:
    if(!newFileName.empty() && !this->config.replacePairs.empty())
        for(const auto& pair: this->config.replacePairs)
            this->replaceSubstring(newFileName, pair.first, pair.second);

    //remove keywords:
    if(!newFileName.empty() && !this->config.keyWords.empty())
        for(const auto& keyWord : this->config.keyWords)
            this->removeSubstring(newFileName, keyWord);

    //replace symbols with replacementSymbol (default ' '):
    if(!newFileName.empty() && !this->config.replaceChars.empty())
        for(const auto& replaceChar : this->config.replaceChars)
            std::replace(newFileName.begin(), newFileName.end(), replaceChar, this->config.replacementSymbol);

    //remove symbols:
    if(!newFileName.empty() && !this->config.removeChars.empty())
        for(const auto& removeChar : this->config.removeChars)
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

    //leading zeros
    if(!newFileName.empty() && this->config.leadingZeroesNumber > 0)
        this->addLeadingZeroes(newFileName);

    //if a name got completely erased this allows us to keep track
    if(newFileName.empty())
        newFileName = "file" + std::to_string(counter++);

    if(this->settings.printing)
        std::cout << "renamed: " << oldName << " to " << newFileName + this->config.extension << '\n';

    if(this->settings.logging)
        this->log.insert(std::make_pair(oldName, newFileName + this->config.extension));

    return newFileName + this->config.extension;
}

bool ReNamer::renameFiles()
{
    for(const auto& dirEntry : std::filesystem::directory_iterator(std::filesystem::current_path()))
    {
        if (std::filesystem::is_regular_file(dirEntry) && dirEntry.path().extension() == this->config.extension)
        {
            const std::string currentFileName{dirEntry.path().filename().string()};
            try
            {
                if(currentFileName != "reNamerConfig.txt" && currentFileName != "reNamerLog.txt" && currentFileName != "licence.txt")
                {
                    const std::string newFileName{this->getNewName(currentFileName)};
                    std::filesystem::rename(std::filesystem::current_path() / currentFileName, std::filesystem::current_path() / newFileName);
                }
            }
            catch (std::filesystem::filesystem_error const& error)
            {
                if(this->settings.printing)
                    std::cerr << error.code() << '\n' << error.what() << '\n';
                return false;
            }
        }
    }

    if(this->settings.logging)
        this->createLogfile();

    if(this->settings.safety)
        this->placeSafetyString();

    return true;
}

bool ReNamer::checkForConfigFile()
{
    if(this->settings.printing)
        std::cout << "We are at: " << std::filesystem::current_path() << '\n';

    for(const auto& dirEntry : std::filesystem::directory_iterator(std::filesystem::current_path()))
    {
        const std::string currentFileName{dirEntry.path().filename().string()};
        if(!currentFileName.compare("reNamerConfig.txt"))
            return true;
    }

    if(this->settings.printing)
        std::cerr << "NO config file found!" << '\n';
    return false;
}

void ReNamer::createConfigFile()
{
    if(this->settings.printing)
        std::cout << "Creating a new config file." << '\n';

    std::ofstream config("reNamerConfig.txt");
    std::for_each(this->text.beginOrder(), this->text.endOrder(), [&](const auto& key)
    {
        config << text[key];
    });
    config.close();
}

void ReNamer::executeSettings()
{
    if(this->settings.autoDelete)
    {
        if(this->settings.printing)
            std::cout << "Auto delete the config file." << '\n';
        std::remove("reNamerConfig.txt");
        //if you want to add a .bat or something to auto delete the .exe too you can do that here
    }
}

void ReNamer::createLogfile()
{
    if(this->settings.printing)
        std::cout << "Create logfile: " << '\n';
    std::ofstream log("reNamerLog.txt");
    for(const auto& entry : this->log)
        log << entry.first << " got renamed to: " << entry.second << '\n';
    log.close();
}

void ReNamer::placeSafetyString()
{
    //read in all text in config file
    std::fstream config("reNamerConfig.txt", std::ios::in);
    std::stringstream content;
    content << config.rdbuf();
    config.close();
    //add safety string and put back everthing else
    std::ofstream configOut("reNamerConfig.txt");
    configOut << this->settings.safetyString << '\n';
    configOut << content.str();
    configOut.close();
}
