#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "Element.h"
#include "Impedance.h"

class Capacitor: public Impedance
{
public:
	Capacitor(int start, int end, double capacitance, double dt);
	virtual double get_capacitance();
	double get_conductance();
	double get_current(double v_a, double v_b);
	double step_time();
private:
	double capacitance;
	double dt;
	double elapsed_time;
};

#endif