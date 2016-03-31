#include "CurrentSource.h"

CurrentSource::CurrentSource(int start, int end, double c):
	Element(start, end), current(c) { }

double CurrentSource::get_current()
{
	return current;
}