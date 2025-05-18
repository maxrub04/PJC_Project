//
// Created by Max Xxxx on 10.06.2024.
//

#include "Character.h"
#include "MapLoader.h"
#include "ENEMYSkeleton.h"
#include "BOSS.h"
#include <SFML/Window.hpp>

Character::Character()
        : lastDirection(1),
          currentFrame(0),
          defaultFrame(sf::IntRect(35, 55, 50, 75)),
          RunningFrames{
                  sf::IntRect(35, 314, 60, 75),
                  sf::IntRect(164, 314, 60, 75),
                  sf::IntRect(292, 314, 60, 75),
                  sf::IntRect(420, 314, 60, 75),
                  sf::IntRect(548, 314, 60, 75),
                  sf::IntRect(676, 314, 60, 75),
                  sf::IntRect(804, 314, 60, 75),
                  sf::IntRect(932, 314, 60, 75)},
          FightingFrames{
                  sf::IntRect(13, 821, 60, 75),
                  sf::IntRect(150, 822, 60, 75),
                  sf::IntRect(288, 824, 80, 75),
                  sf::IntRect(416, 824, 60, 75)},
          DefendingFrames{
                  sf::IntRect(30, 1077, 60, 75),
                  sf::IntRect(160, 1080, 60, 75),
                  sf::IntRect(287, 1081, 60, 75)},
          DeathFrames{
                  sf::IntRect(19, 1210, 47, 70),
                  sf::IntRect(149, 1211, 43, 69),
                  sf::IntRect(296, 1247, 73, 33)},
          dx(0), dy(0), onGround(false), health(3), isBlocking(false),
          isDead(false), attackCooldown(5.0f), lastAttackTime(0.0f) , canAttack(true), isAttacking(false),isAttackingFrames(false) {

    if (texture.loadFromFile("/Users/maxxxxx/CLionProjects/project_rubtsov/Textures/Swordsman_spritelist.psd")) {
        sprite.setTexture(texture);
        sprite.setTextureRect(defaultFrame);
        sprite.setPosition(300, 550); //300
        rect = sf::FloatRect(300, 550, 55, 70);
    }
}

void Character::update(float deltaTime) {
    rect.left += dx * deltaTime;
    CollisionX();
    if (!onGround) dy += 300 * deltaTime;
    rect.top += dy * deltaTime;
    onGround = false;
    CollisionY();

    currentFrame += 10 * deltaTime;
    if (currentFrame >= 8) currentFrame -= 8;

    if (dx > 0) {
        sprite.setTextureRect(RunningFrames[int(currentFrame)]);
        sprite.setScale(1.f, 1.f);
        sprite.setOrigin(0, 0);
        lastDirection = 1;
    }
    if (dx < 0) {
        sprite.setTextureRect(RunningFrames[int(currentFrame)]);
        sprite.setScale(-1.f, 1.f);
        sprite.setOrigin(60, 0);
        lastDirection = -1;
    }
    sprite.setPosition(rect.left, rect.top);
    dx = 0;

    if (attackCooldown > 0) {
        attackCooldown -= deltaTime;
        canAttack = false;
    } else {
        canAttack = true;
    }
}

bool Character::handleInput(float deltaTime,BOSS& boss ,ENEMYSkeleton& skeleton) {
    bool isMoving = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        dx = -150;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        dx = 150;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (onGround) {
            dy = -280;
            onGround = false;
        }
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isAttacking && !isAttackingFrames ) {
        isAttacking = isAttackingFrames = true;
        currentFrame = 0;
    }

    if (isAttacking) {
        currentFrame += 0.5 * deltaTime;
        sprite.setTextureRect(FightingFrames[int(currentFrame)]);
        sprite.setScale(lastDirection, 1.f);
        sprite.setOrigin(lastDirection == -1 ? 60 : 0, 0);

        sf::Vector2f skeletonPos = skeleton.getPosition();
        float skeletonDis = sqrt(pow(rect.left - skeletonPos.x, 2) + pow(rect.top - skeletonPos.y, 2));

        sf::Vector2f bossPos = boss.getPosition();
        float bossDis = sqrt(pow(rect.left - bossPos.x, 2) + pow(rect.top - bossPos.y, 2));

        if (currentFrame >= 4 && isAttackingFrames) {
            isAttackingFrames = false;
            isAttacking = false;
            currentFrame = 0;

            if (skeletonDis < 73 ) {
                skeleton.health--;
                skeleton.dx = skeleton.dx*(-1);
            }
            if (bossDis < 80 ) {
                boss.health--;
                boss.lastDirection = boss.lastDirection*(-1);
            }
        }

        lastAttackTime = attackCooldown;
        isMoving = true;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        sprite.setTextureRect(DefendingFrames[2]);
        sprite.setScale(lastDirection, 1.f);
        sprite.setOrigin(lastDirection == -1 ? 60 : 0, 0);
        isMoving = true;
        isBlocking = true;
    } else {
        isBlocking = false;
    }

    return isMoving;
}

