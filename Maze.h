#ifndef MAZE_H_
#define MAZE_H_


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

#include "MazeCell.h"
#include "Point.h"

namespace DS_Maze {

	class Maze {
	public:
		//Contructors and other items to make Maze variant safe
		Maze();
		Maze(const Maze&);
		~Maze();
		Maze& operator=(const Maze&);


		//Create a maze and load a file, will crash if text file is invalid
		Maze(const std::string&);
		//Load a maze file, will crash if text file is invalid
		void readFile(const std::string& fname);



		//==MAZE LOCATION==
		//At any time, the instance will maintain where you are in the maze
		//You can change direction various ways:

		//goNorth,goEast,goWest,goSouth
		//Go to the cell in the chosen direction
		//Will crash if the direction is invalid
		//The new cells source is updated to reference where you came from, unless the passed bool is false
		Point goNorth(bool = true);
		Point goEast(bool = true);
		Point goWest(bool = true);
		Point goSouth(bool = true);


		//Go back to source from current location
		Point goBack();

		//Returns to the next direction to take in N,E,S,W order, ignoring original cells source
		unsigned int getNext() const;

		//Get the cell at the following point (row,col), this is a very important function since
		// it gives you access to the MazeCells member functions
		MazeCell& getCell(const Point&);

		//Set the cell at Point to not be accessible by the source, this is important when you need to backtrack
		void detourCell(const Point& p);

		//Get the current position in the maze
		Point getPosition() const;

		//True if current position is at FINISH and ALL food was consumed
		bool isSuccess() const;

		//True if current position is at START and you cannot go anywhere else
		// it is possible that maze is NOT solvable
		bool isFailure() const;

		//Get the amount of food that exists in the maze
		std::size_t getFoodCount() const { return food_count; }

		//Get the amount of food found in the maze
		std::size_t getFoodConsumed() const { return food_consumed; }

		//Output the entire maze in a numeric format, the output here will take time to understand
		//s = start
		//f = finish
		//* = current position
		//SOME numbers you will see
		//1 = Wall
		//24 = can go North and East
		//48 = Can go East and West
		//72 = Can go North and South
		friend std::ostream& operator <<(std::ostream&, const Maze&);

	private:
		//Check if current location has food and consume it
		void consumeFood();

		void copyMaze(const Maze&);
		void resetMaze();
		std::vector<MazeCell>* matrix;
		Point start;
		Point end;
		std::size_t row_count;
		std::size_t col_count;
		std::size_t food_count;
		std::size_t food_consumed;
		std::vector<MazeCell>::iterator currentLocation;
	};

}

#endif