/*
Matthew Vater, Adam Mannheim, Nathan Spangler
mav78@pitt.edu, amm349@pitt.edu, njs55@pitt.edu
30 March 2016
SPICE Simulator
*/

#include <stdlib>
#include <cmath>
#include <armadillo>

#include "\Python32\include\Python.h"

#include "CurrentSource.h"
#include "Element.h"
#include "PowerSource.h"
#include "Resistor.h"


#define PYRUN(...) sprintf(cmd_str,__VA_ARGS__); (PyRun_SimpleString(cmd_str) < 0 ? getchar():1);


int main(void) {

}

arma::vec linear_system_solver(arma::mat A, arma::vec x, arma::vec z)
{
	if (!arma::solve(x, A, z)) {
		//handle error

	}
}
