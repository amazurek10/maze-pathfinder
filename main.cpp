
#include "Maze.h"
#include "MazeCell.h"
#include "Point.h"

#include <iostream>
#include <vector>
#include <stack>

bool checkVisited(std::vector<DS_Maze::Point>& v, DS_Maze::Point p) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i].getX() == p.getX() && v[i].getY() == p.getY()) {
			return true;
		}
	}

	return false;
}

int main(int argc, char* argv[])
{
	for (size_t argi = 1; argi < argc; ++argi)
	{
		std::cout << std::endl << std::endl;
		std::cout << "/////////////////////" << std::endl;
		std::cout << "//    ";
		std::cout << argv[argi];
		std::cout << "    //" << std::endl;
		std::cout << "/////////////////////" << std::endl;

		// Create Maze and read in text files
		DS_Maze::Maze m(argv[argi]);

		std::stack<DS_Maze::Point> stack;
		std::vector<DS_Maze::Point> visited;
		std::stack<DS_Maze::Point> path;

		stack.push(m.getPosition());
		visited.push_back(m.getPosition());
		
		while (!stack.empty()) {
			DS_Maze::Point current = stack.top();
			stack.pop();
			path.push(current);

			switch (m.getNext()) {
				case 8:
					m.goNorth();
					stack.push(m.getPosition());
					visited.push_back(m.getPosition());
					continue;
						
				case 16:
					m.goEast();
					stack.push(m.getPosition());
					visited.push_back(m.getPosition());
					continue;

				case 64:
					m.goSouth();
					stack.push(m.getPosition());
					visited.push_back(m.getPosition());
					continue;

				case 32:
					m.goWest();
					stack.push(m.getPosition());
					visited.push_back(m.getPosition());
					continue;

			}
		}

		std::cout << m << std::endl;

		if (m.getNext() == 0 && !m.getCell(m.getPosition()).isFinishCell()) {
			std::cout << std::endl << "Stuck in a dead end. No path was found." << std::endl;
		} else if (m.isSuccess()) {
			std::cout << std::endl << "Path has been found! " << std::endl;
			std::cout << path << std::endl << std::endl;
		}
		else if (m.isFailure()) {
			std::cout << "No path able to be found." << std::endl;
		}
		
	}

	system("pause");
	return 0;
}