void Character::handleMovement(bool isMoving) {
    if (!isMoving) {
        currentFrame = 0;
        sprite.setTextureRect(defaultFrame);
        sprite.setScale(lastDirection, 1.f);
        sprite.setOrigin(lastDirection == -1 ? 50 : 0, 0);
    }
}

sf::Sprite& Character::getSprite() {
    return sprite;
}

sf::Vector2f Character::getPosition() const {
    return sf::Vector2f(rect.left, rect.top);
}

void Character::Finnish(sf::RenderWindow& window, float deltaTime) {
    if (health <= 0) {
        isDead = true;
        rect.height = 33;
        sprite.setTextureRect(DeathFrames[2]);
        sprite.setScale(lastDirection, 1.f);
        sprite.setOrigin(lastDirection == -1 ? 60 : 0, 0);


        sf::Font font;
        font.loadFromFile("/Users/maxxxxx/CLionProjects/project_rubtsov/Textures/Arial.ttf");
        sf::Text finishText("You LOST!", font, 50);
        finishText.setFillColor(sf::Color::Red);
        finishText.setPosition((window.getSize().x / 2 - finishText.getLocalBounds().width / 2),
                               (window.getSize().y / 2 - finishText.getLocalBounds().height ));
        window.clear();
        window.draw(finishText);
        window.display();
        sf::sleep(sf::seconds(10));
        window.close();
    }
}

void Character::drawHealthBar(sf::RenderWindow& window) const {
    if (health <= 0) return;
    sf::RectangleShape healthBarBackground(sf::Vector2f(60, 10));
    healthBarBackground.setFillColor(sf::Color::Red);
    healthBarBackground.setPosition(rect.left, rect.top - 20);

    sf::RectangleShape healthBar(sf::Vector2f(health * 20, 10));
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setPosition(rect.left, rect.top - 20);

    window.draw(healthBarBackground);
    window.draw(healthBar);
}

void Character::CollisionX() {
    bool healed = false;
    for (int i = rect.top / 50; i < (rect.top + rect.height) / 50; i++) {
        for (int j = rect.left / 50; j < (rect.left + rect.width) / 50; j++) {
            if (LoadingMap[i][j] == 'B' || LoadingMap[i][j] == '0' ||
                LoadingMap[i][j] == 'I' || LoadingMap[i][j] == 'i' ||
                LoadingMap[i][j] == 'L' || LoadingMap[i][j] == 'l' ||
                LoadingMap[i][j] == 'G') {
                if (dx > 0) {
                    rect.left = j * 50 - rect.width;
                }
                if (dx < 0) {
                    rect.left = j * 50 + 50;
                }
            }
            if (LoadingMap[i][j] == 't' || LoadingMap[i][j] == 'p') {
                health -= 3;
            }
            if( LoadingMap[i][j] == 'H'){
                if(health < 3 && !healed && !isDead){
                    health++;
                    healed = true;
                }
            } else {
                healed = false;
            }
        }
    }
}

void Character::CollisionY() {
    for (int i = rect.top / 50; i < (rect.top + rect.height) / 50; i++) {
        for (int j = rect.left / 50; j < (rect.left + rect.width) / 50; j++) {
            if (LoadingMap[i][j] == 'B' || LoadingMap[i][j] == '0' ||
                LoadingMap[i][j] == 'I' || LoadingMap[i][j] == 'i' ||
                LoadingMap[i][j] == 'L' || LoadingMap[i][j] == 'l' ||
                LoadingMap[i][j] == 'G') {
                if (dy > 0) {
                    rect.top = i * 50 - rect.height;
                    dy = 0;
                    onGround = true;
                }
                if (dy < 0) {
                    rect.top = i * 50 + 50;
                    dy = 0;
                }
            }
            if (LoadingMap[i][j] == 't' || LoadingMap[i][j] == 'p') {
                health -= 3;
            }
        }
    }
}
