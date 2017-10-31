#include "neuron.hpp"
#include "Constants.hpp"
#include <fstream>
#include <iomanip>
#include <random>



 /////////////////Constructeurs et destructeur
     /*!
	  * @brief Constructor of neuron 
	  * 
	  * at the begining the neuron don't have any connections (created after) neither membrane potential (=0), it's excitatory by default, 
	  * it hasn't spiked, and time=0 because it's in refractory phase and curr elec is 0 cause it cannot spike alone (also why canSpike=false)
	  */
	 Neuron::Neuron(): nbConn(0), test(false), exc_inhib(true), pot_memb(0), curr_elec(0),  nb_spikes(0), times(vector<double>(1,0)), clock(0), canSpike(false), time(0), spike(false)
	 {
	   for(auto& d:buffer_delay) {d=0;}	 
	   for(size_t t(0);t<12500;++t) {connexions.push_back(0);} //mon neurone va avoir 12500 connexion
	   
     }
 
	 /*!
	  * @brief Destructor of neuron
	  */
	 Neuron::~Neuron(){}

	 
	 
 ////////////////Evolution du neurone	 
 
	 /*!
	  * @brief allows a neuron that spiked to send a signal to another neuron
	  * @param the neuron that will receive the signal and an int n corresponding to the number of connections the neuron has with the other
	  * 
	  * when the neuron has spiked, it sends a signal to the neurons it's connected to
	  * with an amplitude Je (if excitatory) and Ji (if inhibitory) times the number of connections that
	  * exist between the two neurons
	  */
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
	 
	 /*!
	  * @brief fill the vector of connections of one neuron
	  * @param an int to avoid the neuron to connect to itself
	  * 
	  * While we don't have as many excitatory (respectively inhibitory) connections as expected, we create randomly
	  * connections by generating a number belowing to the number of excitatory (resp inh) neurons
	  * In the square of the neuron corresponding to the random number we add 1 to show that 1 more connection
	  * between the 2 neurons exists
	  */
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
	 
	 /*!
	  * @brief update the neuron at each simulation time
	  * @param an int corresponding to the simulation time
	  * 
	  * when the membrane potential exceeds maxPot, that means the neuron spiked so my membrane potential turns
	  * back to 0, I add a spike time to the vector times, my time of refractory break turns back to t_refract
	  * the neuron emits a spike (setSpike->true) and I add 1 to my total number of spikes
	  * Then while it's refracting the membrane potential remains at 0
	  * Finally if it can spike alone it increases
	  * I add the poisson generation that corresponds to the connections that comes from the external neurons
	  */
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
		         pot_memb=exp(-dt/tau)*pot_memb+curr_elec/C*(1-exp(-dt/tau)); //tau=r*c r=resistance
		        }
		        
		       random_device randomDevice;
		       mt19937 gen(randomDevice());
		       poisson_distribution<> poissonGen(Vext*Jext*dt*Ce);
		       if(getTest()) {pot_memb+=buffer_delay[clock%buffer_delay.size()];}
		       else {pot_memb+=buffer_delay[clock%buffer_delay.size()]+ poissonGen(gen);}//connexion stockée dans le buffer
		       buffer_delay[clock%buffer_delay.size()]=0;										  			   //+courant aléatoire (poisson) de 
		    }																					   			   //(Vext*J*dt*Ce)
		
		   clock++;
		   time++;
		   
		   
		 }
		 	
	 
	 
	 
