#pragma once

#include <windows.h>
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include "status.cpp"

namespace Taskbar {
    typedef std::unordered_map<std::string, std::string> t_section;
    typedef std::unordered_map<std::string, t_section*> t_settings;

    class Settings {
    public:
        Settings(std::string path) {
            std::ifstream infile(path.c_str());

            if (infile) {
                if (!this->_parseSettings(infile)) {
                    this->_status.setError("Incorrect file format: settings.ini");
                }
            } else {
                this->_status.setError("File not found: settings.ini");
            }

            infile.close();
        }
        ~Settings() {
            for (auto section : this->_settings) {
                delete section.second;
            }
        }
        bool hasError() {
            return this->_status.error;
        }
        const Status getStatus() {
            return this->_status;
        }
        std::string get(std::string section, std::string key, std::string defaultValue="") {
            auto foundSection = this->_settings.find(section);
            
            if (foundSection == this->_settings.end()) return defaultValue;

            auto section_ = foundSection->second;
            auto foundValue = section_->find(key);

            if (foundValue == section_->end()) return defaultValue;

            return foundValue->second;
        }
    private:
        Status _status = {};
        t_settings _settings = {};
        bool _parseSettings(std::istream &infile) {
            t_section* currentSection = nullptr;

            std::string currentSectionName = "default";

            currentSection = new t_section();

            this->_settings.insert_or_assign(currentSectionName, currentSection);

            for (std::string line; std::getline(infile, line); ) {
                if (line == "") continue;

                char firstCharacter = line[0];

                switch (firstCharacter) {
                    case ';': {
                        // comment - ignore...
                    } break;
                    case '[': {
                        size_t posFirstBracket = 0;
                        auto posLastBracket = line.find("]");

                        if (posLastBracket == std::string::npos) return false;
                        
                        currentSectionName = line.substr(posFirstBracket + 1, posLastBracket - posFirstBracket - 1);

                        currentSection = new t_section();

                        this->_settings.insert_or_assign(currentSectionName, currentSection);
                    } break;
                    default: {
                        auto posEqualSign = line.find("=");

                        if (posEqualSign == std::string::npos) return false;

                        std::string key = line.substr(0, posEqualSign);
                        std::string value = line.substr(posEqualSign + 1);

                        currentSection->insert_or_assign(key, value);
                    } break;
                }
            }

            return true;
        }
    };
}
