#include "neuron.hpp"
#include "Constants.hpp"
#include <fstream>


 /////////////////Constructeurs et destructeur
	 Neuron::Neuron(): tau(10), pot_memb(-70), c(250), nb_spikes(0), times(vector<double>(1,0)), clock(0), canSpike(true), t_refract(4), time(0), spike(false)
	 {
	   for(auto& d:buffer_delay) {d=0;}	 
	 }
	 
	 
	 Neuron::Neuron(double pm,int ns, vector<double> t): tau(10), canSpike(true), c(250), pot_memb(pm), nb_spikes(ns), times(t), clock(0), t_refract(4), time(0), spike(false)
	 {
	   for(auto& d:buffer_delay) {d=0;}	 
	 }
	 
	 
	 Neuron::~Neuron(){}
	 
	 
 ////////////////Evolution du neurone	 
 
	 void Neuron::emit_signal(Neuron* other)
	 {
		 if(getSpike())
		 {
			other->buffer_delay[(clock+D)%buffer_delay.size()]=J; //la case associée à la future reception de spike prend 
		 }														 //la valeur de J
		 
		 
	 } 
	 
	 
	 void Neuron::update_state (double dt, double curr_elec, int simTime)
	 {
		 maxPot=-56;
		 setSpike(false);
		 
		 
		   if(pot_memb>maxPot) //gère le moment du spike 
		    {
			    pot_memb=-70;
			    times.push_back(simTime);
			    time=0;
			    setSpike(true);
		    }
		   
		   if(time<t_refract) //maintient la pause entre 2 spikes
		    {
			   pot_memb=-70;
			   
		    }
			
		   else  //si pas en pause entre 2 spikes, le potentiel du neurone augmente
		    {
				if(getCanSpike()) //si le neurone peut spiker (et pas seulement recevoir un signal)
				{
		         pot_memb=exp(-dt/tau)*pot_memb+curr_elec/c*(1-exp(-dt/tau)); //tau=r*c r=resistance
		        }
		       cout<<"pot memb= "<<getPotMemb()<<endl;
		       pot_memb+=buffer_delay[clock%buffer_delay.size()];
		       cout<<"pot memb+J= "<<getPotMemb()<<endl;
		       buffer_delay[clock%buffer_delay.size()]=0;
		    }
		
		   
		   clock++;
		   time++;
		   
		   
		 }
		 	
	 
	 
	 
///////////////getters
	 double Neuron::getPotMemb() const {return pot_memb;}
	 int Neuron::getNbSpikes() const {return nb_spikes;}
	 vector<double> Neuron::getTimes() const {return times;}
	 double Neuron::getTback() const {return times.back();}
	 bool Neuron::getSpike() const {return spike;}
	 bool Neuron::getCanSpike() const {return canSpike;}
	 
//////////////setters
	 void Neuron::setPotMemb(double p) {pot_memb=p;}
	 void Neuron::setNbSpikes(int n) {nb_spikes=n;}
	 void Neuron::setTimes(vector<double> t) {times=t;}
	 void Neuron:: setSpike(bool s){spike=s;}
	 void Neuron:: setCanSpike(bool c) {canSpike=c;}
	 
	 
