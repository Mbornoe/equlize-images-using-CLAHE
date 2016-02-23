#include "opencv2/opencv.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <errno.h>
#include <string>
#include <iostream>

// Input argv variables
std::string inputImagesDir;
std::string outputImageDir;

// Initial the loop
std::vector<std::string> files = std::vector<std::string>();
std::string dir;

// Keeping the loop alive
int totalNumberOfFrames;
std::string workingImageFilepath;
cv::Mat frame;
