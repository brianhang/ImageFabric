#include <SFML/Graphics.hpp>
#include <iostream>

#include "cloth.h"

int main(int argc, const char *args[]) {
    sf::RenderWindow window(sf::VideoMode(640, 480), "Image Fabric Sim");
    window.setVerticalSyncEnabled(true);

    // Create a cloth to simulate.
    Cloth cloth(10, 10, 10.0f);

    // Set the texture to the first argument.
    sf::Texture texture;

    if (argc > 1 && texture.loadFromFile(args[1])) {
        cloth.setTexture(texture);
    }

    // Stick the top two corners.
    cloth.getPoint(0, 0)->setStatic(true);
    cloth.getPoint(9, 0)->setStatic(true);

	while (window.isOpen()) {
		sf::Event e;

		while (window.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseMoved:
                    // Move the top left corner to the mouse.
                    Point *corner = cloth.getPoint(0, 0);
                    corner->setPosition(sf::Vector2f(e.mouseMove.x, e.mouseMove.y));

                    break;
            }
		}

		window.clear();

        // Simulate and draw the cloth.
        cloth.update();
        cloth.draw(window);
        
		window.display();
	}

	return 0;
}