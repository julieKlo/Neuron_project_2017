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
	//constructeurs destructeurs
	 Neuron();
	 Neuron(double pm,int ns, vector<double> t);
	 ~Neuron();
	 
	 //evolution du neurone
	 void update_state (double dt, int simTime);
	 void emit_signal(Neuron* other);
	 
	 //getters
	 double getPotMemb() const;
	 int getNbSpikes() const;
	 vector<double> getTimes() const;
	 double getTback() const;
	 bool getSpike() const;
	 bool getCanSpike() const;
	 double getCurrElec() const;
	 int getClock() const;
	 
	 //setters
	 void setPotMemb(double p);
	 void setNbSpikes(int n);
	 void setTimes(vector<double> t);
	 void setSpike(bool s);
	 void setCanSpike(bool c);
	 void setCurrElec(double c);

	
	private:
	//potentiels
	 double pot_memb; //membrane potential
	 double maxPot;
	 double c; //capacité
	 
	//spikes
	 int nb_spikes; //number of spikes
	 vector<double> times; //times when spikes occur
	 bool spike; //se met à true lors de l'emission d'un spike
	 bool canSpike; //capaciter du neurone a spiker de lui-même ou seulement
					//recevoir un signal (si false)
	//temps
	 double tau; //intervalle de temps
	 int clock; //horloge du neurone
	 int t_refract; //#steps necessaires
	 int time;//horloge gerant la pause entre 2 spikes
	 array<int,30> buffer_delay;//tableau de sockage pour reception du signal pré synaptique
	 double curr_elec; //courant electrique du neurone
	 


	 
};


 //  C=250 pF
 // Tau=10 mS
 // Tau ref= 2 mS
 // Vreset= -70mV => après un spike
 // dt= 0.1 mS
 
 #endif
