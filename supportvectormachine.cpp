#include "supportvectormachine.h"
using namespace cv;
using namespace std;

SupportVectorMachine::SupportVectorMachine()
{
}
void SupportVectorMachine::training(Mat trainData ,Mat trainLabels)
{
    Ptr<cv::ml::SVM> svm= cv::ml::SVM::create();
    svm->setType(cv::ml::SVM::C_SVC);
    svm->setKernel(cv::ml::SVM::POLY);
    svm->setTermCriteria(cv::TermCriteria(TermCriteria::MAX_ITER,100, 1e-6));
    svm->setGamma(0.01);
    svm->setDegree(2);
    svm->setC(1000);

    trainData.convertTo(trainData, CV_32FC1);

    //svm->train(trainData,cv::ml::ROW_SAMPLE,trainLabels);
    cv::Ptr<cv::ml::TrainData> td = cv::ml::TrainData::create(trainData, cv::ml::ROW_SAMPLE, trainLabels);

    // train the SVM
    svm->train(td);

    // or auto train
   //svm->trainAuto(td);

    svm->save("svm.xml");
    cout << "Training Completed" << endl;

}


void SupportVectorMachine::testing(Mat testData ,vector<int> testLabels)
{
    cv::Ptr<cv::ml::SVM> svm=cv::ml::StatModel::load<cv::ml::SVM>("svm.xml");

    if(svm->empty())
        cout << "Loading failed" << endl;

    int totalClassifications = 0;
    int totalCorrect = 0;
    int totalWrong = 0;

    cout << testData.rows << endl;
    for(int i=0;i<testData.rows;i++)
    {
        totalClassifications++;
        Mat data = testData.row(i);
        //cout << data << endl;
        data.convertTo(data, CV_32FC1);
        int predicted = svm->predict(data);
        int expectedLabel = testLabels[i];
        cout <<"pre " << predicted << " exp " << expectedLabel << endl;
        if(predicted==expectedLabel)
            totalCorrect++;
        else
            totalWrong++;
    }
    // calculate percentages
    float percentageCorrect = ((float)totalCorrect / totalClassifications) * 100;
    float percentageIncorrect =  100 - percentageCorrect;

    // output
    cout << "Analysis - SVM" << endl;
    std::cout << std::endl << "Number of classications : " << totalClassifications << std::endl;
    std::cout << "Correct:  " << totalCorrect << " (" << percentageCorrect << "%)" << std::endl;
    std::cout << "Wrong: " << totalWrong  << " (" << percentageIncorrect << "%)" << std::endl;

}
