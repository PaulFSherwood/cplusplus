#ifndef _PID_H_
#define _PID_H_

class PIDImpl;
class PID {
	public:
		// Kp - Proportional gain
		// Ki - Integral gain
		// Kd - derivative gain
		// dt - loop interval time
		// max - maximum value of manipulated variable
		// min - minimum value of manipulated varaible
		PID(double dt, double max, double min, double Kp, double Kd, double Ki);

		// Returns the mainipulated variable given a setpoint and current process value
		double calculate(double setpoint, double pv);
		~PID();

private:
	PIDImpl *pimpl;
};

#endif