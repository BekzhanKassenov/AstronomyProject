//
// Created by bekzhan on 4/12/16.
//

#ifndef _IMAGESET_H
#define _IMAGESET_H

#include <cv.h>
#include <vector>

class ImageSet {
private:
    std::vector <std::string> images;
    std::vector <std::pair <double, double> >  coordinates;
    int currentImage;

public:
    ImageSet();

    ImageSet(const std::string& configPath);

    void loadData(const std::string &configPath);

    void saveData(const std::string& configPath);

    void saveCoordinates(double x, double y);

    const std::string& nextImage();
};

#endif // _IMAGESET_H_
