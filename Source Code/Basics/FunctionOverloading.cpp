#include "Header.h";

using namespace std;


void print(const char* str)
{
	printf("log: %s\n", str);
}

void print(int i)
{
	printf("log: %d\n", i);
}

void print(float f)
{
	printf("log: %f\n", f);
}


int main()
{
	print(.5f);
	print("hi");

	return 0;
}



