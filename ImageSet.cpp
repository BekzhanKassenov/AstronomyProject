//
// Created by bekzhan on 4/12/16.
//

#include <fstream>
#include "ImageSet.h"

ImageSet::ImageSet() : currentImage(0) { }

ImageSet::ImageSet(const std::string& configPath) : currentImage(0) {
    loadData(configPath);
}

ImageSet::~ImageSet() {
    saveData("config/output.txt");
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

    std::cout << "Loaded image names:";
    for (auto fileName: images) {
        std::cout << " " << fileName;
    }

    std::cout << std::endl;

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
    coordinates[currentImage - 1] = std::pair <double, double> (x, y);
}

const std::string& ImageSet::nextImage() {
    if (currentImage >= (int)images.size()) {
        return std::string();
    }

    currentImage++;

    return images[currentImage - 1];
}