#include <vector>

#include "Headers/Global.hpp"
#include "Headers/GetTetromino.hpp"
#include "Headers/GetWallKickData.hpp"
#include "Headers/Tetromino.hpp"

Tetromino::Tetromino(unsigned char i_shape, const std::vector<std::vector<unsigned char>>& i_matrix) :
	rotation(0),
	shape(i_shape),
	minos(get_tetromino(i_shape, COLUMNS / 2, 1))
{
	//Random comment which I decided to put right here. This comment has no meaning.
	//It's main purpose is to waste your time. You're still reading it. You're stupid. Stop it!
	//You still wasting your time. THIS COMMENT DOES NOT HAVE ANY MEANING!
	//Why are you still reading this?
	//Here's how bacteria's reproduce:
	/*
	Bacteria reproduce by binary fission.
	In this process the bacterium, which is a single cell, divides into two identical daughter cells.
	Binary fission begins when the DNA of the bacterium divides into two (replicates).
	The bacterial cell then elongates and splits into two daughter cells each with identical DNA to the parent cell.
	Each daughter cell is a clone of the parent cell.

	When conditions are favourable such as the right temperatureand nutrients are available,
	some bacteria like Escherichia coli can I can't believe you're still reading this. Get a life! divide every 20 minutes.
	This means that in just seven hours one bacterium can generate 2, 097, 152 bacteria.
	After one more hour the number of bacteria will have risen to a colossal 16, 777, 216.
	That's why we can quickly become ill when pathogenic microbes invade our bodies.
	*/
}

bool Tetromino::move_down(const std::vector<std::vector<unsigned char>>& i_matrix)
{
	for (Position& mino : minos)
	{
		//Will we go outside the matrix if we move down?
		if (ROWS == 1 + mino.y)
		{
			return 0;
		}

		//Will we hit another tetromino if we move down?
		if (0 < i_matrix[mino.x][1 + mino.y])
		{
			return 0;
		}
	}

	//Move the tetromino down
	for (Position& mino : minos)
	{
		mino.y++;
	}

	//Return that everything is okay
	return 1;
}

bool Tetromino::reset(unsigned char i_shape, const std::vector<std::vector<unsigned char>>& i_matrix)
{
	//Reset the variables
	rotation = 0;
	shape = i_shape;

	minos = get_tetromino(shape, COLUMNS / 2, 1);

	for (Position& mino : minos)
	{
		if (0 < i_matrix[mino.x][mino.y])
		{
			//Return that we can't reset because there's a tetromino at the spawn location
			return 0;
		}
	}

	//Return that everything is fine
	return 1;
}

unsigned char Tetromino::get_shape()
{
	//I'm gonna take a wild guess and say that this return the shape of the tetromino
	return shape;
}

void Tetromino::hard_drop(const std::vector<std::vector<unsigned char>>& i_matrix)
{
	//I'm so smart. I used the ghost tetromino function to make the hard drop function
	minos = get_ghost_minos(i_matrix);
}

void Tetromino::move_left(const std::vector<std::vector<unsigned char>>& i_matrix)
{
	//This is similar to the move down function so I'm not gonna explain anything here. Bite me!
	for (Position& mino : minos)
	{
		if (0 > mino.x - 1)
		{
			return;
		}

		if (0 > mino.y)
		{
			continue;
		}
		else if (0 < i_matrix[mino.x - 1][mino.y])
		{
			return;
		}
	}

	for (Position& mino : minos)
	{
		mino.x--;
	}
}

void Tetromino::move_right(const std::vector<std::vector<unsigned char>>& i_matrix)
{
	//Hello!
	for (Position& mino : minos)
	{
		if (COLUMNS == 1 + mino.x)
		{
			return;
		}

		if (0 > mino.y)
		{
			continue;
		}
		else if (0 < i_matrix[1 + mino.x][mino.y])
		{
			return;
		}
	}

	for (Position& mino : minos)
	{
		mino.x++;
	}
}

