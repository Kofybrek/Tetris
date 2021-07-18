#pragma once

class Tetromino
{
	unsigned char rotation;
	unsigned char shape;

	std::vector<Position> minos;
public:
	Tetromino(unsigned char i_shape, const Matrix& i_matrix);

	bool move_down(const Matrix& i_matrix);
	bool reset(unsigned char i_shape, const Matrix& i_matrix);

	unsigned char get_shape();

	void hard_drop(const Matrix& i_matrix);
	void move_left(const Matrix& i_matrix);
	void move_right(const Matrix& i_matrix);
	void rotate(bool i_clockwise, const Matrix& i_matrix);
	void update_matrix(Matrix& i_matrix);

	std::vector<Position> get_ghost_minos(const Matrix& i_matrix);
	std::vector<Position> get_minos();
};