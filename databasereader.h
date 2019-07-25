#ifndef DATABASEREADER_H
#define DATABASEREADER_H

// TinyDir
#include "tinydir.h"

// Standard library
#include <iostream>
#include <vector>
#include <string>

class DatabaseReader
{
public:
    DatabaseReader();

    void readTrainingFiles();
    void readTestingFiles();

    std::vector<std::string> getTrainFileNames(){ return mTrainingFilenames; }

    std::vector<std::string> getTestFileNames(){ return mTestFilenames; }

    std::vector<int> getTrainLabels(){ return mLabels; }

    std::vector<int> getTestLabels(){ return mExpectedLabels; }

private:
    // hold labels -> training filenames
    std::vector<int> mLabels;
    std::vector<std::string> mTrainingFilenames;
    // hold labels -> test filenames
    std::vector<int> mExpectedLabels;
    std::vector<std::string> mTestFilenames;

};

#endif // DATABASEREADER_H
