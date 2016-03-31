#include "Element.h"

Element::Element(int start, int end):
	start_node(start), end_node(end) { }

int Element::get_start_node()
{
	return start_node;
}

int Element::get_end_node()
{
	return end_node;
}