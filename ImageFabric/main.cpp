#include <SFML/Graphics.hpp>
#include <assert.h>
#include "point.h"
#include "stick.h"

#include <iostream>

#define SIZE_X 10
#define SIZE_Y 10

int main() {
	sf::RenderWindow window(sf::VideoMode(640, 480), "Image Fabric Sim");
    window.setVerticalSyncEnabled(true);

    std::vector<Point*> points;
    std::vector<Stick*> sticks;

    Point *lastPoint = nullptr;

    for (int y = 0; y < SIZE_Y; y++) {
        for (int x = 0; x < SIZE_X; x++) {
            Point *vertex = new Point(x * 20.0f + 32.0f, y * 20.0f + 32.0f);

            if ((x == (SIZE_X - 1) || x == 0) && y == 0) {
                vertex->setStatic(true);
            }
            
            if (y > 0) {
                sticks.push_back(new Stick(points[(y - 1) * SIZE_X + x], vertex));
            }

            if (x > 0) {
                sticks.push_back(new Stick(vertex, lastPoint));
            }

            points.push_back(vertex);
            lastPoint = vertex;
        }
    }

    sf::VertexArray vertices(sf::Triangles, points.size() * 6);

    sf::Clock deltaClock;

	while (window.isOpen()) {
        float deltaTime = deltaClock.getElapsedTime().asSeconds();
        deltaClock.restart();

		sf::Event e;

		while (window.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (e.key.code == sf::Keyboard::Space) {
                        for (unsigned int i = 0; i < points.size(); i++) {
                            points[i]->move(0.0f, -2.0f);
                        }
                    }

                    break;
                case sf::Event::MouseMoved:
                    sf::Vector2f newPosition(sf::Mouse::getPosition(window));
                    std::cout << newPosition.x << ", " << newPosition.y << std::endl;
                    points[0]->setPosition(newPosition);
            }
		}

		window.clear();

        for (unsigned int i = 0; i < points.size(); i++) {
            points[i]->update(deltaTime);
            //points[i].draw(window);
        }

        for (unsigned int i = 0; i < sticks.size(); i++) {
            for (unsigned int j = 0; j < 10; j++) {
                sticks[i]->constrain(deltaTime);
            }
        }

        int i = 0;

        
        for (unsigned int y = 0; y < SIZE_Y - 1; y++) {
            for (unsigned int x = 0; x < SIZE_X - 1; x++) {
                vertices[i] = points[y * SIZE_X + x]->getPosition();
                vertices[++i] = points[(y + 1) * SIZE_X + x]->getPosition();
                vertices[++i] = points[(y + 1) * SIZE_X + x + 1]->getPosition();
                vertices[++i] = points[y * SIZE_X + x]->getPosition();
                vertices[++i] = points[y * SIZE_X + x + 1]->getPosition();
                vertices[++i] = points[(y + 1) * SIZE_X + x + 1]->getPosition();

                i++;
            }
        }

        window.draw(vertices);

		window.display();
	}

	return 0;
}