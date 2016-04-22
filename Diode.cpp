#include "Diode.h"
#include <iostream>
using namespace std;

Diode::Diode(int start, int end, double Is, double Vt, double dt) :
	Impedance(start, end), Is(Is), Vt(Vt), dt(dt) { }

double Diode::get_conductance()
{
	cout << "calling from Diode" << endl;
	double Vd0 = anode - cathode;
	return (Vd0<0) ? GMIN : (Is/Vt) * exp(Vd0/Vt)
	
}

double Diode::set_voltage(double a, double c) {
	anode = a;
	cathode = c;
}

double Diode::get_current(double v_a, double v_b)
{
	set_voltage(v_a, v_b);
	double Vd0 = v_a - v_b;
	double Id0 = Is * exp((Vd0 / Vt) - 1);
	return (Vd0 < 0) ? 0.0 : Id0 - get_conductance() * Vd0;
}