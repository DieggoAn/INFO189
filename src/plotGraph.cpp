#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "../Dependencias/SFGraphing/include/SFGraphing/SFPlot.h"

using namespace csrc;

bool isValidPath (std::string userInput){
    std::ifstream file(userInput);

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo: " << userInput << std::endl;
        return false;
    }
    return true;
}

struct GraphData {
    std::string title;
    std::vector<float> xValues;
    std::vector<float> yValues;
};

GraphData readGraphFile(const std::string& filePath) {
    std::ifstream file(filePath);

    GraphData graphData;
    std::string line;

    // Lee la primera línea para obtener el título.
    if (std::getline(file, line)) {
        std::size_t pos = line.find("titulo:");
        if (pos != std::string::npos) {
            graphData.title = line.substr(pos + 8);  // 8 es la longitud de "titulo:"
        }
    }

    // Lee las siguientes líneas para obtener las coordenadas.
    while (std::getline(file, line)) {
        std::size_t xPos = line.find("x:");
        std::size_t yPos = line.find("y:");

        if (xPos != std::string::npos && yPos != std::string::npos) {
            int x, y;
            std::istringstream(line.substr(xPos + 2)) >> x;  // 2 es la longitud de "x:"
            std::istringstream(line.substr(yPos + 2)) >> y;  // 2 es la longitud de "y:"
            graphData.xValues.push_back(x);
            graphData.yValues.push_back(y);
        }
    }

    return graphData;
}


int main()
{
    std::string userInput = "";
    std::cout << "Ingrese direccion del archivo .gra : ";
    std::cin >> userInput;
    while (!isValidPath(userInput)){
        std::cout << std::endl << "Ingrese direccion del archivo .gra : ";
        std::cin >> userInput;
    }
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(1600, 800), "SF-Graphing", sf::Style::Default, settings);
    sf::Font font;
    font.loadFromFile("Dependencias/arial.ttf");

    /*
     * Plot
     */
    GraphData result = readGraphFile(userInput);
    if (!result.title.empty()) {
        result.title = result.title.substr(0, result.title.size() - 1);
    }
    std::vector<float> xAxis = result.xValues;
    std::vector<float> yAxis = result.yValues;

    PlotDataSet set1(xAxis, yAxis, sf::Color::Green, result.title, PlottingType::LINE);



    while (window.isOpen())
    {
        SFPlot plot(sf::Vector2f(400, 50), sf::Vector2f(600, 600), 50, font, "X Axis", "Y Axis");
        plot.AddDataSet(set1);
        //x-minimum, x-maximum, y-minimum, y-maximum, x-step-size, y-step-size, Color of axes
        plot.SetupAxes(0, 100, 0, 100, 10, 10, sf::Color::White);
        plot.GenerateVertices();

        window.clear(sf::Color::White);
        sf::Event Event;

        while(window.pollEvent(Event)){
            switch (Event.type){
            
            case sf::Event::Closed:
                window.close();

            }
        }

        window.clear(sf::Color(30, 30, 30));

        //set1.SetDataValue(0, set1.GetDataValue(0) + sf::Vector2f(0, 0.011));

        //Calling withouts parameters makes the Plot auto-deduce the size of the plot

        window.draw(plot);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            sf::Vector2u wSize = window.getSize();
            sf::Texture texture;
            texture.create(wSize.x, wSize.y);
            texture.update(window);
            sf::Image screenshot = texture.copyToImage();
            screenshot.saveToFile("screenshot.png");
        }
        window.display();
    }

    return 0;
}