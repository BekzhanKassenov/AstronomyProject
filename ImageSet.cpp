//
// Created by bekzhan on 4/12/16.
//

#include <fstream>
#include "ImageSet.h"

ImageSet::ImageSet() : currentImage(0) { }

ImageSet::ImageSet(const std::string& configPath) : currentImage(0) {
    loadData(configPath);
}

void ImageSet::loadData(const std::string &configPath) {
    std::ifstream input(configPath);

    if (!input.is_open()) {
        std::cerr << "Could not open file at " << configPath << " for reading" << std::endl;
        return;
    }

    std::string buf;
    while (input >> buf) {
        images.emplace_back(buf);
    }

    coordinates.resize(images.size());

    input.close();
}

void ImageSet::saveData(const std::string &configPath) {
    std::ofstream output(configPath);
    if (!output.is_open()) {
        std::cerr << "Could not open file at " << configPath << " for writing" << std::endl;
        return;
    }

    for (auto i = 0; i < images.size(); i++) {
        output << "{ " << images[i] << ", " << coordinates[i].first << ", " << coordinates[i].second << " }" << std::endl;
    }

    output.close();
}

void ImageSet::saveCoordinates(double x, double y) {
    coordinates[currentImage] = std::pair <double, double> (x, y);
}

const std::string& ImageSet::nextImage() {
    if (currentImage + 1 >= (int)images.size()) {
        return std::string();
    }

    currentImage++;

    return images[currentImage];
}