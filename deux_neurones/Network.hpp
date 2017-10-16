#ifndef _NETWORK_HPP_
#define _NETWORK_HPP_

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
	
	vector<Neuron*> getNeurons() const;
	
	
	private:
	vector<Neuron*> neurons;
	vector<vector<int> > connexions;
	
};

#endif
