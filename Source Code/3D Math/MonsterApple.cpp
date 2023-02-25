#include "Header.h"
/*
Monster Facing Apple
In our game, we have a monster which is looking for apples. Implement a function which returns if a given apple position is in front of a monster with a given position and facing direction (unit vector).

The apple is considered to be in front of the monster if it is 90 degrees or less from the facing direction of the monster. Putting this another way, it's in front if it's within the monster's 180 degree field of vision.

You may use the vector3 class, but do not modify it, and note that you should USE NO OTHER REFERENCE.
https://iq.opengenus.org/dot-product-of-two-vectors-in-cpp/#:~:text=In%20vector%20algebra%20dot%20product,y%20and%20z%20directions%20respectively.
*/

// Vector3 class and functions. DO NOT MODIFY.
class vector3 {
public:
	float x, y, z;
	vector3() {}
	vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	bool operator==(const vector3& v) const { return x == v.x && y == v.y && z == v.z; }

	vector3 operator+=(const vector3& v) { x += v.x;  y += v.y;  z += v.z;  return *this; }

	vector3 operator*=(float s) { x *= s;  y *= s;  z *= s;  return *this; }

	vector3 operator/=(float s) { float r = 1.0f / s;  x *= r;  y *= r;  z *= r;  return *this; }
	float Length() { return sqrt(x * x + y * y + z * z); }
};

vector3 operator+(const vector3& v0, const vector3& v1) { return vector3(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z); }

vector3 operator-(const vector3& v0, const vector3& v1) { return vector3(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z); }

vector3 operator*(const vector3& v, float s) { return vector3(v.x * s, v.y * s, v.z * s); }
vector3 operator*(float s, const vector3& v) { return v * s; }

vector3 operator/(const vector3& v, float s) { return v * (1.0f / s); }

float dot(const vector3& v0, const vector3& v1) { return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z; }

vector3 cross(const vector3& v0, const vector3& v1) { return vector3(v0.y * v1.z - v0.z * v1.y, v0.z * v1.x - v0.x * v1.z, v0.x * v1.y - v0.y * v1.x); }

float norm(const vector3& v) { return sqrt(dot(v, v)); }

vector3 unit(const vector3& v) { return v / norm(v); }

vector3 operator-(const vector3& v) { return vector3(-v.x, -v.y, -v.z); }


// Return whether an apple position is in front of a monster with a given position and direction




bool IsAppleInFrontOfMonster(vector3& monsterPos, vector3& monsterFacingDirection, vector3& applePos) {



	//
	vector3 unitV = monsterFacingDirection; //normalize the monster direction to find the unit vector
	float LOS = 90; //declare line of sight angle
	vector3 P = monsterPos - applePos; //draw a line between monster apple 

	float test = cos(LOS);

	printf("test: %f\n ", test);

	float l = norm(P);
	vector3 p = P / l; //normalize P vector then convert it to unit length
	float test2 = dot(p, unitV);
	printf("test2: %f\n ", test2);

	if (dot(p, unitV) > cos(LOS)) //get the dot product of normalized vector and compare to LOS angle
		return false;
	else
		return true;
}

int main()
{
	vector3 monsterPos(10, 0, 0);
	vector3 monsterDir(1, 1, 0);
	vector3 applePos(2, 0, 0);






	bool infront = IsAppleInFrontOfMonster(monsterPos, monsterDir, applePos);
	printf("APPLE IS %s MONSTER", infront ? "IN FRONT OF" : "BEHIND");

	return 0;
}