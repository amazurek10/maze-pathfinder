#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include <stack>
#include <sstream>
#include <string>

namespace DS_Maze {

	class Point {
	public:
		Point() { x = 0; y = 0; }
		Point(long ix, long iy) { x = ix; y = iy; }

		long getX() const { return x; }
		long getY() const { return y; }

		void set(long ix, long iy) { x = ix; y = iy; }
		bool operator==(const Point& r) { return x == r.x && y == r.y; }
		bool operator!=(const Point& r) { return !(*this == r); }
	private:
		long x;
		long y;
	};


	//Outputs a point in the form (x, y)
	std::ostream& operator <<(std::ostream& out, const Point& p);

	//Output a stack of points in format ->(x1, y1)->(x1,y2) where (x1,y1) is the bottom of the stack
	std::ostream& operator <<(std::ostream& outs, const std::stack<Point>& source);
}


#endif