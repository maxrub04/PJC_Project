//
// Created by Max Xxxx on 10.06.2024.
//

#include "MapLoader.h"

std::string LoadingMap[H] = {
        "0                                                                                                  0",
        "0                                                                                                  0",
        "0   H                                                                             H                0",
        "0IBBBBBBi               IBBBBBi     IBBBBBBBBi                                   IBi               0",
        "0LGGGGGGl1             1                                           1           1         IBi       0",
        "0         IBBBBBBBBBBBBi        ppp          IBBi                   IBBBBBBBBBi                    0",
        "0                              IBBBi         LGGl                                              IBi 0",
        "0                                            LGGl  IBBBi        Ii                                 0",
        "0                                            LGGl                                        IBBBi     0",
        "0                                            LGGl        Ii                 1          1           0",
        "0                      Ii 1           1 IBBBBGGGl                           IBBBBBBBBBi           0",
        "0                      Ll  IBBBBBBBBBi  LGGGGGGGl              Ii                                  0",
        "0          Ii    Ii                                      Ii    Ll    Ii                      Ii    0",
        "0          LlttttLl1                                    1LlttttLlttttLl1                   1 Ll    0",
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBl   IB",
        "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG   GG",
        "0                                                                                                  0",
        "0             H                                                         H                          0",
        "0            IBi              IBi               IBi                    IBi                         0",
        "0                                                                                                  0",
        "01      Ii                          Ii                  Ii         Ii                             10",
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};

std::map<char, std::shared_ptr<sf::Texture>> loadTextures() {
    const std::string TEXTURES_PATH = "/Users/maxxxxx/CLionProjects/project_rubtsov/Textures/";
    const std::map<char, std::string> textureFiles {
            {'B', "ground.png"},
            {'G', "blackblock.png"},
            {'I', "island-L.png"},
            {'i', "island-R.png"},
            {'L', "lower-L.png"},
            {'l', "lower-R.png"},
            {'t',"trapS.png"},
            {'p',"pila.png"},
            {'H',"Fishbarrel2.png"}
    };

    std::map<char, std::shared_ptr<sf::Texture>> textures;
    for (const auto& [key, filename] : textureFiles) {
        auto texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile(TEXTURES_PATH + filename)) {
            // Error handling
        }
        textures[key] = texture;
    }

    return textures;
}
