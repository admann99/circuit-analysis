#ifndef Resistor_H
#define Resistor_H

#include "Element.h"
#include "Impedance.h"

class Resistor: public Impedance
{
public:
	Resistor(int start, int end, double r);
	double get_resistance();
	virtual double get_conductance();
private:
	double resistance;
};

#endif