#include <SFML/Graphics.hpp>

#include "Headers/DrawText.hpp"

void draw_text(unsigned short i_x, unsigned short i_y, const std::string& i_text, sf::RenderWindow& i_window)
{
	//We're gonna align the text ot the left top
	short character_x = i_x;
	short character_y = i_y;

	unsigned char character_width;

	sf::Sprite character_sprite;

	sf::Texture font_texture;
	font_texture.loadFromFile("Resources/Images/Font.png");

	//We're gonna calculate the width of the character based on the font image size
	//96 because there are 96 character in the image
	character_width = font_texture.getSize().x / 96;

	character_sprite.setTexture(font_texture);

	for (const char a : i_text)
	{
		if ('\n' == a)
		{
			//After every newline we put increase the y-coordinate and reset the x-coordinate
			character_x = i_x;
			character_y += font_texture.getSize().y;

			continue;
		}

		//Change the position of the next character
		character_sprite.setPosition(character_x, character_y);
		//Pick the character from the font image
		character_sprite.setTextureRect(sf::IntRect(character_width * (a - 32), 0, character_width, font_texture.getSize().y));

		//Increase the x-coordinate
		character_x += character_width;

		//Draw the character
		i_window.draw(character_sprite);
	}
}