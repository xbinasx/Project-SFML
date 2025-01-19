#include "stale.h"

class blok {
public:
    sf::RectangleShape shape;
    bool destroyed = false;

    blok(float x, float y) {
        shape.setSize(sf::Vector2f(BLOCK_WIDTH - 2, BLOCK_HEIGHT - 2));
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(x, y);
    }
};