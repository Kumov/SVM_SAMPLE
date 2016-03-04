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
	if (argc != 2)
	{
		cout << "You should supply two arguments !" << endl;
		cout << "First Argument : Training set folder path !" << endl;
		cout << "Second Argument : Testing image path !";
		return -1;
	}
	else
	{
		// Check if first paramter is directory

		struct stat s;

		if (stat(argv[0], &s) == 0)
		{
			if (s.st_mode & S_IFDIR)
			{
				cout << "Step 1 : Checking Directory name ! [OK] " << endl;
			}
		}
		else
		{
			cout << "Step 1 : Checking Directory name ! [FAIL] " << endl;
			cout << "The folder does not exist or may be inaccessible !" << endl;
			return -1;
		}

		if (stat(argv[1], &s) == 0)
		{
			if (s.st_mode & S_IFREG)
			{
				cout << "Step 2 : Checking file name ! [OK] " << endl;
			}
		}
		else
		{
			cout << "Step 2 : Checking file name ! [FAIL] " << endl;
			cout << "The file does not exist or may be inaccessible !" << endl;
			return -1;
		}

		cout << "Step 3 : Generate Training Matrix for SVM ! [START] " << endl;

		// Training Matrix

		cout << "Step 3 : Generate Training Matrix for SVM ! [OK] " << endl;

		// Initialize SVM
		Ptr<SVM> svm = SVM::create();
		svm->setType(SVM::C_SVC);
		svm->setKernel(SVM::POLY);
		svm->setGamma(3);
		waitKey(0);
	}




	
}

