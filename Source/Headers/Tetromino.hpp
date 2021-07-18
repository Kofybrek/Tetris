#pragma once

class Tetromino
{
	unsigned char rotation;
	unsigned char shape;

	std::vector<Position> minos;
public:
	Tetromino(unsigned char i_shape, const std::vector<std::vector<unsigned char>>& i_matrix);

	bool move_down(const std::vector<std::vector<unsigned char>>& i_matrix);
	bool reset(unsigned char i_shape, const std::vector<std::vector<unsigned char>>& i_matrix);

	unsigned char get_shape();

	void hard_drop(const std::vector<std::vector<unsigned char>>& i_matrix);
	void move_left(const std::vector<std::vector<unsigned char>>& i_matrix);
	void move_right(const std::vector<std::vector<unsigned char>>& i_matrix);
	void rotate(bool i_clockwise, const std::vector<std::vector<unsigned char>>& i_matrix);
	void update_matrix(std::vector<std::vector<unsigned char>>& i_matrix);

	std::vector<Position> get_ghost_minos(const std::vector<std::vector<unsigned char>>& i_matrix);
	std::vector<Position> get_minos();
};