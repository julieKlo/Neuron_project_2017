#include "Network.hpp"
#include <random>


//////////////////Constructors & Destructor

	  /*!
	  * @brief Constructor of the Network 
	  * We create a tab in wich we have excitatory and inhibitory neurons related by connections
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
	  
	  for(int j(nbNeuronExc); j<(nbNeuronExc+nbNeuronIn);++j) 
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
 
 
 void Network::run() {
	 int t = tstart;
	 
	 while(t < tstop)
	 {
		
		for(size_t i(0); i<neurons.size();i++)
		{
			bool spiked = neurons[i]->update_state(t);
			
			if (spiked) {
				for(size_t j(0);j < (neurons[i]->getConnexions().size());j++) 
				{
					neurons[j]->setBufferDelay( (t + D)%(BUFFER_SIZE), neurons[i]->getJconnect() );
					countEmittedSignals++;
				}	
			}								  
			  
		}
		
		if (t % 100 == 0)
		{
			cout << t/100<<"%" << endl;
		}
		
		t++;
	 }
 }

 
	  /*!
	  * @brief Constructor of the Network composed of 2 neurons to observe the connection between them
	  * We create two excitatory neurons related by a connection from the first to the second
	  */
 Network::Network(Neuron* n1, Neuron* n2)
 {
	 neurons.push_back(n1);
	 neurons.push_back(n2);
	 
	 // 0 transmet à 1
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
	  * @brief update the Network at each step of time
	  * @param an int corresponding to the simulation time
	  * 
	  * it updates each neuron of the Network one at a time
	  * and send the signals if necessary (with method emit_signal)
	  */
	void Network:: update(int simTime)
	{
		for(size_t i(0); i<neurons.size();i++)
		{
			bool spiked = neurons[i]->update_state(simTime);
			
			if (spiked) {
				for(size_t j(0);j<(neurons[i]->getConnexions().size());j++) 
				{
					neurons[j]->setBufferDelay( (simTime+D)%(BUFFER_SIZE), neurons[i]->getJconnect() );
					countEmittedSignals++;
				}	
			}								  
			  
		}
		    
	}
			
			
	
		
		

//////////////////getter

	  /*!
	  * @brief getter of neurons of the Network
	  * @return a vector of pointers over the neurons of the Network 
	  */
vector<Neuron*> Network::getNeurons() const
{return neurons;}

	
	
	
	
