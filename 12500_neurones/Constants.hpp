#ifndef _CONSTANTS_HPP_
#define _CONSTANTS_HPP_

#include <iostream>
using namespace std;

//10t=1mS

//Variable values 
const double G=6; //!< proportion between Je and Ji
const double ETA=4;

//Potential
const double maxPot=20; //!< maximum potential the membrane can reach (Vthreshold)
const double Vext=0.01*ETA; //!< extern potential (warning: if changed, test for number of spikes doesn't work cause poisson generation varies)

//Time
const double tstart=0.0; //!< time when the simulation starts
const double tstop=10000; //!< time when the simulation ends
const double dt=0.1; //!< step of evolution (=h)
const double tau=20;
const double t_refract=20; //!< number of ms between 2 spikes


//Capacity
const double C=1; //!< Capacity
const int Ce=1000; //!< extern capacity


//Connections
const double Jext=0.1; //!< J (amplitude) received by outside
const double Je=0.1; //!< amplitude of the excitatory transmitted signal
const double Ji= -1 * G * Je; //!< amplitude of the inhibitory transmitted signal
const int conn_exc=1000; //!< number of excitatory connections
const int conn_inh=250; //!< number of inhibitory connections
const int D=15; //!< delay time before the reception of the signal
const int BUFFER_SIZE = (int) (D + 1); //!< size of the neuron buffer


//Neurons in Network
const int nbNeuronExc=10000; //!< number of excitatory neurons
const int nbNeuronIn=2500; //!< number of inhibitory neurons

const double NU_EXT=Vext*Je*Ce; //!< value for poisson generation


#endif
