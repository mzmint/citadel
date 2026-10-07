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

    sf::Texture sq;
    sf::Texture st;
    sf::Texture sc;
    sf::Texture ss;
    sf::Texture sb;
    sf::Texture se;
    if (!sq.loadFromFile("assets/street-quad.png")
        || !st.loadFromFile("assets/street-tri.png")
        || !sc.loadFromFile("assets/street-corner.png")
        || !ss.loadFromFile("assets/street-single.png")
        || !sb.loadFromFile("assets/street-straight.png")
        || !se.loadFromFile("assets/street-end.png")) {
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
        sf::Sprite streetSprite(sb);

        for (int x = 0; x < grid.getColumns(); x++) {
            for (int y = 0; y < grid.getRows(); y++) {

                int value = grid.getCell(x, y);

                cell.setPosition({
                    static_cast<float>(x * cellSize),
                    static_cast<float>(y * cellSize)
                });

                // WATER
                if (value == 0) {
                    cell.setFillColor(sf::Color(0, 128, 255));
                    window.draw(cell);
                }

                // LAND
                else if (value == 1) {
                    cell.setFillColor(sf::Color::Green);
                    window.draw(cell);
                }

                // HOUSE
                else if (value == 3) {

                    bool nextToStreet = false;

                    if (x > 0 &&
                        grid.getCell(x - 1, y) == 2)
                        nextToStreet = true;

                    if (x < grid.getColumns() - 1 &&
                        grid.getCell(x + 1, y) == 2)
                        nextToStreet = true;

                    if (y > 0 &&
                        grid.getCell(x, y - 1) == 2)
                        nextToStreet = true;

                    if (y < grid.getRows() - 1 &&
                        grid.getCell(x, y + 1) == 2)
                        nextToStreet = true;

                    if (nextToStreet) {
                        cell.setFillColor(sf::Color::Red);
                        window.draw(cell);
                    }
                }

                // STREET
                else if (value == 2) {

                    bool up =
                        y > 0 &&
                        grid.getCell(x, y - 1) == 2;

                    bool right =
                        x < grid.getColumns() - 1 &&
                        grid.getCell(x + 1, y) == 2;

                    bool down =
                        y < grid.getRows() - 1 &&
                        grid.getCell(x, y + 1) == 2;

                    bool left =
                        x > 0 &&
                        grid.getCell(x - 1, y) == 2;

                    int connections =
                        up + right + down + left;

                    // Reset sprite state every cell
                    streetSprite.setRotation(sf::degrees(0));
                    streetSprite.setScale({1.f, 1.f});

                    // FOUR-WAY
                    if (connections == 4) {
                        streetSprite.setTexture(sq);
                    }

                    // THREE-WAY
                    else if (connections == 3) {

                        streetSprite.setTexture(st);

                        if (!up)
                            streetSprite.setRotation(sf::degrees(0));

                        else if (!right)
                            streetSprite.setRotation(sf::degrees(90));

                        else if (!down)
                            streetSprite.setRotation(sf::degrees(180));

                        else if (!left)
                            streetSprite.setRotation(sf::degrees(270));
                    }

                    // TWO-WAY
                    else if (connections == 2) {

                        // Vertical
                        if (up && down) {
                            streetSprite.setTexture(sb);
                            streetSprite.setRotation(sf::degrees(0));
                        }

                        // Horizontal
                        else if (left && right) {
                            streetSprite.setTexture(sb);
                            streetSprite.setRotation(sf::degrees(90));
                        }

                        // CORNER
                        else {
                            streetSprite.setTexture(sc);

                            if (up && right)
                                streetSprite.setRotation(sf::degrees(270));

                            else if (right && down)
                                streetSprite.setRotation(sf::degrees(0));

                            else if (down && left)
                                streetSprite.setRotation(sf::degrees(90));

                            else if (left && up)
                                streetSprite.setRotation(sf::degrees(180));
                        }
                    }

                    // ONE-WAY / DEAD END
                    else if (connections == 1) {

                        streetSprite.setTexture(se);

                        if (up)
                            streetSprite.setRotation(sf::degrees(180));

                        else if (right)
                            streetSprite.setRotation(sf::degrees(270));

                        else if (down)
                            streetSprite.setRotation(sf::degrees(0));

                        else if (left)
                            streetSprite.setRotation(sf::degrees(90));
                    }

                    // ISOLATED
                    else {
                        streetSprite.setTexture(ss);
                    }

                    // Center the sprite
                    streetSprite.setOrigin({
                        static_cast<float>(cellSize) / 2.f,
                        static_cast<float>(cellSize) / 2.f
                    });

                    streetSprite.setPosition({
                        static_cast<float>(x * cellSize) + cellSize / 2.f,
                        static_cast<float>(y * cellSize) + cellSize / 2.f
                    });

                    window.draw(streetSprite);
                }
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