///////////////getters
	/*!
	  * @brief getter of Membrane potential
	  * @return membrane potential 
	  */
	 double Neuron::getPotMemb() const {return pot_memb;}
	 /*!
	  * @brief getter of number of spikes whose times are in the vector named times
	  * @return number of spikes the neuron has already lived 
	  */
	 int Neuron::getNbSpikes() const {return nb_spikes;}
	 /*!
	  * @brief getter of spike times
	  * @return a vector which stores times when spikes occur 
	  */
	 vector<double> Neuron::getTimes() const {return times;}
	 /*!
	  * @brief getter of time of last spike
	  * @return time when last spike occured 
	  */
	 double Neuron::getTback() const {return times.back();}
	 /*!
	  * @brief getter of boolean spike
	  * @return if a spike has been emited so that the neuron throw signals to its connections
	  */
	 bool Neuron::getSpike() const {return spike;}
	 /*!
	  * @brief getter of canSpike
	  * @return if the neuron can increase its own potential  
	  */
	 bool Neuron::getCanSpike() const {return canSpike;}
	 /*!
	  * @brief getter of curr_elec
	  * @return the electric current the neuron suffers
	  */
	 double Neuron::getCurrElec() const {return curr_elec;}
	 /*!
	  * @brief getter of clock
	  * @return life time of the neuron 
	  */
	 int Neuron::getClock() const {return clock;}
	 /*!
	  * @brief getter of exc_inhib
	  * @return true if neuron is excitatory, false if inhibitory
	  */
	 bool Neuron::getExcInhib() const {return exc_inhib;}
	 /*!
	  * @brief getter of vector connexions
	  * @return the connexions of the neuron 
	  */
	 vector<int> Neuron::getConnexions() const {return connexions;}
	 /*!
	  * @brief getter of buffer_delay
	  * @return  the array where are stored the signals the neuron is going to receive 
	  */
	 array<double,30> Neuron:: getBufferDelay() const {return buffer_delay;}
	 /*!
	  * @brief getter of nb_Conn
	  * @return the number of connexions the neuron has 
	  */
	 int Neuron:: getNbConn() const {return nbConn;}
	 
	  /*!
	  * @brief getter of test
	  * @return if we are testing or not 
	  */
	 bool Neuron:: getTest() const {return test;}
	 
//////////////setters
	  /*!
	  * @brief setter of Membrane Potential
	  * @param  a double corresponding to a membrane potential p;
	  */
	 void Neuron::setPotMemb(double p) {pot_memb=p;}
	 /*!
	  * @brief setter of nbSpikes
	  * @param  an int n corresponding to a number of spikes
	  */
	 void Neuron::setNbSpikes(int n) {nb_spikes=n;}
	 /*!
	  * @brief setter of vector of spike times named times
	  * @param   a vector of double corresponding to times
	  */
	 void Neuron::setTimes(vector<double> t) {times=t;}
	 /*!
	  * @brief setter of Spike (if the neuron has spiked or not)
	  * @param  a boolean to say if it spiked and so can throw signal (true=yes)
	  */
	 void Neuron:: setSpike(bool s){spike=s;}
	 /*!
	  * @brief setter of canSpike (if neuron can generate its own membrane potential with current I)
	  * @param  a boolean telling if the neuron can only receive signal (false) to increase its potential
	  */
	 void Neuron:: setCanSpike(bool c) {canSpike=c;}
	 /*!
	  * @brief setter of electric current of neuron
	  * @param  a double corresponding to an electric current
	  */
	 void Neuron:: setCurrElec(double c) {curr_elec=c;}
	 /*!
	  * @brief setter of ExcInhib to tell if the neuron is excitatory (true) or inhibitory (false), used during construction of neurons
	  * @param   a double which corresponds to an electric current
	  */
	 void Neuron:: setExcInhib(bool b) {exc_inhib=b;}
	 /*!
	  * @brief setter of connexions 
	  * @param  a vector of int corresponding to index of connections to other neurons
	  */
	 void Neuron:: setConnexions(vector<int> v) {connexions=v;}
	 /*!
	  * @brief setter of buffer_delay to modify one of the squares (when a neuron is going to receive a signal)
	  * @param  an int corresponding to the place where we're going to store the value b of the signal received
	  */
	 void Neuron:: setBufferDelay(int place, double b) {buffer_delay[place]=b;}
	 /*!
	  * @brief setter of test
	  * @param  boolean corresponding to if we are testing something (in unitTest) or not
	  */
	 void Neuron:: setTest(bool b) {test=b;}
	 
