//
// Created by bekzhan on 4/12/16.
//

#include "ImageSet.h"

ImageSet::ImageSet() : currentImage(0) { }

ImageSet::ImageSet(const std::string& configPath) : currentImage(0) {
    loadData(configPath);
}

void ImageSet::loadData(const std::string &configPath) {
    cv::FileStorage storage(configPath, cv::FileStorage::READ);

    if (!storage.isOpened()) {
        std::cerr << "Could not open file storage at " << configPath << " for reading" << std::endl;
        return;
    }

    cv::FileNode root = storage.getFirstTopLevelNode();

    for (cv::FileNode it: root) {
        images.emplace_back(std::string(it));
    }

    coordinates.resize(images.size());

    storage.release();
}

void ImageSet::saveData(const std::string &configPath) {
//    cv::FileStorage storage(configPath, cv::FileStorage::WRITE);
//    if (!storage.isOpened()) {
//        std::cerr << "Could not open file storage at " << configPath << " for writing" << std::endl;
//        return;
//    }
//
//    for (auto i = 0; i < images.size(); i++) {
//
//    }
}