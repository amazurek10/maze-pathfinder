
#include "MazeCell.h"

namespace DS_Maze {

	std::ostream& operator<< (std::ostream& outs, const MazeCell& source) {
		outs << source.getValue();
		return outs;
	}

	unsigned char MazeCell::nextMove() {
		if ((flags & FINISH) == FINISH) {
			//If we are at finish, do not suggest a new move
			return 0;
		}
		if (source != NORTH && isNorthOpen())
			return NORTH;
		if (source != EAST && isEastOpen())
			return EAST;
		if (source != SOUTH && isSouthOpen())
			return SOUTH;
		if (source != WEST && isWestOpen())
			return WEST;
		return 0;
	}

} /* namespace DS_Maze */