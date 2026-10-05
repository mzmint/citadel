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

    Grid grid(width, height, cellSize, false);

    sf::RectangleShape cell({
        static_cast<float>(cellSize),
        static_cast<float>(cellSize)
    });

    while (window.isOpen()) {

        while (auto event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* mouse =
                event->getIf<sf::Event::MouseButtonPressed>()) {

                if (mouse->button == sf::Mouse::Button::Left) {

                    int x = mouse->position.x / cellSize;
                    int y = mouse->position.y / cellSize;

                    grid.setCell(x, y, grid.getCell(x, y) + 1);
                }
                }
        }

        window.clear();

        for (int x = 0; x < grid.getColumns(); x++) {
            for (int y = 0; y < grid.getRows(); y++) {

                if (grid.getCell(x, y) >= 3) grid.setCell(x, y, 0);

                cell.setPosition({
                    static_cast<float>(x * cellSize),
                    static_cast<float>(y * cellSize)
                });

                if (grid.getCell(x, y) == 0) cell.setFillColor(sf::Color::Blue);
                else if (grid.getCell(x, y) == 1) cell.setFillColor(sf::Color::Green);
                else cell.setFillColor(sf::Color::Black);

                window.draw(cell);
            }
        }

        window.display();
    }

    return 0;
}