#include "neuron.hpp"
#include <fstream>



 /////////////////Constructor and destructor
     /*!
	  * @brief Constructor of neuron 
	  * 
	  * At the begining the neuron doesn't have any connections (created after) neither membrane 
	  * potential (=0), it's excitatory by default, it hasn't spiked, and time=0 because it's in 
	  * refractory phase and curr elec is 0 .
	  */
	 Neuron::Neuron(bool ExcInh): pot_memb(0), nb_spikes(0), exc_inhib(ExcInh),
		clock(0), curr_elec(0), nbConn(0), test(false)  
	 {
	   buffer_delay = { 0 }; 
	   times = {};
	   connexions = {};
	   
	   if(exc_inhib){
		   j_connection = Je;
	   } 
	   else {
		   j_connection = Ji;
	   } //j_connection takes the value according to the type of the neuron (exc or inh)

	   
	}
	 /*!
	  * @brief Destructor of neuron
	  */
	 Neuron::~Neuron(){}

	 
	 
 ////////////////Neuron evolution	 

     
     void Neuron::addConnexion(int i) {
		 connexions.push_back(i);
		 nbConn++;
	 }
	 
	 /*!
	  * @brief update the neuron at each simulation time
	  * @param an int corresponding to the simulation time
	  * 
	  * I check if my neuron emits a spike (when membrane potential exceeds maximum membrane potential 
	  * (Vthershold)).
	  * Then while it's refracting the membrane potential remains at 0.
	  * 
	  */
	 bool Neuron::update_state (int simTime)
	 {
		bool spiked = false;
		
		if (pot_memb >= maxPot) 
		{
			spike_emission(simTime);
			spiked = true;
		}
		   
		   if(isRefractory(simTime))
		   {
			   pot_memb=0.0;
		   }
			
		   else {V_compute();}	
		   																			   			   
			buffer_delay[clock%buffer_delay.size()] = 0.0;
		   clock++;
		   
		   return spiked;
	 }
	 
	 /*!
	  * @brief allows to see if the neuron is refractory 
	  * @param the simulation time to ""compute" the last time the neuron spiked
	  */ 
	 bool Neuron::isRefractory(int simTime) const
	{
		return (!times.empty() and (simTime < (times.back() + t_refract)));
	}
		 
	/*!
	 *@brief treats the membrane potential during a spike emission
	 * 
	  * the neuron spiked so my membrane potential turns
	  * back to 0, I add a spike time to the vector times, my time of refractory break turns back to t_refract
	  * the neuron emits a spike (setSpike->true) and I add 1 to my total number of spikes.
	 */
	void Neuron::spike_emission(int simTime)
	{
	  pot_memb = 0.0;
	  times.push_back(simTime);
	  setNbSpikes(getNbSpikes()+1);
	} 
		 
		 
	 /*!
	 * @brief it computes the membrane potential according to the specificity of neuron (if it's tested (has its own potential) or normal)
	 * 
	 * If it can spike alone it increases its membrane potential according to an input electric current curr_elec.
	 * I add the poisson generation that corresponds to the connections that comes from the external neurons
	 * (only if I'm not testing because it's difficult to test values with random generation)
	 * and the contents of the buffer (that corresponds to the reception of a signal received with delay D).
	 */	 
	 void Neuron::V_compute()
	 {
		 pot_memb = exp(-dt/tau)*pot_memb;
		 
		 if(getTest()) 
			{
		     pot_memb += curr_elec * tau/C * (1-exp(-dt/tau)); //tau=r*c r=resistance
		    }
		 
		 else 
		    {
		      pot_memb += Neuron::getPoissonNoise();
		    }
		    
		pot_memb += buffer_delay[clock % buffer_delay.size()];
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
	 array<double, BUFFER_SIZE> Neuron::getBufferDelay() const {
		 return buffer_delay;
	 }
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
	 
	 
	 /*!
	  * @brief getter of the amplitude of the signal the neuron is going to transmit
	  * @return a double corresponding to this amplitude
	  */ 
	 double Neuron:: getJconnect() const {
		 return exc_inhib ? Je : Ji;
	}
	 
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
	  * @brief setter of electric current of neuron
	  * @param  a double corresponding to an electric current
	  */
	 void Neuron:: setCurrElec(double c) {curr_elec=c;}
	 /*!
	  * @brief setter of ExcInhib to tell if the neuron is excitatory (true) or inhibitory (false), used during construction of neurons
	  * @param   a double which corresponds to an electric current
	  */
	 void Neuron:: setExcInhib(bool b) {exc_inhib=b;
		 j_connection = b ? Je : Ji;
		 }
	 /*!
	  * @brief setter of connexions 
	  * @param  a vector of int corresponding to index of connections to other neurons
	  */
	 void Neuron:: setConnexions(vector<int> v) {connexions=v;}
	 /*!
	  * @brief setter of buffer_delay to modify one of the squares (when a neuron is going to receive a signal)
	  * @param  an int corresponding to the place where we're going to store the value b of the signal received
	  */
	 void Neuron:: setBufferDelay(int place, double b) {
		 buffer_delay[place] += b;
	 }
	 /*!
	  * @brief setter of test
	  * @param  boolean corresponding to if we are testing something (in unitTest) or not
	  */
	 void Neuron:: setTest(bool b) {test=b;}

	 /*!
	  * @brief set the amplitude of the signal the neuron is going to emit 
	  * @param a double corresponding to this amplitude 
	  */ 
	 void Neuron::setJconnect(double j) {j_connection=j;}
	 
