#pragma once

//The size of the cell
constexpr unsigned char CELL_SIZE = 8;
//The duration of the line clearing effect
constexpr unsigned char CLEAR_EFFECT_DURATION = 8;
//Number of columns
constexpr unsigned char COLUMNS = 10;
//Lines needed to increase the game speed
constexpr unsigned char LINES_TO_INCREASE_SPEED = 2;
//The movement speed
constexpr unsigned char MOVE_SPEED = 4;
//I feel like my explanations are just longer versions of the names
constexpr unsigned char ROWS = 20;
//Screen resize
constexpr unsigned char SCREEN_RESIZE = 4;
//Soft drop speed
constexpr unsigned char SOFT_DROP_SPEED = 4;
//Fall speed at the start of the game. Lower the value, faster the falling
constexpr unsigned char START_FALL_SPEED = 32;

//The duration of every frame
constexpr unsigned short FRAME_DURATION = 16667;

//I just realized I could use the Vector2 in the SFML! I'M SO STUPID!
struct Position
{
	char x;
	char y;
};