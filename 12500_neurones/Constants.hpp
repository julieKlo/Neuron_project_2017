#ifndef _CONSTANTS_HPP_
#define _CONSTANTS_HPP_

#include <iostream>
using namespace std;

//les double de  temps correspondent à des mS

const double maxPot=20; //potentiel maximum atteint par la membrane
const int tstart=0;//temps de début de simulation
const int tstop=1000; //temps de fin de simulation
const double dt=0.2; //pas d'evolution
const int n=5; //taux d'actualisation
const int tau=10;
const double C=1; //capacity
const double Jext=0.1; //J reçu par l'exterieur
const double Je=0.1; //amplitude du signal transmis exitateur
const double Ji=-0.5; //amplitude du signal transmis inihbiteur
const int D=15; //temps de retard pour reception du signal
const int conn_exc=10; //#connexions excitatrices
const int conn_inh=3; //#connexions inhibitrices
const int nbNeuronExc=100; //#neurones excitateurs
const int nbNeuronIn=25; //#neurones inhibiteurs
const int t_refract=2; //#steps de pause entre 2 spikes
const double Vext=0.02; //si varié, test nbSpikes ne fonctionne plus car poisson varie bcp
const int Ce=1000;


#endif
