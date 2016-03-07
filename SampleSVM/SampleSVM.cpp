// SampleSVM.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace cv::ml;
using namespace std;

int main(int argc, char ** argv)
{
	if (argc != 3)
	{
		cout << "You should supply two arguments !" << endl;
		cout << "First Argument : Training set folder path !" << endl;
		cout << "Second Argument : Testing image path !";
		waitKey(0);
		_gettch();
		return -1;
	}
	else
	{
		// Check if first paramter is directory

		struct stat s;

		if (stat(argv[1], &s) == 0)
		{
			if (s.st_mode & S_IFDIR)
			{
				cout << "Step 1 : Checking Directory name ! [OK] " << endl;
			}
			else
			{
				cout << "Step 1 : Checking Directory name ! [FAIL] " << endl;
				cout << "The folder does not exist or may be inaccessible !" << endl;
				waitKey(0);
				_gettch();
				return -1;
			}
		}
		else
		{
			cout << "Step 1 : Checking Directory name ! [FAIL] " << endl;
			cout << "The folder does not exist or may be inaccessible !" << endl;
			waitKey(0);
			_gettch();
			return -1;
		}

		if (stat(argv[2], &s) == 0)
		{
			if (s.st_mode & S_IFREG)
			{
				cout << "Step 2 : Checking file name ! [OK] " << endl;
			}
			else
			{
				cout << "Step 2 : Checking file name ! [FAIL] " << endl;
				cout << "The file does not exist or may be inaccessible !" << endl;
				waitKey(0);
				_gettch();
				return -1;
			}
		}
		else
		{
			cout << "Step 2 : Checking file name ! [FAIL] " << endl;
			cout << "The file does not exist or may be inaccessible !" << endl;
			waitKey(0);
			_gettch();
			return -1;
		}

		cout << "Step 3 : Generate Training Matrix for SVM ! [START] " << endl;

		// Training Matrix

		cout << "Step 3 : Generate Training Matrix for SVM ! [OK] " << endl;

		int numofFiles = 12;
		int imageArea = 30 * 30;
		Mat training_mat(numofFiles, imageArea, CV_32FC1);
		
		int labelsVal[12] = { 1, 1, 1, 1,1,1,1,-1,-1,-1,-1,-1 };


		Mat labels(numofFiles, 1, CV_32S, labelsVal);

		for (int im = 1; im <= numofFiles; im++)
		{


			char * fileName = (char*)malloc(200 * sizeof(char));

			sprintf(fileName, "%s%s%d%s", argv[1], "\\Untitled-", im, ".jpg");

			cout << "Proccesing Image: " << fileName << endl;

			Mat img_mat = imread(fileName, 0); // I used 0 for greyscale
			

			int ii = 0; // Current column in training_mat
			for (int i = 0; i<img_mat.rows; i++) {
				for (int j = 0; j < img_mat.cols; j++) {
					training_mat.at<float>(im-1, ii++) = img_mat.at<uchar>(i, j);
				}
			}
			
		}


		Mat testMat(1, imageArea, CV_32FC1);
		Mat queryMat = imread("C:\\Users\\User\\Pictures\\Number2\\Untitled-3_Prova.jpg", 0);

		int ii = 0; // Current column in training_mat
		for (int i = 0; i<queryMat.rows; i++) {
			for (int j = 0; j < queryMat.cols; j++) {
				testMat.at<float>(0, ii++) = queryMat.at<uchar>(i, j);
			}
		}


		
		

		// Initialize SVM
		Ptr<SVM> svm = SVM::create();
		svm->setType(SVM::C_SVC);
		svm->setKernel(SVM::POLY);
		svm->setGamma(3);
		svm->setDegree(3);

		svm->train(training_mat, ml::ROW_SAMPLE, labels);
		svm->save("trainingRes.xml");

		float result = svm->predict(testMat);
		Mat spv = svm->getSupportVectors();

		imshow("SPV", spv);
		waitKey(0);
		_gettch();
	}




	
}

