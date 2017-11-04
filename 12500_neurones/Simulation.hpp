#ifndef _SIMULATION_HPP_
#define _SIMULATION_HPP_

#include <iostream>
#include "neuron.hpp"
#include "Constants.hpp"
#include "Network.hpp"
#include <string>
#include <fstream>

using namespace std;
enum SIMULATION_TYPE {ONE_NEURON,TWO_NEURONS,NETWORK,OTHER};

class Simulation 
 {
	
	public:
	
	  Simulation(int n); //!< Constructor of a simulation
	  void simulate_one_neuron(); //!< simulation of one neuron
	  void simulate_two_neurons(); //!< simulation os 2 neurons
	  void simulate_Network(); //!< simulation of a complete Network
	  SIMULATION_TYPE choose_simulation(); //!< allows to choose what we're going to simulate
	  
 };

#endif
