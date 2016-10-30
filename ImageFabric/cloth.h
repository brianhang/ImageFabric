#pragma once

#include <SFML/Graphics.hpp>

#include "point.h"
#include "stick.h"

// The Cloth class simulates a rectangular piece of cloth.
class Cloth {
    private:
        // The dimensions of the cloth.
        unsigned int width;
        unsigned int height;

        // How far apart points on the cloth are.
        float spacing;

        // Coefficients to transform texture point to the cloth surface.
        float transformX;
        float transformY;

        // Render state for the cloth texture.
        sf::RenderStates renderState;

        // Points and sticks for simulating the cloth.
        std::vector<Point*> points;
        std::vector<Stick*> sticks;
        
        // Vertices for drawing the cloth.
        sf::VertexArray vertices;

    public:
        // Cloth constructor.
        Cloth(unsigned int newWidth, unsigned int newHeight,
            float spacing = 1.0f);

        // Cloth destructor.
        ~Cloth();

        // Updates the cloth simulation by 1 step.
        void update();

        // Draws the cloth to the screen.
        void draw(sf::RenderWindow &window);

        // Sets the texture to display on the cloth.
        void setTexture(const sf::Texture &texture);

        // Gets a point within the cloth.
        Point *getPoint(unsigned int x, unsigned int y);
}; 