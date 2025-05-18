//
// Created by Max Xxxx on 10.06.2024.
//

#ifndef PROJECT_RUBTSOV_ENEMYSPIRIT_H
#define PROJECT_RUBTSOV_ENEMYSPIRIT_H

#include <SFML/Graphics.hpp>
class Character;
#include "MapLoader.h"
class EnemySpirit {
private:
    int lastDirection;
    float currentFrame;
    sf::IntRect defaultFrame;
    std::vector<sf::IntRect> WalkingFrames;
    std::vector<sf::IntRect> DeathFrames;

public:
    sf::Sprite sprite;
    sf::Texture texture;
    float dx, dy;
    sf::FloatRect rect;
    bool onGround;
    int health;
    bool isDead;

    EnemySpirit(sf::Vector2f startPosition);

    void update(float deltaTime);
    sf::Sprite& getSprite();
    void fight(Character& player);
    void CollisionX();
    void CollisionY();
};

#endif //PROJECT_RUBTSOV_ENEMYSPIRIT_H
