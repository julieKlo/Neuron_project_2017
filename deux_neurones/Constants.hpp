#ifndef _CONSTANTS_HPP_
#define _CONSTANTS_HPP_

#include <iostream>
using namespace std;

//les double de  temps correspondent à des mS

const int tstart=0.0;//temps de début de simulation
const int tstop=1000.0; //temps de fin de simulation
const double dt=0.2; //pas d'evolution
const int n=5; //taux d'actualisation
const int tau=10;
const double C=250; //capacity
const double J=3; //amplitude du signal transmis
const int D=15; //temps de retard pour reception du signal

#endif
