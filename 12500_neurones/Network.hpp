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
	
	Network(Neuron* n1, Neuron* n2); //!< Constructor to simulate the connection between 2 neurons */
	Network(); //!< Constructor of a Network whose number of neurons are in file Constants.hpp
	~Network(); //!< Destructor that free the pointers
	
	
	void update(int simTime); //!< update the Network at each step of time (interactions between neurons)
	
	vector<Neuron*> getNeurons() const; //!< return the neurons of the Network
	
	
	private:
	vector<Neuron*> neurons; //!< neurons interacting with each others
	
};

#endif
