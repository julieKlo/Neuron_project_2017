#ifndef _CONSTANTS_HPP_
#define _CONSTANTS_HPP_

#include <iostream>
using namespace std;

//les double de  temps correspondent à des mS

const double maxPot=20; //!< maximum potential the membrane can reach (Vthreshold)
const int tstart=0; //!< time when the simulation starts
const int tstop=1000; //!< time when the simulation ends
const double dt=0.1; //!< step of evolution (=h)
const int n=5; //!< rate of actualisation
const int tau=10;
const double C=1; //!< Capacity
const double Jext=0.1; //!< J (amplitude) received by outside
const double Je=0.1; //!< amplitude of the excitatory transmitted signal
const double Ji=-0.5; //!< amplitude of the inhibitory transmitted signal
const int D=15; //!< delay time before the reception of the signal
const int conn_exc=1000; //!< number of excitatory connections
const int conn_inh=250; //!< number of inhibitory connections
const int nbNeuronExc=10000; //!< number of excitatory neurons
const int nbNeuronIn=2500; //!< number of inhibitory neurons
const int t_refract=20; //!< number of steps between 2 spikes
const double Vext=0.02; //!< extern potential (warning: if changed, test for number of spikes doesn't work cause poisson generation varies)
const int Ce=1000; //!< extern capacity


#endif
