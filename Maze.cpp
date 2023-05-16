
#include <stdexcept>
#include <vector>
#include "Maze.h"

namespace DS_Maze {

	Maze::Maze(const std::string& fName) {
		readFile(fName);
	}

	Maze::Maze() {
		resetMaze();
	}

	Maze::~Maze() {
		resetMaze();
	}

	Maze::Maze(const Maze& source) {
		copyMaze(source);
	}

	Maze& Maze::operator=(const Maze& source) {
		//Test for self assignment
		if (this == &source)
			return *this;
		//Clear old maze
		resetMaze();
		copyMaze(source);
		return *this;
	}

	void Maze::copyMaze(const Maze& source) {
		row_count = source.row_count;
		col_count = source.col_count;
		food_count = source.food_count;
		food_consumed = source.food_consumed;
		if (source.matrix != nullptr) {
			matrix = new std::vector<MazeCell>(*source.matrix);
			start = source.start;
			end = source.end;
			currentLocation = matrix->begin() + (source.currentLocation - source.matrix->begin());
		}
		else
			matrix = nullptr;
	}

	void Maze::resetMaze() {
		row_count = col_count = food_count = food_consumed = 0;
		matrix = nullptr;
		start = Point();
		end = Point();
		if (matrix != nullptr)
			delete matrix;
	}

	std::ostream& operator <<(std::ostream& out, const Maze& maze) {
		std::vector<MazeCell>::iterator it;
		std::size_t i;

		for (it = maze.matrix->begin(), i = 0; it < maze.matrix->end(); ++it, ++i) {
			if ((*it).isFinishCell()) {
				out << (it == maze.currentLocation ? std::setfill('*') : std::setfill(' ')) << std::setw(3) << "f" << " ";
			}
			else if (it == maze.currentLocation) {
				out << std::setfill('*') << std::setw(3) << *it << " ";
			}
			else if ((*it).isStartCell()) {
				out << std::setfill('s') << std::setw(3) << *it << " ";
			}
			else if ((*it).isFood()) {
				out << std::setfill('+') << std::setw(3) << *it << " ";
			}
			else {
				if (i % maze.row_count == 0)
					out << std::endl;
				out << std::setfill(' ') << std::setw(3) << *it << " ";
			}
		}
		return out;
	}

	void Maze::readFile(const std::string& fname) {
		std::ifstream fmaze;
		int cell;
		const unsigned char OPEN = 0;
		const unsigned char OPENMASK = 1; //Special
		//const unsigned char WALL = 1;
		const unsigned char START = 2;
		const unsigned char END = 4;
		const unsigned char FOOD = 8;

		resetMaze();
		fmaze.open(fname);
		if (fmaze.is_open()) {
			//Get size of maze matrix
			fmaze >> row_count;
			fmaze >> col_count;

			//Allow for walls
			row_count += 2;
			col_count += 2;

			matrix = new std::vector<MazeCell>(row_count * col_count);

			for (size_t r = 1; r < row_count - 1; ++r) {
				for (unsigned int c = 1; c < col_count - 1; ++c) {

					fmaze >> cell;

					if ((cell & START) == START) {
						if (start.getX() == 0) {
							start.set(r, c);
							matrix->at(r * col_count + c).setStart();
						}
						else
							throw std::runtime_error("Maze integrity violated, multiple starts found.");
					}

					if ((cell & END) == END) {
						if (end.getX() == 0) {
							end.set(r, c);
							matrix->at(r * col_count + c).setFinish();
						}
						else
							throw std::runtime_error("Maze integrity violated, multiple ends found.");
					}

					if ((cell & OPENMASK) == OPEN) {
						matrix->at(r * col_count + c).setOpen();

						if ((cell & FOOD) == FOOD) {
							++food_count;
							matrix->at(r * col_count + c).addFood();
						}
					}

					if (r > 1) {
						if (!matrix->at(r * col_count + c).isWall() && !matrix->at((r - 1) * col_count + c).isWall()) {
							matrix->at((r - 1) * col_count + c).openSouth();
							matrix->at(r * col_count + c).openNorth();
						}
					}
					if (c > 1) {
						if (!matrix->at(r * col_count + c).isWall() && !matrix->at(r * col_count + c - 1).isWall()) {
							matrix->at(r * col_count + c).openWest();
							matrix->at(r * col_count + c - 1).openEast();
						}
					}


				}
			}
			fmaze.close();
			if (start.getX() == 0) {
				//If maze source text file does not have a start, start in upper left
				start.set(1, 1);
				matrix->at(col_count + 1).setStart();
			}
			if (end.getX() == 0) {
				//If maze source text file does not have an end, end in lower right
				end.set(row_count - 2, col_count - 2);
				matrix->at((col_count - 2) * col_count + col_count - 2).setFinish();
			}
			currentLocation = matrix->begin() + start.getY() * col_count + start.getX();

		}
		else {
			throw std::runtime_error("Unable to open file, check file path.");
		}
	}


