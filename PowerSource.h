#ifndef PowerSource_H
#define PowerSource_H

#include "Element.h"

class PowerSource: public Element
{
public:
	PowerSource(int start, int end, double v);
	double get_voltage();
private:
	double voltage;
};

#endif