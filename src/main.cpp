#include "Game.h"
#include "GameData.h"
#include "State.h"
#include <SFML/Graphics.hpp>


int main() {
    // create window and set up
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Factory", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Font font1;
    sf::Font font2;
    sf::Font font3;

    sf::Texture straight;
    straight.loadFromFile("Data/debug_sprite_16.png");
    sf::Texture bendr;
    bendr.loadFromFile("Data/debug_sprite_bendr.png");
    sf::Texture bendl;
    bendl.loadFromFile("Data/debug_sprite_bendl.png");
    sf::Texture splitter;
    splitter.loadFromFile("");

    conveyor_texture conveyor = {
            straight,
            bendr,
            bendl,
            splitter,
    };

    GameData gamedata = {
            window,
            false,
            font1, font2, font3,
            conveyor,
            0,
            16.f};

    //initialize an instance of the game class
    Game game(gamedata, Builder(gamedata));

    //run the init function of the game class and check it all initializes OK
    if (!game.init()) {
        return 0;
    }

    // A Clock starts counting as soon as it's created
    sf::Clock clock;

    // Game loop: run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event{};

        //calculate delta time
        sf::Time time = clock.restart();
        float dt = time.asSeconds();

        //'process inputs' element of the game loop
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            switch (event.type) {
                case sf::Event::Closed:
                    gamedata.window.close();
                    break;
                case sf::Event::Resized:
                    game.resize(event);
                    break;
                case sf::Event::KeyPressed:
                    game.keyPressed(event);
                    break;
                case sf::Event::KeyReleased:
                    game.keyReleased(event);
                    break;
                case sf::Event::MouseWheelScrolled:
                case sf::Event::MouseButtonPressed:
                case sf::Event::MouseButtonReleased:
                    game.mouseClicked(event);
                case sf::Event::MouseMoved:
                    game.mouseMoved(event);
                    break;
            }
        }

        //'update' element of the game loop
        game.update(dt);

        window.clear(sf::Color(50, 50, 50));

        //'render' element of the game loop
        game.render();
        window.display();
    }

    return 0;
}