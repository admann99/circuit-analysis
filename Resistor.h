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