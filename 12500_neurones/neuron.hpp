#ifndef _NEURON_HPP_
#define _NEURON_HPP_

#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <random>
#include <iomanip>
#include "Constants.hpp"

using namespace std;


class Neuron 
{
	public:
	//constructor destructor
	 Neuron(bool ExcInh); //!< Constructor of neuron
	 ~Neuron();//!< Destructor of neuron
	 
	 //neuron evolution
	 bool update_state (int simTime); //!< Update the neuron at each step of time
	 void V_compute(); //!< compute the membrane potential
	 void spike_emission(int simTime);//!< treats the membrane potential during a spike emission
	 
	
	static double getPoissonNoise() {
		static random_device randomDevice;
		static mt19937 gen(randomDevice());
		static poisson_distribution<> poissonGen(NU_EXT);
		  
		int spik = poissonGen(gen);
		  
		return spik * Jext;
	}
	 
	 
	 //getters
	 double getPotMemb() const; //!< return the membrane potential
	 int getNbSpikes() const; //!< return the number of spikes the neuron lived
	 vector<double> getTimes() const; //!< return the times corresponding to the spikes of the neuron
	 double getTback() const; //!< return the last element of the spike times
	 double getCurrElec() const; //!< return the electric current of the neuron
	 int getClock() const; //!< return the life time of the neuron
	 bool getExcInhib() const; //!< return if the neuron is excitatory or inhibitory
	 vector<int> getConnexions() const; //!< return the connections of the neuron (through indexes)
	 array<double,16> getBufferDelay() const; //!< return the buffer in which are stored the signals theneuron is going to receive after the delay
	 int getNbConn() const; //!< return the number of connections of the neuron
	 bool getTest() const; //!< return if we are testing something (true) or just using it in the main
	 double getJconnect() const;
	 
	 //setters
	 void setPotMemb(double p); //!< set the membrane potential
	 void setNbSpikes(int n); //!< set the number of spikes the neuron lived
	 void setTimes(vector<double> t); //!< set the spike times
	 void setCurrElec(double c); //!< set the electric current of the neuron
	 void setExcInhib(bool b); //!< set the boolean telling if the neuron is excitatory or inhibitory
	 void setConnexions(vector<int> v); //!< set the connections of the neuron
	 void setBufferDelay(int place, double b); //!< set a square of the buffer
	 void setTest(bool b); //!< set if we are testing something or just using it in the main
	 void setJconnect(double j);
	 void addConnexion(int i); //!< return the connections of the neuron (through indexes)
	
	private:
	//potentials
	 double pot_memb; //!< membrane potential of the neuron
	 
	//spikes
	 int nb_spikes; //!< number of spikes it already had
	 vector<double> times; //!< times when spikes occur
	 bool exc_inhib; //!< true=excitatory and false=inhibitory
	 
	//time
	 int clock; //!< clock of the neuron
	 array<double, BUFFER_SIZE> buffer_delay; //!< stores the pre-synaptic signals the neuron will receive with a delay D
	 double curr_elec; //!< electric current 
	 
	 bool isRefractory(int simTime) const; //!< tests if neuron in refractory time
	 
	//connections
	 vector<int> connexions; //!< vector of index corresponding to the neurons this one is connected to
	 int nbConn; //!< number of connections the neuron has
	 bool test; //!< true if we're testing, false else

	double j_connection; //!< potential received from connected neurons

	 
};



 
#endif
