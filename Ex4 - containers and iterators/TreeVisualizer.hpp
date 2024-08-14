#ifndef TREE_VISUALIZER_HPP
#define TREE_VISUALIZER_HPP

#include <SFML/Graphics.hpp>
#include "Tree.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>

using namespace ariel;

// Helper function to convert various types to string
template <typename T>
std::string valueToString(const T &value)
{
    std::ostringstream os;
    os << std::fixed << std::setprecision(1) << value;
    return os.str();
}

template <typename T>
class TreeVisualizer
{
private:
    Tree<T> &tree;
    sf::RenderWindow window;
    const float nodeRadius = 25.0f;
    const float verticalSpacing = 80.0f;
    const float initialHorizontalSpacing = 200.0f;
    sf::Font font;
    std::map<Node<T> *, sf::Vector2f> positions;

    bool loadFont()
    {
        if (!font.loadFromFile("sansation.ttf"))
        {
            std::cerr << "Error loading sansation.ttf. Please ensure the font file is in the correct directory." << std::endl;
            return false;
        }
        return true;
    }

    void positionNodes(Node<T> *node, float x, float y, float horizontalSpacing)
    {
        if (!node)
            return;

        positions[node] = sf::Vector2f(x, y);

        float childXOffset = x - (node->children.size() - 1) * horizontalSpacing / 2.f;

        for (size_t i = 0; i < node->children.size(); ++i)
        {
            Node<T> *child = node->children[i];
            if (child)
            {
                positionNodes(child, childXOffset + i * horizontalSpacing, y + verticalSpacing, horizontalSpacing / 2.f);
            }
        }
    }

    void drawTree()
    {
        for (const auto &pair : positions)
        {
            Node<T> *node = pair.first;
            sf::Vector2f position = pair.second;

            // Draw the node
            sf::CircleShape circle(nodeRadius);
            circle.setFillColor(sf::Color::White);
            circle.setOutlineColor(sf::Color::Black);
            circle.setOutlineThickness(1);
            circle.setPosition(position - sf::Vector2f(nodeRadius, nodeRadius));
            window.draw(circle);

            // Draw the node value
            sf::Text text;
            text.setFont(font);
            text.setString(valueToString(node->value));
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::Black);

            // Center the text
            sf::FloatRect textRect = text.getLocalBounds();
            text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            text.setPosition(position);
            window.draw(text);

            // Draw edges to child nodes
            for (Node<T> *child : node->children)
            {
                if (child)
                {
                    sf::Vector2f childPosition = positions[child];

                    sf::Vertex line[] = {
                        sf::Vertex(position, sf::Color::Black),
                        sf::Vertex(childPosition, sf::Color::Black)};
                    window.draw(line, 2, sf::Lines);
                }
            }
        }
    }

public:
    TreeVisualizer(Tree<T> &tree) : tree(tree), window(sf::VideoMode(1000, 800), "Tree Visualization")
    {
        if (!loadFont())
        {
            std::cerr << "Failed to load font. Exiting..." << std::endl;
            window.close();
        }
    }

    void display()
    {
        Node<T> *root = tree.get_root();
        if (root)
        {
            positionNodes(root, window.getSize().x / 2.f, nodeRadius + 50.f, initialHorizontalSpacing);
        }

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);

            // Draw the tree
            if (root)
            {
                drawTree();
            }

            window.display();
        }
    }
};

#endif
