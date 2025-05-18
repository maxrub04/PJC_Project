//
// Created by Max Xxxx on 10.06.2024.
//

#include "Background.h"

Background::Background() {
    const std::string filePath = "/Users/maxxxxx/CLionProjects/project_rubtsov/Textures/Summer8.png";
    if (!texture.loadFromFile(filePath)) {
        // Handle error
    }
    sprite.setScale(sf::Vector2f(1.f * 1000 / texture.getSize().x, 1.f * 700 / texture.getSize().y));
    sprite.setTexture(texture);
}

void Background::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}
