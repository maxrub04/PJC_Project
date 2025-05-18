//
// Created by Max Xxxx on 10.06.2024.
//

#ifndef PROJECT_RUBTSOV_MAPLOADER_H
#define PROJECT_RUBTSOV_MAPLOADER_H


#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>

std::map<char, std::shared_ptr<sf::Texture>> loadTextures();

const int H = 22;
const int W = 110;
extern std::string LoadingMap[H];


#endif //PROJECT_RUBTSOV_MAPLOADER_H
