/*
 * Sally.h
 *
 *  Created on: May 6, 2011
 *      Author: grrwood
 */

#ifndef SALLY_H_
#define SALLY_H_

class Sally {

public:

	Sally();
	void print();
	void dance();
	void talk();
	void talk2() const;

	virtual ~Sally();
};

class Pally {
public:
	Pally(int a, int b);
	void print();

private:
	int regVar;
	const int constVar;
};

#endif /* SALLY_H_ */
