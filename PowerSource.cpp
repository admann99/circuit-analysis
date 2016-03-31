#include "PowerSource.h"

PowerSource::PowerSource(int start, int end, double v):
	Element(start, end), voltage(v) { }

double PowerSource::get_voltage()
{
	return voltage;
}