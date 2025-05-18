//
// Created by Max Xxxx on 10.06.2024.
//

#include "EnemySpirit.h"
#include "Character.h"

EnemySpirit::EnemySpirit(sf::Vector2f startPosition)
        : lastDirection(1), currentFrame(0), defaultFrame(sf::IntRect(48, 62, 52, 30)),
          WalkingFrames({
                                sf::IntRect(23, 187, 50, 30),
                                sf::IntRect(150, 187, 52, 30),
                                sf::IntRect(279, 186, 51, 30),
                                sf::IntRect(406, 186, 52, 30),
                                sf::IntRect(533, 187, 53, 30),
                                sf::IntRect(662, 187, 52, 30),
                                sf::IntRect(790, 188, 51, 30),
                        }),
          DeathFrames({
                              sf::IntRect(50, 1250, 23, 30),
                              sf::IntRect(180, 1250, 20, 26),
                              sf::IntRect(310, 1255, 17, 22),
                              sf::IntRect(441, 1262, 11, 15),
                              sf::IntRect(570, 1266, 8, 11),
                      }),
          onGround(false), health(0), isDead(false) {

    if (texture.loadFromFile("/Users/maxxxxx/CLionProjects/project_rubtsov/Textures/Fire_Spirit_spritelist.psd")) {
        sprite.setTexture(texture);
        sprite.setTextureRect(defaultFrame);
        dx = 300;
        dy = 0;
        rect = sf::FloatRect(startPosition.x, startPosition.y, 52, 30);
    }
}

void EnemySpirit::update(float deltaTime) {
    rect.left += dx * deltaTime;
    CollisionX();
    if (!onGround) dy += 300 * deltaTime;
    rect.top += dy * deltaTime;
    onGround = false;
    CollisionY();

    currentFrame += deltaTime * 7;
    if (currentFrame >= 7) currentFrame -= 7;

    sprite.setTextureRect(WalkingFrames[int(currentFrame)]);

    if (dx < 0) {
        sprite.setScale(-1.f, 1.f);
        sprite.setOrigin(60, 0);
        lastDirection = -1;
    } else {
        sprite.setScale(1.f, 1.f);
        sprite.setOrigin(0, 0);
        lastDirection = 1;
    }

    sprite.setPosition(rect.left, rect.top);

    // Death animation
    if (health == -1) {
        currentFrame = 0;
        currentFrame += deltaTime * 100;
        if (currentFrame >= 5) {
            currentFrame -= 4;
            health = -2;
        }
        sprite.setTextureRect(DeathFrames[int(currentFrame)]);
    } else if (health == -2) {
        sprite.setTextureRect(DeathFrames[4]);
    }
}

sf::Sprite& EnemySpirit::getSprite() {
    return sprite;
}

void EnemySpirit::fight(Character& player){

    if(player.rect.intersects(rect) ){

        if(player.dy > 0 && health == 0 && !player.isDead) {

            dx = 0;
            player.dy = -200;
            health--;
        }
        if(!player.isDead && player.dy == 0 && health ==0) {
            player.health -= 3;
        }
    }
}

void EnemySpirit::CollisionX() {
    for (int i = rect.top / 50; i < (rect.top + rect.height) / 50; i++) {
        for (int j = rect.left / 50; j < (rect.left + rect.width) / 50; j++) {
            if (LoadingMap[i][j] == '1') {
                if (dx > 0) {
                    rect.left = j * 50 - rect.width;
                    dx *= -1;
                } else if (dx < 0) {
                    rect.left = j * 50 + 50;
                    dx *= -1;
                }
            }
        }
    }
}

void EnemySpirit::CollisionY() {
    for (int i = rect.top / 50; i < (rect.top + rect.height) / 50; i++) {
        for (int j = rect.left / 50; j < (rect.left + rect.width) / 50; j++) {
            if (LoadingMap[i][j] == 'B' || LoadingMap[i][j] == '0' ||
                LoadingMap[i][j] == 'I' || LoadingMap[i][j] == 'i'
                || LoadingMap[i][j] == 'L' || LoadingMap[i][j] == 'l'){
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
        }
    }
}
