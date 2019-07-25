
#include <QCoreApplication>
#include <iostream>
#include <databasereader.h>
#include <opencv2/opencv.hpp>
#include <string.h>
#include <supportvectormachine.h>

using namespace cv;
using namespace cv::ml;
using namespace std;

void train(void);
void test(void);
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    train();
    test();

    return a.exec();
}

void train(void)
{
    DatabaseReader dr;
    dr.readTrainingFiles();

    std::vector<int> labels= dr.getTrainLabels();
    std::vector<std::string>trainingFileNames = dr.getTrainFileNames();

    Mat trainingData,trainlabelMat;
    std::vector<int>trainingLabels;

    cout << "size =" << trainingFileNames.size()<<endl;

    for(unsigned int index=0;index<trainingFileNames.size();index++)
    {
        cout<<"file  "<<labels[index]<<"  "<<trainingFileNames[index]<<endl;
        Mat image=imread(trainingFileNames[index]);
        resize(image,image,Size(32,24));
        cvtColor(image,image, COLOR_BGR2GRAY);
        //HOGDescriptor d(Size(32,24),Size(8,8),Size(4,4),Size(4,4),9);
        //vector <float> descriptervalue;
       // vector <Point> location;
        //d.compute(image,descriptervalue,Size(0,0),Size(0,0),location);

       // Mat input(descriptervalue);
        //input=input.reshape(0,1);
        //trainingData.push_back(input);
        image=image.reshape(0,1);
        trainingData.push_back(image);
        trainingLabels.push_back(labels[index]);
     }
    trainingData.convertTo(trainingData,CV_32FC1);

    cout<<"training started" ;
    cout<<trainingData.size()<<endl;
    cout<<trainingLabels.size()<<endl;
    SupportVectorMachine svm;
    trainlabelMat=Mat(trainingLabels);
    svm.training(trainingData,trainlabelMat);

}
void test(void)
{
    DatabaseReader dr;
    dr.readTestingFiles();

    std::vector<int> labels= dr.getTestLabels();
    std::vector<std::string>testFileNames = dr.getTestFileNames();

    Mat testData,testlabelMat;
    std::vector<int>testLabels;

    cout << "size =" << testFileNames.size()<<endl;

    for(unsigned int index=0;index<testFileNames.size();index++)
    {
        cout<<"file  "<<labels[index]<<"  "<<testFileNames[index]<<endl;
        Mat image=imread(testFileNames[index]);
        resize(image,image,Size(32,24));
        cvtColor(image,image, COLOR_BGR2GRAY);
        //HOGDescriptor d(Size(32,24),Size(8,8),Size(4,4),Size(4,4),9);
        //vector <float> descriptervalue;
       // vector <Point> location;
       // d.compute(image,descriptervalue,Size(0,0),Size(0,0),location);


       // Mat input(descriptervalue);
       // input=input.reshape(0,1);
       // testData.push_back(input);
        image=image.reshape(0,1);
        testData.push_back(image);

        testLabels.push_back(labels[index]);


    }
    testData.convertTo(testData,CV_32FC1);

    cout<<"testing started" ;
    cout<<testData.size()<<endl;
    cout<<testLabels.size()<<endl;
    SupportVectorMachine svm;
    testlabelMat=Mat(testLabels);
    svm.testing(testData,testlabelMat);


}


