#include "Network.hpp"
#include <random>


//////////////////Constructors & Destructor

	  /*!
	  * @brief Constructor of the Network 
	  * We create a tab in wich we have excitatory and inhibitory neurons related by connections randomly generated
	  */
 Network::Network()
 {
	 neurons = {};
	 
	 random_device rd; 
	mt19937 gen(rd());
	  
	uniform_int_distribution<int> excitatoryDistribution(0, nbNeuronExc - 1); 
	uniform_int_distribution<int> inhibitoryDistribution(nbNeuronExc, nbNeuronExc + nbNeuronIn - 1); 
	  
		
	for(int i(0); i<nbNeuronExc;++i) 
	  {
	    neurons.push_back(new Neuron(true));
	    
	  }
	  
	  for(int j(0); j<nbNeuronIn;++j) 
	  {
		neurons.push_back(new Neuron(false));
	  }
		
		
	for(int i(0); i<(nbNeuronExc+nbNeuronIn);++i) 
	  {
	    for (int exc(0); exc < conn_exc; ++exc) {
			int generated = excitatoryDistribution(gen);
			while (generated == i) {
				generated = excitatoryDistribution(gen);
			}
			neurons[generated]->addConnexion(i);
		}
		
		for (int inh(0); inh < conn_inh; ++inh) {
			int generated = inhibitoryDistribution(gen);
			while (generated == i) {
				generated = inhibitoryDistribution(gen);
			}
			neurons[generated]->addConnexion(i);
		}
	    
	  }
	  
	  cout<<"#constructed neurons : "<<neurons.size()<<endl;
    
 }
 
 


 
	  /*!
	  * @brief Constructor of the Network composed of 2 neurons to observe the connection between them
	  * We create two excitatory neurons related by a connection from the first to the second
	  */
 Network::Network(Neuron* n1, Neuron* n2)
 {
	 neurons.push_back(n1);
	 neurons.push_back(n2);
	 
	 // 0 transmits to 1
	 neurons[0]->addConnexion(1);
 }					

	  /*!
	  * @brief Destructor of Network (free the pointers) 
	  */
 Network::~Network() 
 {
    for (auto& e : neurons)
     {
        delete e;
        e=nullptr;
     }
 }
 
 

//////////////////Action on Network

	 /*!
	  * @brief run the simulation from tstart to tstop (updates the neuron at each step of time)
	  * Until tstop we update each neuron. It returns a boolean telling if it spiked or not. If it spiked
	  * it sends a signal to all its connections and the number of emitted signals is incremented. 
	  */ 
	  
	void Network::run() 
 {
	 
		int t = tstart;
	 
		while(t < tstop)
		{
		
			for(auto& neuron : neurons)
			{
			 bool spiked = neuron->update_state(t);
			
			 if (spiked)
			  {
				for(int target : neuron->getConnexions()) 
				{
					neurons[target]->setBufferDelay( (t + D)%(BUFFER_SIZE), neuron->getJconnect() );
					countEmittedSignals++;
				}	
			  }										  
			  
			}
		
		  //if (t % 100 == 0){cout << t/100<<"%" << endl;} //decomment to print the program state of avdvancement in %
		
		   t++;
	   }
 }

		

//////////////////getter

	  /*!
	  * @brief getter of neurons of the Network
	  * @return a vector of pointers over the neurons of the Network 
	  */
vector<Neuron*> Network::getNeurons() const
{return neurons;}

	
	
	
	
