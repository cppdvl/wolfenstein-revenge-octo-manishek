// This program was created by the cpp devil
//
// Remake of Wolfenstein 3D.
// Author: The CPP Devil



// The things we are using from the standard library
#include <array>
#include <mutex>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <iostream>
#include <functional>

// The things we are using from SDL.
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


namespace Application
{
	namespace Window
	{
		constexpr auto scale = 4.0f;
		constexpr auto width = 320 * scale;
		constexpr auto height = 200 * scale;
	}
	namespace DataSpecific
	{
		auto transparentKeyColor = sf::Color(152, 0, 136);
	}
	


	namespace Util
	{
		void setTransparencies(sf::Image& image)
		{
			auto width = image.getSize().x;
			auto count = 0;
			for (auto x = 0u; x < width; x++)
			{
				for (auto y = 0u; y < image.getSize().y; y++)
				{
					auto pixel = image.getPixel(x, y);
					if (!y && !x)
					{
						std::cout << "Pixel: " << static_cast<int>(pixel.r) << " " << static_cast<int>(pixel.g) << " " << static_cast<int>(pixel.b) << std::endl;
					}
					if (pixel == DataSpecific::transparentKeyColor)
					{
						count++;
						image.setPixel(x, y, sf::Color::Transparent);
					}
				}
			}
			std::cout << "Transparent pixels: " << count << std::endl;
		}
	}
}
	

int main()
{


	sf::Image image;
	image.loadFromFile("resources/bmps/mguard_s_1.bmp");
	Application::Util::setTransparencies(image);
	sf::Texture texture;
	texture.loadFromImage(image);

	sf::Sprite sprite(texture);

	//scale the sprite
	sprite.setScale(Application::Window::scale, Application::Window::scale);

	
	//Create a window with transparent Background
	
	sf::RenderWindow window(sf::VideoMode(Application::Window::width, Application::Window::height), "AssetCheck", sf::Style::None);
	auto desktop = sf::VideoMode::getDesktopMode();
	window.setPosition(sf::Vector2i(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2));
	
	//Create a loop to keep the window open until esc is pressed.
	while (window.isOpen())
	{
		//Check for events.
		sf::Event event;
		while (window.pollEvent(event))
		{
			//Close the window if the close button is pressed.
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//Clear the window.
		window.clear();

		//Draw the Sprite
		window.draw(sprite);

		//Draw the window.
		window.display();
	}

	return 0;
}


