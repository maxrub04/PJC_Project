//
// Created by Max Xxxx on 10.06.2024.
//

#ifndef PROJECT_RUBTSOV_BOSS_H
#define PROJECT_RUBTSOV_BOSS_H

#include <SFML/Graphics.hpp>
class Character;
#include "MapLoader.h"

class BOSS {
private:
    float currentFrame;
    sf::IntRect defaultFrame;
    std::vector<sf::IntRect> WalkingFrames;
    std::vector<sf::IntRect> Fighting_1_Frames;
    std::vector<sf::IntRect> Fighting_2_Frames;
    std::vector<sf::IntRect> DeathFrames;

public:
    sf::Sprite sprite;
    sf::Texture texture;
    float dx, dy;
    sf::FloatRect rect;
    bool onGround;
    int health;
    bool isDead;
    bool isAttacking;
    bool isAttackingFrames;
    bool useFirstAttackFrames;

    BOSS();

    void update(float deltaTime);
    sf::Sprite& getSprite();
    sf::Vector2f getPosition() const;
    void Finnish(sf::RenderWindow& window, float deltaTime);
    void fight(Character& player, float deltaTime);
    void drawHealthBar(sf::RenderWindow& window) const;
    void CollisionX();
    void CollisionY();

    int lastDirection;
};

#endif //PROJECT_RUBTSOV_BOSS_H
