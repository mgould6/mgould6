#include "Header.h";

using namespace std;

/*
Clock Angle Problem
Google Translate Icon
Clock Angle Problem: Given time in hh:mm format in 24-hour notation, calculate the shorter angle between the hour and minute hand in an analog clock.

For example,

Input:  5:30
Output: 15°


Input:  21:00
Output: 90°


Input:  12:00
Output: 0°

Please note that hh:60 should be considered as (hh+1):0
Practice This Problem

The idea is to consider the rate of change of the angle in degrees per minute. The hour hand of a 12–hour analog clock turns 360° in 12 hours, and the minute hand rotates through 360° in 60 minutes. So, we can calculate the angle in degrees of the hour hand minute hand separately and return their difference using the following formula:

Degree(hh) = H×(360/12) + (M×360)/(12×60)
Degree(mm) = M×(360/60)
Here, H is the hour, and M is the minutes past the hour. The angle should be in degrees and measured clockwise from the 12 o’clock position of the clock. If the angle is greater than 180°, take its difference with 360.


Following is the C++


*/

// function to compute the angle between the hour and the minute hand
int findAngle(int hh, int mm)
{
	// handle 24 hour notation 
	hh = hh % 12;

	// find the position of the hours hand
	int h = (hh * 360) / 12 + (mm * 360) / (12 * 60);

	// find the position of the minutes hand
	int m = (mm * 360) / (60);

	// calculate the angle difference
	int angle = abs(h - m);

	// consider the shorter angle and return it
	if (angle > 180)
	{
		angle = 360 - angle;
	}
	return angle;
}

int main()
{

	int hh = 5;
	int mm = 30;

	cout << findAngle(hh, mm);
	return 0;
}

/*

*/