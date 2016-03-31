#ifndef CurrentSource_H
#define CurrentSource_H

#include "Element.h"

class CurrentSource: public Element
{
public:
	CurrentSource(int start, int end, double c);
	int get_start_node();
	int get_end_node();
	double get_current();
private:
	int start_node;
	int end_node;
	double current;
};

#endif