#ifndef CurrentSource_H
#define CurrentSource_H

#include "Element.h"

class CurrentSource: public Element
{
public:
	CurrentSource(int start, int end, double c);
	double get_current();
private:
	double current;
};

#endif