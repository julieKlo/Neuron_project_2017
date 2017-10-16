#include <iostream>
using namespace std;
#include "neuron.hpp"
#include "Constants.hpp"
#include <array>


class Network 
{
	public:
	
	Network(Neuron n1, Neuron n2);
	~Network();
	
	
	void update(int simTime);
	
	
	private:
	vector<Neuron*> neurons;
	vector<vector<int> > connexions;
	
};
