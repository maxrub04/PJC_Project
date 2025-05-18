//
// Created by Max Xxxx on 10.06.2024.
//

#ifndef PROJECT_RUBTSOV_CHARACTER_H
#define PROJECT_RUBTSOV_CHARACTER_H

#include <SFML/Graphics.hpp>
struct ENEMYSkeleton;
#include "BOSS.h"


extern std::string LoadingMap[];

class Character {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    int lastDirection = 1;
    float currentFrame = 0;
    sf::IntRect defaultFrame = sf::IntRect(35, 55, 50, 75);
    std::vector<sf::IntRect> RunningFrames;
    std::vector<sf::IntRect> FightingFrames;
    std::vector<sf::IntRect> DefendingFrames;
    std::vector<sf::IntRect> DeathFrames;

    float dx;
    bool onGround;
    float attackCooldown;
    float lastAttackTime;
    bool canAttack;
    bool isAttacking;
    bool isAttackingFrames;

public:
    Character();
    void update(float deltaTime);
    bool handleInput(float deltaTime, BOSS& boss, ENEMYSkeleton &skeleton);
    void handleMovement(bool isMoving);
    sf::Sprite& getSprite();
    sf::Vector2f getPosition() const;
    void Finnish(sf::RenderWindow& window, float deltaTime);
    void drawHealthBar(sf::RenderWindow& window) const;
    void CollisionX();
    void CollisionY();

    bool isBlocking = false;
    int health = 3;
    sf::FloatRect rect;
    float dy;
    bool isDead = false;

};

#endif //PROJECT_RUBTSOV_CHARACTER_H
