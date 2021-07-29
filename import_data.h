//
// Created by gaurang on 7/29/21.
//

#ifndef MICTRACKERCPP_IMPORT_DATA_H
#define MICTRACKERCPP_IMPORT_DATA_H

#include <string>
#include <stdexcept>
#include <vector>

class DataImporter{
public:
    DataImporter(std::string dataPath){
        if (!dataPath.empty()){
            dataDirectory = dataPath;
        } else {
            throw std::invalid_argument( "received empty path" );
        }
    };
    ~DataImporter(){};
    std::vector<std::string> getAllFilesInDir(const std::string &dirPath, const std::vector<std::string> dirSkipList = { });

public:
    std::string dataDirectory;
    std::vector<std::string> listOfFiles;
};

#endif //MICTRACKERCPP_IMPORT_DATA_H
