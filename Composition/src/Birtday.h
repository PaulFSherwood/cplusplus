/*
 * Birtday.h
 *
 *  Created on: May 6, 2011
 *      Author: grrwood
 */

#ifndef BIRTDAY_H_
#define BIRTDAY_H_

class Birthday
{
public:
	Birthday(int m, int d, int y);
	void printDate();
private:
	int month;
	int day;
	int year;
};

#endif /* BIRTDAY_H_ */
