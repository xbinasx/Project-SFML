#include "blok.h"

class belka {
public:
    sf::RectangleShape shape;

    belka(float x, float y) {
        shape.setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(x, y);
    }

    void move(float dx) {
        shape.move(dx, 0);
        // Ograniczenie ruchu paletki w oknie
        if (shape.getPosition().x < 0) shape.setPosition(0, shape.getPosition().y);
        if (shape.getPosition().x + PADDLE_WIDTH > WINDOW_WIDTH)
            shape.setPosition(WINDOW_WIDTH - PADDLE_WIDTH, shape.getPosition().y);
    }
};
