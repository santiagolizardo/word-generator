#include "TrainingData.hpp"

#include <fstream>
#include <iostream>

#include <rapidjson/document.h>

void TrainingData::loadFromDisk() {
    std::ifstream file("training-data.json");
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open the file.");
    }
    std::string jsonContent((std::istreambuf_iterator(file)),
                                std::istreambuf_iterator<char>());
    file.close();

    rapidjson::Document document;
    if (document.Parse(jsonContent.c_str()).HasParseError()) {
        std::cerr << "JSON parse error." << std::endl;
        return;
    }

    for (rapidjson::SizeType i = 0; i < document.Size(); ++i) {
        if (document[i].IsString()) {
            words.push_back(document[i].GetString());
        }
    }
}

