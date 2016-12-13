/*
Copyright 2012. All rights reserved.
Institute of Measurement and Control Systems
Karlsruhe Institute of Technology, Germany

This file is part of libviso2.
Authors: Andreas Geiger

libviso2 is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or any later version.

libviso2 is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
libviso2; if not, write to the Free Software Foundation, Inc., 51 Franklin
Street, Fifth Floor, Boston, MA 02110-1301, USA
*/

/*
  Documented C++ sample code of stereo visual odometry (modify to your needs)
  To run this demonstration, download the Karlsruhe dataset sequence
  '2010_03_09_drive_0019' from: www.cvlibs.net!
  Usage: ./viso2 path/to/sequence/2010_03_09_drive_0019
  */

#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>

#include "viso_stereo.h"
#include <cv.h>
#include <highgui.h>
#include <time.h>

using namespace cv;
using namespace std;

void readParamters(string xmlFile, string& leftDir, string& rightDir, int& frameBegin, int &frameEnd, string& poseFile);

int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		printf("usage: ./viso2 [parameter.xml] \nend...\n");
		return 1;
	}
	// set most important visual odometry parameters
	// for a full parameter list, look at: viso_stereo.h
	VisualOdometryStereo::parameters param;

	// calibration parameters for sequence 2010_03_09_drive_0019 
	param.calib.f = 645.24; // focal length in pixels
	param.calib.cu = 635.96; // principal point (u-coordinate) in pixels
	param.calib.cv = 194.13; // principal point (v-coordinate) in pixels
	param.base = 0.5707; // baseline in meters

	// init visual odometry
	VisualOdometryStereo viso(param);

	// current pose (this matrix transforms a point from the current
	// frame's camera coordinates to the first frame's camera coordinates)
	Matrix pose = Matrix::eye(4);

	string leftDir, rightDir;
	string poseFile;
	int frameBegin, frameEnd;

	readParamters("parameter.xml", leftDir, rightDir, frameBegin, frameEnd, poseFile);

	cout << "frameBegin:" << frameBegin << endl;
	cout << "frameEnd:" << frameEnd << endl;
	cout << "leftDir:" << leftDir << endl;
	cout << "rightDir:" << rightDir << endl;
	cout << "poseFile:" << poseFile << endl;
	//system("pause");

	FILE* fp = fopen(poseFile.c_str(), "w");

	char leftFile[256];
	char rightFile[256];

	// loop through all frames i=0:372
	for (int32_t i = frameBegin; i <= frameEnd; i++)
	{
		clock_t timeBegin, timeEnd;
		// input file names
		//char base_name[256]; sprintf(base_name,"%06d.png",i);
		// catch image read/write errors here
		try
		{
			// load left and right input image
			sprintf(leftFile, leftDir.c_str(), i);
			sprintf(rightFile, rightDir.c_str(), i);

			Mat leftImg = imread(leftFile, CV_LOAD_IMAGE_GRAYSCALE);
			Mat rightImg = imread(rightFile, CV_LOAD_IMAGE_GRAYSCALE);

			// image dimensions
			int32_t width = leftImg.cols;
			int32_t height = leftImg.rows;

			// status
			cout << "Processing: Frame: " << i;

			// compute visual odometry
			int32_t dims[] = { width, height, width };
			timeBegin = clock();
			if (viso.process(leftImg.data, rightImg.data, dims))
			{
				// on success, update current pose
				pose = pose * Matrix::inv(viso.getMotion());
				// output some statistics
				double num_matches = viso.getNumberOfMatches();
				double num_inliers = viso.getNumberOfInliers();
				cout << ", Matches: " << num_matches<<endl;
				cout << pose << endl << endl;
				for (int32_t i = 0; i < 4; i++) 
				{
					for (int32_t j = 0; j < 4; j++) 
					{
						fprintf(fp, "%12.7f ", pose.val[i][j]);
					}
				}
				fprintf(fp, "\n");
			}
			else
			{
				cout << " ... failed!" << endl;
			}
			timeEnd = clock();
			cout<<"Time:"<<float(timeEnd - timeBegin)/CLOCKS_PER_SEC<<endl;

		}
		catch (...) {
			cerr << "ERROR: Couldn't read input files!" << endl;
			return 1;
		}
	}

	cout << "Demo complete! Exiting ..." << endl;

	return 0;
}

void readParamters(string xmlFile, string& leftDir, string& rightDir, int& frameBegin, int &frameEnd, string& poseFile)
{
	FileStorage fs(xmlFile, FileStorage::READ);

	fs["FrameBegin"] >> frameBegin;
	fs["FrameEnd"] >> frameEnd;
	fs["LeftDir"] >> leftDir;
	fs["RightDir"] >> rightDir;
	fs["PoseFile"] >> poseFile;
}
