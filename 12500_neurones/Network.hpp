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
	Network(); //crée un Network composé de 12 500 neurones dont 
			   //10000 excitateurs et 2500 inhibiteurs
	~Network();
	
	
	void update(int simTime);
	
	vector<Neuron*> getNeurons() const;
	
	
	private:
	vector<Neuron*> neurons;
	
};

#endif
