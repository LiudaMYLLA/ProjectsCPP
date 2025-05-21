
#include <iostream>
#include <vector>

namespace Acces_to = std;
using Integer = int;
using Matrix = Acces_to::vector<Acces_to::vector<Integer>>;

struct Board {
public: 
	Matrix board = {
	{1,	 2,	 3,	 4,  5},
	{6,	 7,	 8,	 9,	 10},
	{11, 12, 0,	 13, 14},
	{15, 16, 17, 18, 19},
	{20, 21, 22, 23, 24}
	};

	Integer step = 1;
};

static Matrix Knights_tour5x5(Matrix& board, Integer x = 2, Integer y = 2, Acces_to::vector<int>& used_pos,Integer step) {
	Acces_to::vector<int> X = { -1, 1, -2, 2, -2, 2, -1, 1 };
	Acces_to::vector<int> Y = { 2, 2, 1, 1, -1, -1, -2, -2 };

	Integer nextX;
	Integer nextY;
	board[y][x] = step;
	// Possible movements at start
	// 1. x: 2-1 = 1	y: 2+2 = 4		(21)
	// 2. x: 2+1 = 3	y: 2+2 = 4		(23)
	// 3. x: 2-2 = 0	y: 2+1 = 3		(15)
	// 4. x: 2+2 = 4	y: 2+1= 3		(19)
	// ...

	Acces_to::vector<int> possible_moves;
	// Finding all possible movements for current position of a knight
	for (Integer i = 0; i < 8; i++) {
		nextY = y + Y[i];
		nextX = x + X[i]; 				

		if (nextX >= 0 && nextY >= 0 && nextX < 5 && nextY < 5 && board[nextY][nextX]) {
			possible_moves.push_back(board[nextY][nextX]);
		}
	}

	// Finding the smolest one to detect next step
	Integer smolest = possible_moves[0];

	for (int i = 0; i < possible_moves.size(); i++) { 
		bool already_used = false;

		for (int j = 0; j < used_pos.size(); j++) { // for each elem from first vector we go throug all elems from second vector and if it's the same then deleting
			if (possible_moves[i] == used_pos[j]) {
				already_used = true;
				break;
			}
		}
		// At this step we have deleted all elems from possible_moves that was used before and correctly define smolest
		if (!already_used) {
			if (smolest > possible_moves[i]) {
				smolest = possible_moves[i];
			}
		}
	}

	if (possible_moves.size() == 0) return board;

	used_pos.push_back(smolest);
	// move a knight to next field
	for (int i = 0; i <= 4; ++i) {
		for (int j = 0; j <= 4; ++j) {
			if (board[i][j] == smolest) {
				Knights_tour5x5(board, j, i, used_pos, step + 1); // Call the func again with new new position
				return board;
			}
		}
	}	
	return board;
}