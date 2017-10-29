#include "neuron.hpp"
#include "Constants.hpp"
#include <fstream>
#include <iomanip>
#include <random>



 /////////////////Constructeurs et destructeur
	 Neuron::Neuron(): tau(10), nbConn(0), exc_inhib(true), pot_memb(0), curr_elec(1.0), c(250), nb_spikes(0), times(vector<double>(1,0)), clock(0), canSpike(true), time(0), spike(false)
	 {
	   for(auto& d:buffer_delay) {d=0;}	 
	   for(size_t t(0);t<12500;++t) {connexions.push_back(0);} //mon neurone va avoir 12500 connexion
	   
     }
	 
	 
	 Neuron::Neuron(double pm,int ns, vector<double> t): exc_inhib(true), nbConn(0), tau(10), curr_elec(1.0), canSpike(true), c(250), pot_memb(pm), nb_spikes(ns), times(t), clock(0), time(0), spike(false)
	 {
	   for(auto& d:buffer_delay) {d=0;}	 
	   for(size_t t(0);t<12500;++t) {connexions.push_back(0);} //mon neurone va avoir 12500 connexion
	 }
	 
	 
	 Neuron::~Neuron(){}
	 
	 
 ////////////////Evolution du neurone	 
 
	 void Neuron::emit_signal(Neuron* other, int n)
	 {
		 if(getSpike())
		 {
			 if(exc_inhib)
			 {
				 (other->buffer_delay[(clock+D)%(buffer_delay.size())])+=(n*Je);
			 }														 //la case associée à la future reception de spike prend 
																	 //la valeur de J (e ou i suivant excitateur ou inhibiteur)
			 else
	         {other->buffer_delay[(clock+D)%buffer_delay.size()]+=n*(Ji-0.1);}
		 }														     
		 
		 
		 
	 } 
	 
	 void Neuron::connexions_fill(int num_neuron) //sert à créer des connexions aléatoires avec 
	 {											  //d'autres neurones que soi (=num neuron)
	    random_device rd; 
        mt19937 gen(rd());
	    int i(0); //compte les connexions excitatrices
	    int j(0); //compte les connexions inhibitrices
	  
	    while(i<conn_exc) //dont 1000 excitatrices
	     {
		   uniform_int_distribution<int> d(0,nbNeuronExc); //mes 10000 premiers neurones sont excitateurs
		
		   if(d(gen)!=num_neuron) //mon neurone doit se connecter à un autre neurone que lui-même
		    {
			 connexions[d(gen)]+=1;
			 ++i;
			 nbConn+=1;
		    }
	     }
	    
	    while(j<conn_inh)
	      {
		     uniform_int_distribution<int> e(nbNeuronExc+1,nbNeuronExc+nbNeuronIn); //mes 10000 premiers neurones sont excitateurs
		
		     if(e(gen)!=num_neuron) //mon neurone doit se connecter à un autre neurone que lui-même
		      {
			   connexions[e(gen)]+=1;
			   ++j;
			   nbConn+=1;
		      }
	      }
     }
	 
	 
	 void Neuron::update_state (int simTime)
	 {
		 setSpike(false);
		 
		 
		   if(pot_memb>maxPot) //gère le moment du spike 
		    {
			    pot_memb=0.0;
			    times.push_back(simTime);
			    time=0;
			    setSpike(true);
			    setNbSpikes(getNbSpikes()+1);
		    }
		   
		   if(time<t_refract) //maintient la pause entre 2 spikes
		    {
			   pot_memb=0.0;
			   
		    }
			
		   else  //si pas en pause entre 2 spikes, le potentiel du neurone augmente
		    {
				if(getCanSpike()) //si le neurone peut spiker (et pas seulement recevoir un signal)
				{
		         pot_memb=exp(-dt/tau)*pot_memb+curr_elec/c*(1-exp(-dt/tau)); //tau=r*c r=resistance
		        }
		        
		       random_device randomDevice;
		       mt19937 gen(randomDevice());
		       poisson_distribution<> poissonGen(0.02*Je*dt*1000);
    
		       pot_memb+=buffer_delay[clock%buffer_delay.size()]+ poissonGen(gen);//connexion stockée dans le buffer
		       buffer_delay[clock%buffer_delay.size()]=0;										  			   //+courant aléatoire (poisson) de 
		    }																					   			   //(Vext*J*dt*Ce)
		
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
	 double Neuron::getCurrElec() const {return curr_elec;}
	 int Neuron::getClock() const {return clock;}
	 bool Neuron::getExcInhib() const {return exc_inhib;}
	 vector<int> Neuron::getConnexions() const {return connexions;}
	 array<double,30> Neuron:: getBufferDelay() const {return buffer_delay;}
	 int Neuron:: getNbConn() const {return nbConn;}
	 
//////////////setters
	 void Neuron::setPotMemb(double p) {pot_memb=p;}
	 void Neuron::setNbSpikes(int n) {nb_spikes=n;}
	 void Neuron::setTimes(vector<double> t) {times=t;}
	 void Neuron:: setSpike(bool s){spike=s;}
	 void Neuron:: setCanSpike(bool c) {canSpike=c;}
	 void Neuron:: setCurrElec(double c) {curr_elec=c;}
	 void Neuron:: setExcInhib(bool b) {exc_inhib=b;}
	 void Neuron:: setConnexions(vector<int> v) {connexions=v;}
	 void Neuron:: setBufferDelay(int place, double b) {buffer_delay[place]=b;}
	 
