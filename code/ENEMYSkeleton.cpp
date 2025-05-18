//
// Created by Max Xxxx on 10.06.2024.
//

#include "ENEMYSkeleton.h"
#include "Character.h"

ENEMYSkeleton::ENEMYSkeleton(sf::Vector2f startPosition)
        : lastDirection(1), currentFrame(0), defaultFrame(sf::IntRect(35, 60, 45, 67)),
          WalkingFrames({
                                sf::IntRect(52, 186, 40, 70),
                                sf::IntRect(180, 187, 40, 70),
                                sf::IntRect(308, 188, 40, 70),
                                sf::IntRect(436, 187, 40, 70),
                                sf::IntRect(564, 186, 40, 70),
                                sf::IntRect(692, 187, 40, 70),
                                sf::IntRect(820, 188, 40, 70),
                                sf::IntRect(948, 187, 40, 70)
                        }),
          FightingFrames({
                                 sf::IntRect(51, 699, 60, 75),
                                 sf::IntRect(179, 699, 60, 75),
                                 sf::IntRect(277, 700, 99, 75),
                                 sf::IntRect(402, 700, 60, 75),
                         }),
          DeathFrames({
                              sf::IntRect(33, 1224, 39, 56),
                              sf::IntRect(150, 1226, 50, 54),
                              sf::IntRect(268, 1256, 60, 24),
                      }),
          onGround(false), health(2), isAttacking(false), isAttackingFrames(false), isDead(false) {

    if (texture.loadFromFile("/Users/maxxxxx/CLionProjects/project_rubtsov/Textures/Skeleton_spritelist.psd")) {
        lastAttack = clock();
        sprite.setTexture(texture);
        sprite.setTextureRect(defaultFrame);
        sprite.setPosition(startPosition.x, startPosition.y);
        dx = 50;
        dy = 0;
        rect = sf::FloatRect(startPosition.x, startPosition.y, 55, 70);
    }
}

void ENEMYSkeleton::update(float deltaTime) {
    rect.left += dx * deltaTime;
    CollisionX();
    if (!onGround) dy += 300 * deltaTime;
    rect.top += dy * deltaTime;
    onGround = false;
    CollisionY();

    currentFrame += deltaTime * 8;
    if (currentFrame >= 8) currentFrame -= 8;

    sprite.setTextureRect(WalkingFrames[int(currentFrame)]);

    if (!isAttacking && dx < 0) {
        sprite.setScale(-1.f, 1.f);
        sprite.setOrigin(60, 0);
        lastDirection = -1;
    } else if (!isAttacking) {
        sprite.setScale(1.f, 1.f);
        sprite.setOrigin(0, 0);
        lastDirection = 1;
    }

    sprite.setPosition(rect.left, rect.top);

    // Death animation
    if (health <= 0) {
        isDead = true;
        dx = 0;
        currentFrame = 0;
        rect.height = 24;
        sprite.setTextureRect(DeathFrames[2]);
    }
}

sf::Sprite& ENEMYSkeleton::getSprite() {
    return sprite;
}

sf::Vector2f ENEMYSkeleton::getPosition() const {
    return sf::Vector2f(rect.left, rect.top);
}

void ENEMYSkeleton::fight(Character& player, float deltaTime) {
    sf::Vector2f playerPos = player.getPosition();
    float distance = sqrt(pow(rect.left - playerPos.x, 2) + pow(rect.top - playerPos.y, 2));
    playerPos.x < rect.left ? lastDirection = -1 : lastDirection = 1;

    if (!isDead) {
        if (distance < 50 && !isAttacking && !isAttackingFrames) {
            dx = 0;
            isAttacking = isAttackingFrames = true;
            currentFrame = 0; // Start at the beginning of the animation
        }

        if (isAttacking) {
            // If we're in the attacking state, play the animation
            currentFrame += 0.5 * deltaTime; // Potentially slower frame change
            sprite.setTextureRect(FightingFrames[int(currentFrame)]);
            sprite.setScale(lastDirection, 1.f);
            sprite.setOrigin(lastDirection == -1 ? 60 : 0, 0);
        }

        if (currentFrame >= 4 && isAttackingFrames) {
            isAttackingFrames = false; // Reset the attack flag
            isAttacking = false; // End the attack animation
            currentFrame = 0; // Reset the frame counter
            if (!player.isBlocking) {
                player.health--;
                if (playerPos.x >= rect.left) {
                    dx = -50;
                } else {
                    dx = 50;
                }
            }
        }
        if (!isAttacking && distance < 50) { // If we're not attacking, the enemy can turn
            if (playerPos.x >= rect.left) {
                dx = -50;
            } else {
                dx = 50;
            }
        }
    }
}

void ENEMYSkeleton::drawHealthBar(sf::RenderWindow& window) const {
    if (health <= 0) return;

    sf::RectangleShape healthBarBackground(sf::Vector2f(60, 10));
    healthBarBackground.setFillColor(sf::Color::Red);
    healthBarBackground.setPosition(rect.left, rect.top - 20);

    sf::RectangleShape healthBar(sf::Vector2f(health * 30, 10));
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setPosition(rect.left, rect.top - 20);

    window.draw(healthBarBackground);
    window.draw(healthBar);
}

void ENEMYSkeleton::CollisionX() {
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

void ENEMYSkeleton::CollisionY() {
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
