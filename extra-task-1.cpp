#include <assert.h>
#include <iostream>
using namespace std;
double seconds_difference(double time_1, double time_2)
{
	return time_2 - time_1;
	
}

double hours_difference(double time_1, double time_2)
{
	return (time_2 - time_1) / 3600.0;
}

double to_float_hours(int hours, int minutes, int seconds)
{
	assert((minutes>=0)&&(minutes<60)&&(seconds>=0)&&(seconds<60));
	return hours * 1.0 + minutes / 60.0 + seconds / 3600.0;
}

double to_24_hour_clock(double hours)
{
	assert(hours>=0);
	while (hours > 23)
		hours -= 24;
	return hours;
}

int get_hours(int seconds)
{
	return seconds / 3600;
	
}
int get_minutes(int seconds)
{
	return (seconds - get_hours(seconds)*3600) / 60;
}
int get_seconds(int seconds)
{
	return seconds - get_hours(seconds)*3600 - get_minutes(seconds)*60;
}

double time_to_utc(int utc_offset, double time)
{
	double x = time - utc_offset;
	while (x > 23) x -= 24;
	if (x < 0) x += 24;
	return x;
}

double time_from_utc(int utc_offset, double time)
{
	double x = time + utc_offset;
	while (x > 23) x -= 24;
	if (x < 0) x += 24;
	return x;

}
int main()
{
	assert(abs(seconds_difference(1800.0, 3600.0) - 1800.0)<DBL_EPSILON);
	assert(abs(seconds_difference(3600.0, 1800.0) + 1800.0)<DBL_EPSILON);
	assert(abs(seconds_difference(1800.0, 2160.0) - 360.0)<DBL_EPSILON);
	assert(abs(seconds_difference(1800.0, 1800.0) - 0.0)<0.01);
	cout << "ok"<<endl;
	//
	assert(abs(hours_difference(1800.0, 3600.0) - 0.5)<DBL_EPSILON);
	assert(abs(hours_difference(3600.0, 1800.0) + 0.5)<DBL_EPSILON);
	assert(abs(hours_difference(1800.0, 2160.0) - 0.1)<DBL_EPSILON);
	assert(abs(hours_difference(1800.0, 1800.0) - 0.0)<DBL_EPSILON);
	cout << "ok" << endl;
	//
	assert(abs(to_float_hours(0, 15, 0) - 0.25)<DBL_EPSILON);
	assert(abs(to_float_hours(2, 45, 9) - 2.7525)<DBL_EPSILON);
	assert(abs(to_float_hours(1, 0, 36) - 1.01)<DBL_EPSILON);
	cout << "ok" << endl;
	//
	assert(abs(to_24_hour_clock(24) - 0)<DBL_EPSILON);
	assert(abs(to_24_hour_clock(48) - 0)<DBL_EPSILON);
	assert(abs(to_24_hour_clock(25) - 1)<DBL_EPSILON);
	assert(abs(to_24_hour_clock(4) - 4)<DBL_EPSILON);
	assert(abs(to_24_hour_clock(28.5) - 4.5)<DBL_EPSILON);
	cout << "ok" << endl;
	//
	assert(get_hours(3800) == 1);
	assert(get_minutes(3800) == 3);
	assert(get_seconds(3800) == 20);
	cout << "ok" << endl;
	//
	assert(abs(time_to_utc(0, 12.0) - 12.0)<DBL_EPSILON);
	assert(abs(time_to_utc(1, 12.0) - 11.0)<DBL_EPSILON);
	assert(abs(time_to_utc(-1, 12.0) - 13.0)<DBL_EPSILON); 
	assert(abs(time_to_utc(-11, 18.0) - 5.0)<DBL_EPSILON); 
	assert(abs(time_to_utc(-1, 0.0) - 1.0)<DBL_EPSILON); 
	assert(abs(time_to_utc(-1, 23.0) - 0.0)<DBL_EPSILON); 
	cout << "ok" << endl;
	//
	assert(abs(time_from_utc(+0, 12.0) - 12.0)<DBL_EPSILON);
	assert(abs(time_from_utc(+1, 12.0) - 13.0)<DBL_EPSILON);
	assert(abs(time_from_utc(+-1, 12.0) - 11.0)<DBL_EPSILON);
	assert(abs(time_from_utc(+6, 6.0) - 12.0)<DBL_EPSILON);
	assert(abs(time_from_utc(-7, 6.0) - 23.0)<DBL_EPSILON);
	assert(abs(time_from_utc(-1, 0.0) - 23.0)<DBL_EPSILON);
	assert(abs(time_from_utc(-1, 23.0) - 22.0)<DBL_EPSILON);
	assert(abs(time_from_utc(+1, 23.0) - 0.0)<DBL_EPSILON);
	cout << "ok" << endl;

	system("pause");
}
