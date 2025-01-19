#include "belka.hpp"

class pilka {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;

    pilka(float x, float y, float speedX, float speedY) {
        shape.setRadius(BALL_RADIUS);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(x, y);
        velocity = sf::Vector2f(speedX, speedY);
    }

    void move() {
        shape.move(velocity);
    }

    void bounceHorizontal() {
        velocity.x = -velocity.x;
    }

    void bounceVertical() {
        velocity.y = -velocity.y;
    }

    void reset(float x, float y) {
        shape.setPosition(x, y);
        velocity = sf::Vector2f(4.f, -4.f);
    }
};
