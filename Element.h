class Element
{
public:
	int get_start_node();
	int get_end_node();
protected:
	Element(int start, int end);
	int start_node;
	int end_node;
};