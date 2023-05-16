
#ifndef MAZECELL_H_
#define MAZECELL_H_

#include <iostream>
#include <stack>

namespace DS_Maze {

	class MazeCell {
	public:
		//Assume the cell is a wall
		MazeCell() { flags = WALL; source = 0; }

		//Return the flags, this is here to be able to OUTPUT the max with all the numbers
		const unsigned getValue() const { return flags; }

		//Declare the cell as NOT a wall
		void setOpen() { flags &= ~WALL; }

		//Precondition: No other cells reference this cell as a valid direction
		//Set the cell to be a wall, clears all other flags since food cannot be in a wall and so on
		void setClosed() { flags = WALL; }

		//===SOURCE===
		//Each cell maintains HOW the cell was last reached, called the source
		//For example, if a cell was reached by going north, source will be set to NORTH
		//A move cannot be taken to a SOURCE, this prevents looping inside a maze

		//Get the current source, will need to use MazeCell::NORTH, MazeCell::EAST,  MazeCell::SOUTH,  MazeCell::WEST,
		// to process the result
		unsigned char getSource() const { return source; }

		//void setSource(unsigned char isource) { source = isource; }

		//The following four sets the source to the desired
		void setSourceNorth() { source = NORTH; }
		void setSourceEast() { source = EAST; }
		void setSourceWest() { source = WEST; }
		void setSourceSouth() { source = SOUTH; }
		//Clear the source, as in, forget where we came from
		void clearSource() { source = 0; }

		//===MAINTAIN DIRECTION===
		//Each cell keeps track of which directions you can go from the cell as North, East, South, West
		// If a direction is open, a move is permitted in this direction
		// If a direction is closed, a move is NOT permitted in this direction
		void openNorth() { flags |= NORTH; }
		void openEast() { flags |= EAST; }
		void openWest() { flags |= WEST; }
		void openSouth() { flags |= SOUTH; }
		void addFood() { flags |= FOOD; }
		void closeNorth() { flags &= ~NORTH; }
		void closeEast() { flags &= ~EAST; }
		void closeWest() { flags &= ~WEST; }
		void closeSouth() { flags &= ~SOUTH; }
		//Conditionals for direction
		bool isNorthOpen() const { return (flags & NORTH) == NORTH; }
		bool isEastOpen() const { return (flags & EAST) == EAST; }
		bool isWestOpen() const { return (flags & WEST) == WEST; }
		bool isSouthOpen() const { return (flags & SOUTH) == SOUTH; }
		bool isBlocked() const { return !(isNorthOpen() || isEastOpen() || isSouthOpen() || isWestOpen()); }

		//Get the next move to take from the cell
		// North is always first, followed by clockwise order
		// Source cell is never selected
		// If no move available, 0 is returned
		unsigned char nextMove();

		//Is the cell a wall?
		bool isWall() const { return (flags & WALL) == WALL; }

		//Is the cell NOT a wall?
		bool isOpen() const { return (flags & !WALL) == 0; }

		//Is food contained in the cell?
		bool isFood() const { return (flags & FOOD) == FOOD; }

		//Sets the start of the maze, used by Maze
		void setStart() { flags |= START; }
		//Sets the finish of the maze, used by Maze
		void setFinish() { flags |= FINISH; }
		//Is the cell the start cell
		bool isStartCell() const { return (flags & START) == START; }
		//Is the cell the finish cell
		bool isFinishCell() const { return (flags & FINISH) == FINISH; }
		//Use these by using the scope operator, MazeCell::NORTH and so on
		static const unsigned char NORTH = 8;
		static const unsigned char EAST = 16;
		static const unsigned char WEST = 32;
		static const unsigned char SOUTH = 64;
	private:
		static const unsigned char WALL = 1;
		static const unsigned char START = 2;
		static const unsigned char FINISH = 128;
		static const unsigned char FOOD = 4;
		unsigned char flags;
		unsigned char source;
	};

	//Output a cells flags
	std::ostream& operator <<(std::ostream&, const MazeCell&);



} /* namespace DS_Maze */

#endif /* MAZECELL_H_ */