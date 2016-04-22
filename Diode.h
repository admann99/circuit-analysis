#ifndef DIODE_H
#define DIODE_H

#include "Element.h"
#include "Impedance.h"

class Diode: public Impedance
{
public:
	Diode(int start, int end, double Is, double Vt, double dt);
	double Diode::set_voltage(double v_a, double v_b);
	double get_conductance();
	double get_current(double v_a, double v_b);
	double step_time();
private:
	double Is;
	double Vt;
	double dt;
	double elapsed_time;
	double anode;
	double cathode;
};

#endif