#ifndef IMPEDANCE_H
#define IMPEDANCE_H

class Impedance: public Element
{
public:
	Impedance(int start, int end): Element(start, end) {}
	virtual double get_conductance() = 0;
};

#endif