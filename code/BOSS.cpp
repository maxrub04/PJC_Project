//
// Created by Max Xxxx on 10.06.2024.
//

#include "BOSS.h"
#include "Character.h"

BOSS::BOSS()
        : lastDirection(1), currentFrame(0), defaultFrame(sf::IntRect(26, 181, 86, 75)),
          WalkingFrames({
                                sf::IntRect(26, 181, 86, 75),
                                sf::IntRect(155, 180, 84, 76),
                                sf::IntRect(284, 179, 83, 77),
                                sf::IntRect(413, 178, 81, 78),
                                sf::IntRect(542, 179, 80, 77),
                                sf::IntRect(799, 181, 81, 75),
                                sf::IntRect(926, 180, 81, 76),
                        }),
          Fighting_1_Frames({
                                    sf::IntRect(10, 812, 85, 84),
                                    sf::IntRect(140, 812, 84, 84),
                                    sf::IntRect(279, 813, 97, 83),
                                    sf::IntRect(401, 813, 80, 83),
                            }),
          Fighting_2_Frames({
                                    sf::IntRect(15, 935, 70, 89),
                                    sf::IntRect(146, 935, 68, 89),
                                    sf::IntRect(278, 940, 74, 84),
                                    sf::IntRect(407, 931, 92, 93),
                                    sf::IntRect(536, 930, 73, 94)
                            }),
          DeathFrames({
                              sf::IntRect(28, 1230, 83, 50),
                              sf::IntRect(156, 1258, 89, 22),
                      }),
          onGround(false), health(10), isDead(false),isAttacking(false), isAttackingFrames(false),useFirstAttackFrames() {

    if (texture.loadFromFile("/Users/maxxxxx/CLionProjects/project_rubtsov/Textures/Werewolf_Spritelist.psd")) {
        sprite.setTexture(texture);
        sprite.setTextureRect(defaultFrame);
        dx = 100;
        dy = 0;
        rect = sf::FloatRect(100, 800, 86, 75);
    }
}

void BOSS::update(float deltaTime) {
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
}

sf::Sprite& BOSS::getSprite() {
    return sprite;
}

sf::Vector2f BOSS::getPosition() const {
    return sf::Vector2f(rect.left, rect.top);
}

void BOSS::Finnish(sf::RenderWindow& window, float deltaTime) {
    if (health <= 0) {
        dx = 0;
        rect.height = 22;
        sprite.setTextureRect(DeathFrames[1]);

         sf::Font font;
         font.loadFromFile("/Users/maxxxxx/CLionProjects/project_rubtsov/Textures/Arial.ttf");
         sf::Text finishText("You win!", font, 50);
         finishText.setFillColor(sf::Color::Green);
         finishText.setPosition((window.getSize().x / 2 - finishText.getLocalBounds().width / 2),
                                (window.getSize().y / 2 - finishText.getLocalBounds().height ));
         window.clear();
         window.draw(finishText);
         window.display();
         sf::sleep(sf::seconds(5));
         window.close();
    }
}

void BOSS::fight(Character& player, float deltaTime) {
    sf::Vector2f playerPos = player.getPosition();
    float distance = sqrt(pow(rect.left - playerPos.x, 2) + pow(rect.top - playerPos.y, 2));
    playerPos.x < rect.left ? lastDirection = -1 : lastDirection = 1;

    if (!isDead) {
        if (distance < 50 && !isAttacking && !isAttackingFrames) {
            dx = 0;
            isAttacking = isAttackingFrames = true;
            currentFrame = 0; // Start at the beginning of the animation
            useFirstAttackFrames = rand() % 2 == 0; // Randomly choose between first and second attack frames
        }
        if (isAttacking) {
            // If we're in the attacking state, play the animation
            currentFrame += 0.5 * deltaTime; // Potentially slower frame change
            if (useFirstAttackFrames) {
                sprite.setTextureRect(Fighting_1_Frames[int(currentFrame)]);
            } else {
                sprite.setTextureRect(Fighting_2_Frames[int(currentFrame)]);
            }
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
                    dx = -100;
                } else {
                    dx = 100;
                }
            }
        }
        if (!isAttacking && distance < 50) { // If we're not attacking, the enemy can turn
            if (playerPos.x >= rect.left) {
                dx = -100;
            } else {
                dx = 100;
            }
        }
    }
}


void BOSS::drawHealthBar(sf::RenderWindow& window) const {
    sf::RectangleShape healthBarBackground(sf::Vector2f(100, 10));
    healthBarBackground.setFillColor(sf::Color::Red);
    healthBarBackground.setPosition(rect.left, rect.top - 20);

    sf::RectangleShape healthBar(sf::Vector2f(health * 10, 10));
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setPosition(rect.left, rect.top - 20);

    window.draw(healthBarBackground);
    window.draw(healthBar);
}

void BOSS::CollisionX() {
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

void BOSS::CollisionY() {
    for (int i = rect.top / 50; i < (rect.top + rect.height) / 50; i++) {
        for (int j = rect.left / 50; j < (rect.left + rect.width) / 50; j++) {
            if (LoadingMap[i][j] == 'B' || LoadingMap[i][j] == '0' ||
                LoadingMap[i][j] == 'I' || LoadingMap[i][j] == 'i'
                || LoadingMap[i][j] == 'L' || LoadingMap[i][j] == 'l') {
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