	Point Maze::goBack() {
		if ((*currentLocation).isFood())
			--food_consumed;
		switch ((*currentLocation).getSource()) {
		case MazeCell::NORTH:
			return goNorth(false);
		case MazeCell::EAST:
			return goEast(false);
		case MazeCell::SOUTH:
			return goSouth(false);
		case MazeCell::WEST:
			return goWest(false);
		default:
			throw std::runtime_error("No moves left.");
		}
	}

	Point Maze::goNorth(bool setSource/*=true*/) {
		if (!(*currentLocation).isNorthOpen())
			throw std::runtime_error("Unable to move in this direction due to wall.");

		currentLocation -= col_count;
		if (setSource) {
			(*currentLocation).setSourceSouth();
			consumeFood();
		}
		return getPosition();
	}

	Point Maze::goEast(bool setSource/*=true*/) {
		if (!(*currentLocation).isEastOpen())
			throw std::runtime_error("Unable to move in this direction due to wall.");

		++currentLocation;
		if (setSource) {
			(*currentLocation).setSourceWest();
			consumeFood();
		}
		return getPosition();
	}

	Point Maze::goWest(bool setSource/*=true*/) {
		if (!(*currentLocation).isWestOpen())
			throw std::runtime_error("Unable to move in this direction due to wall.");

		--currentLocation;
		if (setSource) {
			(*currentLocation).setSourceEast();
			consumeFood();
		}
		return getPosition();
	}

	Point Maze::goSouth(bool setSource/*=true*/) {
		if (!(*currentLocation).isSouthOpen())
			throw std::runtime_error("Unable to move in this direction due to wall.");

		currentLocation += col_count;
		if (setSource) {
			(*currentLocation).setSourceNorth();
			consumeFood();

		}
		return getPosition();
	}

	/*
	Point Maze::goNext() {
	return go((*currentLocation).nextMove());
	}*/

	unsigned int Maze::getNext() const {
		return (*currentLocation).nextMove();
	}

	/*
	Point Maze::go(unsigned char direction) {
	switch ( direction ) {
	case MazeCell::NORTH:
	return goNorth();
	case MazeCell::EAST:
	return goEast();
	case MazeCell::SOUTH:
	return goSouth();
	case MazeCell::WEST:
	return goWest();
	default:
	throw std::runtime_error("No moves left.");
	}
	}*/

	void Maze::consumeFood() {
		if ((*currentLocation).isFood())
			++food_consumed;
	}

	MazeCell& Maze::getCell(const Point& p) {
		return matrix->at(p.getX() * col_count + p.getY());
	}

	void Maze::detourCell(const Point& p) {
		size_t index = p.getX() * col_count + p.getY();
		switch (matrix->at(index).getSource()) {
		case MazeCell::NORTH:
			matrix->at(index).closeNorth();
			matrix->at(index - row_count).closeSouth();
			break;
		case MazeCell::EAST:
			matrix->at(index).closeEast();
			matrix->at(index + 1).closeWest();
			break;
		case MazeCell::SOUTH:
			matrix->at(index).closeSouth();
			matrix->at(index + col_count).closeNorth();
			break;
		case MazeCell::WEST:
			matrix->at(index).closeWest();
			matrix->at(index - 1).closeEast();
			break;
		}
		matrix->at(index).clearSource();
	}

	
	/*void Maze::closeCell(const Point& p) {
		size_t index = p.getX()*col_count + p.getY();
		matrix->at(index).setClosed();
		matrix->at(index-col_count).closeSouth();
		matrix->at(index-1).closeEast();
		matrix->at(index+1).closeWest();
		matrix->at(index+row_count).closeNorth();
	}*/

	Point Maze::getPosition() const {
		size_t index = currentLocation - matrix->begin();
		return Point(index / col_count, index % col_count);
	}

	// Originally && (food taken into account)
	bool Maze::isSuccess() const {
		return getPosition() == end || food_consumed == food_count;
	}

	bool Maze::isFailure() const {
		return getNext() == 0 && (*currentLocation).getSource() == 0;
	}

} /* namespace DS_Maze */