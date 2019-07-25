#include "databasereader.h"

DatabaseReader::DatabaseReader()
{

}

/**
 * Get training files and store labels/filenames in vector classes
 **/
void DatabaseReader::readTrainingFiles()
{

    // open directory containing number directories
    tinydir_dir training_root_dir;
    tinydir_open(&training_root_dir, "train");

    // iterate over directories
    while (training_root_dir.has_next)
    {
        // get file
        tinydir_file file;
        tinydir_readfile(&training_root_dir, &file);

        // if it is a directory
        if(file.is_dir){

            std::string numbersDirName = file.name;

            // skip . / .. / .DS_Store (OSX)
            if(numbersDirName != "." && numbersDirName != ".." && numbersDirName != ".DS_Store"){

                // atoi isn't supersafe but sufficient for this test
                int currentLabel = atoi(file.name);

                // prepend full training_files directory
                numbersDirName.insert(0, "train/");

                // open directory containing number directories
                tinydir_dir training_number_dir;
                tinydir_open(&training_number_dir, numbersDirName.c_str() );

                // iterate over directories
                while (training_number_dir.has_next)
                {
                    // get file
                    tinydir_file trainingJpgFile;
                    tinydir_readfile(&training_number_dir, &trainingJpgFile);

                    // get directory name
                    std::string trainingJpgFileName = trainingJpgFile.name;

                    // skip . / .. / .DS_Store (OSX)
                    if (trainingJpgFileName != "." && trainingJpgFileName != ".." && trainingJpgFileName != ".DS_Store"){

                        // prepend full training_files directory
                        trainingJpgFileName.insert(0, numbersDirName + "/");

                        // store training filename and label
                        mTrainingFilenames.push_back(trainingJpgFileName);
                        mLabels.push_back(currentLabel);
                    }

                    // get next file
                    tinydir_next(&training_number_dir);
                }

                // close directory
                tinydir_close(&training_number_dir);
            }
        }

        // get next file
        tinydir_next(&training_root_dir);
    }

    // close directory
    tinydir_close(&training_root_dir);
}

/**
 * Get test files and store labels/filenames in vector classes
 **/
void DatabaseReader::readTestingFiles()
{

    // open directory containing number directories
    tinydir_dir test_root_dir;
    tinydir_open(&test_root_dir, "test");

    // iterate over directories
    while (test_root_dir.has_next)
    {
        // get file
        tinydir_file file;
        tinydir_readfile(&test_root_dir, &file);

        // if it is a directory
        if(file.is_dir)
        {

            std::string numbersDirName = file.name;

            // skip . / .. / .DS_Store (OSX)
            if(numbersDirName != "." && numbersDirName != ".." && numbersDirName != ".DS_Store")
            {

                // atoi isn't supersafe but sufficient for this test
                int currentLabel = atoi(file.name);

                // prepend full test_files directory
                numbersDirName.insert(0, "test/");

                // open directory containing number directories
                tinydir_dir test_number_dir;
                tinydir_open(&test_number_dir, numbersDirName.c_str() );

                // iterate over directories
                while (test_number_dir.has_next)
                {
                    // get file
                    tinydir_file testJpgFile;
                    tinydir_readfile(&test_number_dir, &testJpgFile);

                    // get directory name
                    std::string testJpgFileName = testJpgFile.name;

                    // skip . / .. / .DS_Store (OSX)
                    if (testJpgFileName != "." && testJpgFileName != ".." && testJpgFileName != ".DS_Store"){

                        // prepend full test_files directory
                        testJpgFileName.insert(0, numbersDirName + "/");

                        // store test filename and expected label
                        mTestFilenames.push_back(testJpgFileName);
                        mExpectedLabels.push_back(currentLabel);
                    }

                    // get next file
                    tinydir_next(&test_number_dir);
                }

                // close directory
                tinydir_close(&test_number_dir);
            }
        }

        // get next file
        tinydir_next(&test_root_dir);
    }

    // close directory
    tinydir_close(&test_root_dir);
}

