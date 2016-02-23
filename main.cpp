#include "main.hpp"


void help() {
  std::cout << "";
  std::cout << " ";
  std::cout << ".\n"<< std::endl;

  std::cout << "Usage: ./main <imagesDirectory> <outputDirectory>\n" << std::endl;


}
int getdir (std::string dir, std::vector<std::string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        std::cout << "Error(" << errno << ") opening " << dir << std::endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(std::string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

 int numberOfFrames(std::vector<std::string> &files) {
  int numberOfImages = 0;
  for (size_t i = 0; i < files.size(); i++) {
    if ( files[i] != "." && files[i] != ".." && files[i] != ".DS_Store" && files[i] != ".git" && files[i] != ".gitignore"  ){
        // std::cout << files[i] << std::endl;
        numberOfImages = numberOfImages + 1;
      }
    }
  return numberOfImages;
}



int main(int argc, char* argv[]) {
  if (argc < 2) {
    help();
  }

  inputImagesDir = argv[1];

  outputImageDir = argv[2];

  std::cout << "Starting CLAHE conversion" << std::endl;
  std::cout << "Input images dir: " << inputImagesDir << std::endl;

  dir = std::string(inputImagesDir);

  getdir(dir, files);
  totalNumberOfFrames = numberOfFrames(files);

  for (size_t i = (files.size()-totalNumberOfFrames); i < files.size(); i++) {
    workingImageFilepath = inputImagesDir;
    workingImageFilepath += "/";
    workingImageFilepath += files[i];
    std::cout << "File: " << workingImageFilepath << std::endl;

    // READ RGB color image and convert it to Lab
    frame = cv::imread(workingImageFilepath);
    cv::Mat lab_image;
    cv::cvtColor(frame, lab_image, CV_BGR2Lab);
    cv::Mat lab_imageA = lab_image.clone();

    // Extract the L channel
    std::vector<cv::Mat> lab_planes(3);
    cv::split(lab_image, lab_planes);  // now we have the L image in lab_planes[0]

    // apply the CLAHE algorithm to the L channel
    //cv::Ptr<cv::gpu::CLAHE> clahe = cv::gpu::createCLAHE();
    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
    clahe->setClipLimit(4);
    cv::Mat dst;
    clahe->apply(lab_planes[0], dst);


    // Merge the the color planes back into an Lab image
    dst.copyTo(lab_planes[0]);
    cv::merge(lab_planes, lab_image);


    cv::Mat image_clahe;
    cv::cvtColor(lab_image, image_clahe, CV_Lab2BGR);
    std::string outputFilePath;
    outputFilePath = outputImageDir;
    outputFilePath += "/";
    outputFilePath += files[i];

    cv::imwrite( outputFilePath, image_clahe );

  }
  return 0;
}
