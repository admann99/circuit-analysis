#include "Resistor.h"

Resistor::Resistor(int start, int end, double r):
	Element(start, end), resistance(r) { }

double Resistor::get_resistance()
{
	return resistance;
}

double Resistor::get_conductance()
{
	return 1/resistance;
}