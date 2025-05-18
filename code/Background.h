//
// Created by Max Xxxx on 10.06.2024.
//

#ifndef PROJECT_RUBTSOV_BACKGROUND_H
#define PROJECT_RUBTSOV_BACKGROUND_H


#include <SFML/Graphics.hpp>

class Background {
private:
    sf::Texture texture;
    sf::Sprite sprite;
public:
    Background();
    void draw(sf::RenderWindow& window) const;
};


#endif //PROJECT_RUBTSOV_BACKGROUND_H
