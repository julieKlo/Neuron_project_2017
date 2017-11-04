#ifndef _NEURON_HPP_
#define _NEURON_HPP_

#include <iostream>
#include <cmath>
#include <vector>
#include <array>

using namespace std;


class Neuron 
{
	public:
	//constructor destructor
	 Neuron(); //!< Constructor of neuron
	 ~Neuron();//!< Destructor of neuron
	 
	 //neuron evolution
	 void update_state (int simTime); //!< Update the neuron at each step of time
	 void emit_signal(Neuron* other); //!< Allows a neuron to emit a signal toward its connections once it spiked
	 void connexions_fill(int num_neuron); //!< create connections randomly from the neuron toward other neurons through indexes (int)
	 void V_compute(); //!< compute the membrane potential
	 void spike_emission(int simTime);//!< treats the membrane potential during a spike emission
	 
	 
	 
	 //getters
	 double getPotMemb() const; //!< return the membrane potential
	 int getNbSpikes() const; //!< return the number of spikes the neuron lived
	 vector<double> getTimes() const; //!< return the times corresponding to the spikes of the neuron
	 double getTback() const; //!< return the last element of the spike times
	 bool getSpike() const; //!< return the boolean telling if the neuron just spiked or not
	 double getCurrElec() const; //!< return the electric current of the neuron
	 int getClock() const; //!< return the life time of the neuron
	 bool getExcInhib() const; //!< return if the neuron is excitatory or inhibitory
	 vector<int> getConnexions() const; //!< return the connections of the neuron (through indexes)
	 array<double,16> getBufferDelay() const; //!< return the buffer in which are stored the signals theneuron is going to receive after the delay
	 int getNbConn() const; //!< return the number of connections of the neuron
	 bool getTest() const; //!< return if we are testing something (true) or just using it in the main
	 vector<int> getEfficientConnections() const;
	 
	 //setters
	 void setPotMemb(double p); //!< set the membrane potential
	 void setNbSpikes(int n); //!< set the number of spikes the neuron lived
	 void setTimes(vector<double> t); //!< set the spike times
	 void setSpike(bool s); //!< set the boolean telling if the neuron spiked or not
	 void setCurrElec(double c); //!< set the electric current of the neuron
	 void setExcInhib(bool b); //!< set the boolean telling if the neuron is excitatory or inhibitory
	 void setConnexions(vector<int> v); //!< set the connections of the neuron
	 void setBufferDelay(int place, double b); //!< set a square of the buffer
	 void setTest(bool b); //!< set if we are testing something or just using it in the main
	 void setEfficientConnections(vector<int> v);
	
	private:
	//potentials
	 double pot_memb; //!< membrane potential of the neuron
	 
	//spikes
	 int nb_spikes; //!< number of spikes it already had
	 vector<double> times; //!< times when spikes occur
	 bool spike; //!< becomes true when the neuron spikes (->can emit a signal)
	 bool exc_inhib; //!< true=excitatory and false=inhibitory
	 
	//time
	 int clock; //!< clock of the neuron
	 int time; //!< counter for the break between 2 spikes
	 array<double,16> buffer_delay; //!< stores the pre-synaptic signals the neuron will receive with a delay D
	 double curr_elec; //!< electric current 
	 
	//connections
	 vector<int> connexions; //!< vector of index corresponding to the neurons this one is connected to
	 int nbConn; //!< number of connections the neuron has
	 bool test; //!< true if we're testing, false else
	 vector<int> efficient_connections; //!< vector of neurons this is connected to


	 
};



 
 #endif
