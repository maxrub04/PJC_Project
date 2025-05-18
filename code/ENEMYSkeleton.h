//
// Created by Max Xxxx on 10.06.2024.
//

#ifndef PROJECT_RUBTSOV_ENEMYSKELETON_H
#define PROJECT_RUBTSOV_ENEMYSKELETON_H

#include <SFML/Graphics.hpp>
class Character;
#include "MapLoader.h"

struct ENEMYSkeleton {
    int lastDirection;
private:
    float currentFrame;
    sf::IntRect defaultFrame;
    std::vector<sf::IntRect> WalkingFrames;
    std::vector<sf::IntRect> FightingFrames;
    std::vector<sf::IntRect> DeathFrames;

public:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::FloatRect rect;
    float dx, dy;
    bool onGround;
    int health;
    float lastAttack;
    bool isAttacking;
    bool isAttackingFrames;
    bool isDead;

    explicit ENEMYSkeleton(sf::Vector2f startPosition);

    void update(float deltaTime);
    sf::Sprite& getSprite();
    sf::Vector2f getPosition() const;
    void fight(Character& player, float deltaTime);
    void drawHealthBar(sf::RenderWindow& window) const;
    void CollisionX();
    void CollisionY();
};

#endif //PROJECT_RUBTSOV_ENEMYSKELETON_H
