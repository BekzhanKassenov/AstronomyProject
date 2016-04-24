#include <iostream>
#include <cv.h>
#include <highgui.h>
#include "ImageSet.h"

namespace ap {
    const std::string WINDOW_NAME = "AstronomyProject";

    ImageSet imageSet("config/images.txt");

    void convertCoordinates(double& x, double& y) {

    }

    void loadImage(const std::string& fileName) {
        if (!fileName.empty()) {
            std::cout << "ap::loadImage: loading file "  << fileName << std::endl;

            cv::Mat image = cv::imread("dataset/" + fileName);

            if (!image.empty()) {
                cv::imshow(WINDOW_NAME, image);
                cv::waitKey(0);
            } else {
                std::cout << "Empty image, finishing" << std::endl;
                cv::destroyWindow(WINDOW_NAME);
            }

            image.release();
        } else {
            std::cout << "Empty filename, finishing" << std::endl;
            cv::destroyWindow(WINDOW_NAME);
        }
    }

    static void onMouse(int evt, int xInput, int yInput, int flag, void* param) {
        if (evt == CV_EVENT_LBUTTONDOWN) {
            double x = xInput;
            double y = yInput;

            convertCoordinates(x, y);

            imageSet.saveCoordinates(x, y);

            loadImage(imageSet.nextImage());
        }
    }
}

int main() {

    cv::namedWindow(ap::WINDOW_NAME, 0);
    cv::setMouseCallback(ap::WINDOW_NAME, ap::onMouse, NULL);

    ap::loadImage(ap::imageSet.nextImage());

    return 0;
}