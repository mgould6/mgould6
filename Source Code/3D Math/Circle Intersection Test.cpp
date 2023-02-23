#include "Header.h"
/*
Circle Intersection Test
Write a function which tests if two circles overlap.

The circles are described by a position and radius.

Return true if the circles exactly touch or are intersecting.

Return false otherwise.

Performance and accuracy are important.
https://tutorialspoint.dev/algorithm/geometric-algorithms/check-two-given-circles-touch-intersect
*/
bool CirclesIntersect(float x1, float y1, float r1, float x2, float y2, float r2)
{
    //distance between 2 cirles is calculated with the below formula
    // C1C2 = sqrt((x1 - x2)2 + (y1 - y2)2).


    /*
    *
    There are three condition arises.
1. If C1C2 == R1 + R2
     Circle A and B touch each other.

2. If C1C2 > R1 + R2
     Circle A and B do not touch each other.

3. If C1C2 < R1 + R2
      Circle intersects each other.
      */
    int distSq = (x1 - x2) * (x1 - x2) +
        (y1 - y2) * (y1 - y2);

    int radSumSq = (r1 + r2) * (r1 + r2);


    if (distSq == radSumSq)
        return 1;
    else if (distSq > radSumSq)
        return 0;
    else
        return 1;



    return false;	// Todo
}


int main()
{
    bool intersects = CirclesIntersect(0, 0, 5, 10, 0, 4);
    printf("CIRCLE INTERSECTION : %s\n\n", intersects ? "Yes" : "No");

    return 0;
}
