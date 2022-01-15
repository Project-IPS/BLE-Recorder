#ifndef POSITION_H
#define POSITION_H

class Position{
private:
	int x;
	int y;
	int z;

public:

	Position(int x, int y, int z) : x{x}, y{y}, z{z}{}

	Position(const Position&) = default;
	Position& operator=(const Position&) = default;

	Position(Position&&) = default;
	Position& operator=(Position&&) = default;

	int getX() const{
		return x;
	}
	int getY() const{
		return y;
	}
	int getZ() const{
		return z;
	}

	void setX(int pos_x){
		x=pos_x;
	}
	void setY(int pos_y){
		y=pos_y;
	}
	void setZ(int pos_z){
		z=pos_z;
	}

	string toString() const{
		string str = "("+to_string(x)+","+to_string(y)+","+to_string(z)+")";
		return str;
	}
};

#endif