void Tetromino::rotate(bool i_clockwise, const std::vector<std::vector<unsigned char>>& i_matrix)
{
	//I don't even wanna explain this. I spent way too much time writing this
	if (3 != shape)
	{
		unsigned char next_rotation;

		std::vector<Position> current_minos = minos;

		//Calculating the next rotation state
		if (0 == i_clockwise)
		{
			next_rotation = (3 + rotation) % 4;
		}
		else
		{
			next_rotation = (1 + rotation) % 4;
		}

		//If it's the I shape
		if (0 == shape)
		{
			//We find it's center
			float center_x = 0.5f * (minos[1].x + minos[2].x);
			float center_y = 0.5f * (minos[1].y + minos[2].y);

			switch (rotation)
			{
				case 0:
				{
					center_y += 0.5f;

					break;
				}
				case 1:
				{
					center_x -= 0.5f;

					break;
				}
				case 2:
				{
					center_y -= 0.5f;

					break;
				}
				case 3:
				{
					center_x += 0.5f;
				}
			}

			//Then we rotate every mino based on the center
			for (Position& mino : minos)
			{
				//We find the position of the mino relative to the center
				float x = mino.x - center_x;
				float y = mino.y - center_y;

				if (0 == i_clockwise)
				{
					mino.x = static_cast<char>(center_x + y);
					mino.y = static_cast<char>(center_y - x);
				}
				else
				{
					mino.x = static_cast<char>(center_x - y);
					mino.y = static_cast<char>(center_y + x);
				}
			}
		}
		else
		{
			//We don't rotate the mino that's located at the center of rotation
			for (unsigned char a = 1; a < minos.size(); a++)
			{
				//We find the position of the mino relative to the central mino
				char x = minos[a].x - minos[0].x;
				char y = minos[a].y - minos[0].y;

				if (0 == i_clockwise)
				{
					minos[a].x = y + minos[0].x;
					minos[a].y = minos[0].y - x;
				}
				else
				{
					minos[a].x = minos[0].x - y;
					minos[a].y = x + minos[0].y;
				}
			}
		}

		//We try every vector from the wall kick data
		for (Position& wall_kick : get_wall_kick_data(0 == shape, rotation, next_rotation))
		{
			bool can_turn = 1;

			for (Position& mino : minos)
			{
				//Here we're checking every collision that can happen
				if (0 > mino.x + wall_kick.x || COLUMNS <= mino.x + wall_kick.x || ROWS <= mino.y + wall_kick.y)
				{
					can_turn = 0;

					break;
				}

				if (0 > mino.y + wall_kick.y)
				{
					continue;
				}
				else if (0 < i_matrix[mino.x + wall_kick.x][mino.y + wall_kick.y])
				{
					can_turn = 0;

					break;
				}
			}

			//If we can turn
			if (1 == can_turn)
			{
				//We turn
				rotation = next_rotation;

				for (Position& mino : minos)
				{
					mino.x += wall_kick.x;
					mino.y += wall_kick.y;
				}

				return;
			}
		}

		//Since we applied changes to the minos array, we're resetting it when we can't rotate the tetromino
		minos = current_minos;
	}
}

void Tetromino::update_matrix(std::vector<std::vector<unsigned char>>& i_matrix)
{
	//Putting the tetromino to the matrix
	for (Position& mino : minos)
	{
		if (0 > mino.y)
		{
			continue;
		}

		i_matrix[mino.x][mino.y] = 1 + shape;
	}
}

std::vector<Position> Tetromino::get_ghost_minos(const std::vector<std::vector<unsigned char>>& i_matrix)
{
	//We're just moving the tetromino down until it hits something. Then we're returning it's position
	bool keep_falling = 1;

	unsigned char total_movement = 0;

	std::vector<Position> ghost_minos = minos;

	while (1 == keep_falling)
	{
		total_movement++;

		for (Position& mino : minos)
		{
			if (ROWS == total_movement + mino.y)
			{
				keep_falling = 0;

				break;
			}

			if (0 > total_movement + mino.y)
			{
				continue;
			}
			else if (0 < i_matrix[mino.x][total_movement + mino.y])
			{
				keep_falling = 0;

				break;
			}
		}
	}

	for (Position& mino : ghost_minos)
	{
		mino.y += total_movement - 1;
	}

	return ghost_minos;
}

std::vector<Position> Tetromino::get_minos()
{
	//Return minos (I'm so good at explaining stuff!)
	return minos;
}