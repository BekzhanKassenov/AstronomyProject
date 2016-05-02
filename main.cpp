#include <iostream>
#include <cmath>

#include <cv.h>
#include <highgui.h>

#include "ImageSet.h"

namespace ap {
    const std::string WINDOW_NAME = "AstronomyProject";

    // Boundaries of the Sun
    const double LEFT = 19.0;
    const double RIGHT = 493.0;

    const double TOP = 19.0;
    const double BOTTOM = 493.0;

    // Coordinates of the center of the Sun
    const double CENTER_X = (LEFT + RIGHT) / 2.0;
    const double CENTER_Y = (TOP + BOTTOM) / 2.0;

    // Radius of the Sun on the image
    const double RADIUS = CENTER_X - LEFT;

    ImageSet imageSet("config/images.txt");

    template <typename T>
    inline T sqr(T x) {
        return x * x;
    }

    double getZ(double x, double y) {
        return sqrt(sqr(RADIUS) - sqr(x) - sqr(y));
    }

    double getAngle(double _x1, double _y1, double _z1,
                    double _x2, double _y2, double _z2) {
        double dot = _x1 * _x2 + _y1 * _y2 + _z1 * _z2;
        double len1 = sqrt(sqr(_x1) + sqr(_y1) + sqr(_z1));
        double len2 = sqrt(sqr(_x2) + sqr(_y2) + sqr(_z2));

        double rad = acos(dot / (len1 * len2));

        return rad * 180.0 / M_PI;
    }

    int sign(double x) {
        return (x > 0) - (x < 0);
    }

    void convertCoordinates(double& x, double& y) {
        x = x - CENTER_X;
        y = y - CENTER_Y;

        double xControl = 0;
        double yControl = 0;
        double zControl = getZ(xControl, yControl);

        double _x1 = 0;
        double _y1 = y;
        double _z1 = getZ(_x1, _y1);

        double _x2 = x;
        double _y2 = 0;
        double _z2 = getZ(_x2, _y2);

        double lat = -sign(_y1) * getAngle(xControl, yControl, zControl, _x1, _y1, _z1);

        double lon = sign(_x2) * getAngle(xControl, yControl, zControl, _x2, _y2, _z2);

        x = lat;
        y = lon;
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