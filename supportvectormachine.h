#ifndef SUPPORTVECTORMACHINE_H
#define SUPPORTVECTORMACHINE_H
#include <opencv2/opencv.hpp>
#include <iostream>

class SupportVectorMachine
{
public:
    SupportVectorMachine();

    void training(cv::Mat trainData ,cv::Mat trainLabels);
    void testing(cv::Mat testData ,std::vector<int> testLabels);


};

#endif // SUPPORTVECTORMACHINE_H
