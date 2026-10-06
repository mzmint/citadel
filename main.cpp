#include <SFML/Graphics.hpp>
#include "Grid.h"


int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    unsigned int width = desktop.size.x;
    unsigned int height = desktop.size.y;

    sf::RenderWindow window(
        desktop,
        "Citadel",
        sf::State::Fullscreen
    );

    int cellSize = width / 40;
    int tilet = 0;

    Grid grid(height + cellSize * 8, height, cellSize, true);

    sf::Font font;
    if (!font.openFromFile("assets/lemon_milk.ttf")) {
        return 1;
    }

    sf::RectangleShape cell({
        static_cast<float>(cellSize),
        static_cast<float>(cellSize)
    });

    sf::RectangleShape waterbtn({100.f, 100.f});
    waterbtn.setPosition({2020.f, 640.f});
    waterbtn.setFillColor(sf::Color(0, 128, 255));

    sf::RectangleShape landbtn({100.f, 100.f});
    landbtn.setPosition({2140.f, 640.f});
    landbtn.setFillColor(sf::Color(0, 255, 0));

    sf::RectangleShape roadbtn({100.f, 100.f});
    roadbtn.setPosition({2260.f, 640.f});
    roadbtn.setFillColor(sf::Color(0, 0, 0));

    sf::RectangleShape housebtn({100.f, 100.f});
    housebtn.setPosition({2380.f, 640.f});
    housebtn.setFillColor(sf::Color(255, 0, 0));

    sf::Text title(font);
    title.setCharacterSize(96);
    title.setPosition({2020.f, 80.f});
    title.setString("Citadel");
    title.setFillColor(sf::Color::Black);

    while (window.isOpen()) {

        while (auto event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* mouse =
                event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouse->button == sf::Mouse::Button::Left) {

                    int x = mouse->position.x / cellSize;
                    int y = mouse->position.y / cellSize;

                    grid.setCell(x, y, tilet);
                }
            }

            if (const auto* mouse =event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouse->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos = {
                        static_cast<float>(mouse->position.x),
                        static_cast<float>(mouse->position.y)
                    };

                    if (waterbtn.getGlobalBounds().contains(mousePos)) {
                        tilet = 0;
                    }
                }
            }

            if (const auto* mouse =event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouse->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos = {
                        static_cast<float>(mouse->position.x),
                        static_cast<float>(mouse->position.y)
                    };

                    if (landbtn.getGlobalBounds().contains(mousePos)) {
                        tilet = 1;
                    }
                }
            }

            if (const auto* mouse =event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouse->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos = {
                        static_cast<float>(mouse->position.x),
                        static_cast<float>(mouse->position.y)
                    };

                    if (roadbtn.getGlobalBounds().contains(mousePos)) {
                        tilet = 2;
                    }
                }
            }

            if (const auto* mouse =event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouse->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos = {
                        static_cast<float>(mouse->position.x),
                        static_cast<float>(mouse->position.y)
                    };

                    if (housebtn.getGlobalBounds().contains(mousePos)) {
                        tilet = 3;
                    }
                }
            }
        }

        window.clear(sf::Color::White);

        for (int x = 0; x < grid.getColumns(); x++) {
            for (int y = 0; y < grid.getRows(); y++) {

                if (grid.getCell(x, y) >= 4) grid.setCell(x, y, 0);

                cell.setPosition({
                    static_cast<float>(x * cellSize),
                    static_cast<float>(y * cellSize)
                });

                if (grid.getCell(x, y) == 0) cell.setFillColor(sf::Color(0, 128, 255));
                else if (grid.getCell(x, y) == 1) cell.setFillColor(sf::Color::Green);
                else if (grid.getCell(x, y) == 2) cell.setFillColor(sf::Color::Black);
                else cell.setFillColor(sf::Color::Red);

                window.draw(cell);
            }
        }

        grid.draw(window);
        window.draw(waterbtn);
        window.draw(landbtn);
        window.draw(roadbtn);
        window.draw(housebtn);
        window.draw(title);
        window.display();
    }

    return 0;
}