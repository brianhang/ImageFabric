#include <SFML/Graphics.hpp>

#include "point.h"
#include "stick.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(640, 480), "Image Fabric Sim");
    window.setVerticalSyncEnabled(true);

    Point p(25.0f, 25.0f, 1.0f, 0.0f);
    Point p2(50.0f, 25.0f, 0.0f, 20.0f);
    Stick s(p, p2);

    sf::Clock deltaClock;

	while (window.isOpen()) {
        float deltaTime = deltaClock.getElapsedTime().asSeconds();
        deltaClock.restart();

		sf::Event e;

		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window.close();
            }
		}

        p.update(deltaTime);
        p2.update(deltaTime);

        s.constrain(deltaTime);

		window.clear();
        p.draw(window);
        p2.draw(window);
		window.display();
	}

	return 0;
}