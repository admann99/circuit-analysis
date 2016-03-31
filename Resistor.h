#ifndef Resistor_H
#define Resistor_H

#include "Element.h"

class Resistor: public Element
{
public:
	Resistor(int start, int end, double r);
	double get_resistance();
	double get_conductance();
private:
	double resistance;
};

#endif