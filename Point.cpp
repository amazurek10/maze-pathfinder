
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include "Point.h"


namespace DS_Maze {


	std::ostream& operator <<(std::ostream& out, const Point& p) {
		out << "(" << p.getX() << ", " << p.getY() << ")";
		return out;
	}

	std::ostream& operator <<(std::ostream& outs, const std::stack<Point>& source) {
		//Make a copy of the stack that we can mutate it
		std::stack<Point> pstack(source);
		std::string s;

		while (!pstack.empty()) {
			std::ostringstream os;
			os << pstack.top();
			s.insert(0, "->" + os.str());
			pstack.pop();
		}
		outs << s;
		return outs;
	}

}