#include <iostream>
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Background.h"
#include "ENEMYSkeleton.h"
#include "EnemySpirit.h"
#include "BOSS.h"
#include "MapLoader.h"
using namespace std;



void Map() {
    float fightCooldown = 0.0f;
    BOSS boss;
    EnemySpirit spirit1({600,10});
    EnemySpirit spirit2({1500,600});
    EnemySpirit spirit3({3600 ,600});
    ENEMYSkeleton skeleton1({1500,400});
    ENEMYSkeleton skeleton2({3400,10});
    ENEMYSkeleton skeleton3({4000,300});
    Character character;
    auto window = sf::RenderWindow(
            sf::VideoMode({1000, 700}), "The Arthur",
            sf::Style::Default, sf::ContextSettings(0, 0, 8)
    );
    sf::Clock clock;
    Background background;

    sf::RectangleShape rectangle(sf::Vector2f(50, 50));
    sf::View gameView(sf::FloatRect(0, 0, 1000, 700));

    std::map<char, std::shared_ptr<sf::Texture>> textures = loadTextures();


    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        fightCooldown -= deltaTime;


        auto event = sf::Event();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        bool isMoving = character.handleInput(deltaTime,boss,skeleton1);
        character.handleInput(deltaTime,boss,skeleton2);
        character.handleInput(deltaTime,boss,skeleton3);
        character.update(deltaTime);
        character.handleMovement(isMoving);
        character.Finnish(window, deltaTime);

        skeleton1.update(deltaTime);
        skeleton1.fight(character,deltaTime);
        skeleton2.update(deltaTime);
        skeleton2.fight(character,deltaTime);
        skeleton3.update(deltaTime);
        skeleton3.fight(character,deltaTime);

        spirit1.update(deltaTime);
        spirit1.fight(character);
        spirit2.update(deltaTime);
        spirit2.fight(character);
        spirit3.update(deltaTime);
        spirit3.fight(character);

        boss.update(deltaTime);
        boss.fight(character,deltaTime);
        boss.Finnish(window, deltaTime);



        // Update the game view to follow the character
        sf::Vector2f characterPosition = character.getPosition();
        gameView.setCenter(characterPosition.x +50, characterPosition.y -130);  // Center view around character

        window.clear();
        // Draw the static background using the default view
        window.setView(window.getDefaultView());
        background.draw(window);

        // Draw the game world using the game view
        window.setView(gameView);
        for(int i = 0; i < H; i++) {
            for(int j = 0; j < W; j++) {
                char currChar = LoadingMap[i][j];
                if (textures.count(currChar)) {
                    sf::Sprite sprite;
                    sprite.setTexture(*textures[currChar]);
                    sprite.setScale(rectangle.getSize().x / textures[currChar]->getSize().x, rectangle.getSize().y / textures[currChar]->getSize().y);
                    sprite.setPosition(j * 50, i * 50);
                    window.draw(sprite);
                }
            }
        }
        window.draw(boss.getSprite());
        boss.drawHealthBar(window);

        window.draw(spirit1.getSprite());
        window.draw(spirit2.getSprite());
        window.draw(spirit3.getSprite());

        window.draw(skeleton1.getSprite());
        skeleton1.drawHealthBar(window);
        window.draw(skeleton2.getSprite());
        skeleton2.drawHealthBar(window);
        window.draw(skeleton3.getSprite());
        skeleton3.drawHealthBar(window);

        window.draw(character.getSprite());
        character.drawHealthBar(window);
        window.display();

    }
}

int main() {
    Map();
    return 0;
}




