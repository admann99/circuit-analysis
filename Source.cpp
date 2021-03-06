/*
Matthew Vater, Adam Mannheim, Nathan Spangler
mav78@pitt.edu, amm349@pitt.edu, njs55@pitt.edu
30 March 2016
SPICE Simulator
*/
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <armadillo>
#include "\Python32\include\Python.h"
#include "CurrentSource.h"
#include "Element.h"
#include "PowerSource.h"
#include "Resistor.h"
#include "Capacitor.h"
#include "Impedance.h"
#include "Diode.h"

#define PYRUN(...) sprintf(cmd_str,__VA_ARGS__); (PyRun_SimpleString(cmd_str) < 0 ? getchar():1);
#define CIRCUIT 0
#define RUNTIME 6e-6
#define DT 1e-6


arma::vec linear_system_solver(arma::mat A, arma::vec x, arma::vec z)
{
	if (!arma::solve(x, A, z)) {
		//handle error
	}
}


void get_conductance_matrix(arma::mat *g, Impedance **impedances, int num_impedances)
{
	for(int i=0; i<num_impedances; i++)
	{
		int a = impedances[i]->get_start_node();
		int b = impedances[i]->get_end_node();
		
		if(a != 0)
		{
			(*g)(a-1, a-1) += impedances[i]->get_conductance();
		}
		if(b != 0)
		{
			(*g)(b-1, b-1) += impedances[i]->get_conductance();
		}
		if(a != 0 && b != 0)
		{
			(*g)(a-1, b-1) -= impedances[i]->get_conductance();
			(*g)(b-1, a-1) -= impedances[i]->get_conductance();
		}
	}
}

void get_voltage_matrix(arma::mat *v, PowerSource **power_sources, int num_power_sources)
{
	for(int i=0; i<num_power_sources; i++)
	{
		int a = power_sources[i]->get_start_node();
		int b = power_sources[i]->get_end_node();
		
		if(b != 0)
		{
			(*v)(i, b-1) = power_sources[i]->get_voltage();	
		}
		if(a != 0)
		{
			(*v)(i, a-1) = -power_sources[i]->get_voltage();	
		}
	}
}

void parser(int argc, char **argv)
{

}

int main(void)
{
	Impedance *conductor = new Capacitor(0, 0, 0, 0);
	conductor->get_conductance();

#if CIRCUIT == 0
	const int num_nodes = 4;
	const int num_resistors = 4;
	const int num_power_sources = 1;
	const int num_current_sources = 0;
	const int num_capacitors = 0;
	const int num_diodes = 0;

	Resistor *resistors[num_resistors];
	Capacitor **capacitors = NULL;
	Diode **diodes = NULL;
	PowerSource *power_sources[num_power_sources];
	CurrentSource **current_sources = NULL;

	resistors[0] = new Resistor(1, 2, 100);
	resistors[1] = new Resistor(2, 0, 400);
	resistors[2] = new Resistor(2, 3, 200);
	resistors[3] = new Resistor(4, 0, 300);
	power_sources[0] = new PowerSource(0, 1, 1);

#elif CIRCUIT == 1
	// low pass filter
	const int num_nodes = 4;
	const int num_resistors = 1;
	const int num_power_sources = 1;
	const int num_current_sources = 0;
	const int num_capacitors = 1;

	Resistor *resistors[1];
	PowerSource *power_sources[1];
	CurrentSource **current_sources = NULL;
	Capacitor *capacitors[1];

	resistors[0] = new Resistor(1, 2, 5000);
	power_sources[0] = new PowerSource(0, 1, 5);
	capacitors[0] = new Capacitor(2, 3, 1e-3, DT);

#endif
	const int num_impedances = num_resistors + num_capacitors + num_diodes;
	Impedance *impedances[num_impedances];
	std::copy(resistors, resistors + num_resistors, impedances);
	std::copy(capacitors, capacitors + num_capacitors, impedances + num_resistors);
	std::copy(diodes, diodes + num_capacitors, impedances + num_resistors + num_diodes);

	arma::mat *g = new arma::mat(num_nodes, num_nodes);
	g->zeros();
	get_conductance_matrix(g, impedances, num_impedances);

	arma::mat *b = new arma::mat(num_impedances, 1);
	b->zeros();
	get_voltage_matrix(b, power_sources, 1);	

	arma::mat c = trans(*b);
	arma::mat d = arma::mat(1, 1).zeros();
	arma::mat a = arma::join_cols(arma::join_rows(*g, *b), arma::join_rows(c, d));
	a.print();

	arma::vec x = arma::vec(num_impedances + 1);
	x.zeros();

	arma::vec z = arma::vec(num_impedances + 1);
	for(int i=0; i<num_power_sources; i++)
	{
		int a = power_sources[i]->get_start_node();
		int b = power_sources[i]->get_end_node();

		if(a != 0)
		{
			z(a-1, 0) = power_sources[i]->get_voltage(); 
		}
		if(b != 0)
		{
			z(b-1, 0) = power_sources[i]->get_voltage();
		}
	}
	for(int i=0; i<num_current_sources; i++)
	{
		int a = current_sources[i]->get_start_node();
		int b = current_sources[i]->get_end_node();

		if(a != 0)
		{
			z(a-1, 0) = current_sources[i]->get_current(); 
		}
		if(b != 0)
		{
			z(b-1, 0) = current_sources[i]->get_current();
		}
	}

	for(double t=0; t<RUNTIME; t+=DT)
	{	
		for(int i=0; i<num_capacitors; i++)
		{
			int a = capacitors[i]->get_start_node();
			int b = capacitors[i]->get_end_node();

			if(a != 0)
			{
				z(a-1, 0) = capacitors[i]->get_current(x(a, 0), x(b, 0)); 
			}
			if(b != 0)
			{
				z(b-1, 0) = capacitors[i]->get_current(x(b, 0), x(a, 0));
			}
		}
		for (int i = 0; i<num_diodes; i++)
		{
			int a = diodes[i]->get_start_node();
			int b = diodes[i]->get_end_node();

			if (a != 0)
			{
				z(a - 1, 0) = diodes[i]->get_current(x(a, 0), x(b, 0));
			}
			if (b != 0)
			{
				z(b - 1, 0) = diodes[i]->get_current(x(b, 0), x(a, 0));
			}
		}

		arma::solve(x, a, z);
		x.print();
	}


	for(Impedance *impedance : impedances)
	{
		delete impedance;
	}
	for(PowerSource *power_source : power_sources)
	{
		delete power_source;
	}
	delete g;
	delete b;

	getchar();
}