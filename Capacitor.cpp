#include "Capacitor.h"
#include <iostream>
using namespace std;

Capacitor::Capacitor(int start, int end, double c, double dt):
	Impedance(start, end), capacitance(c), dt(dt) { }

double Capacitor::get_capacitance()
{
	return capacitance;
}

double Capacitor::get_conductance()
{
	cout << "calling from capacitor" << endl;
	return capacitance / dt;
}

double Capacitor::get_current(double v_a, double v_b)
{
	return (v_b - v_a) / dt;
}