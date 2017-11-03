#include "Network.hpp"
#include <random>


//////////////////Constructors & Destructor

	  /*!
	  * @brief Constructor of the Network 
	  * We create a tab in wich we have excitatory and inhibitory neurons related by connections
	  */
 Network::Network()
 {
	 for(int i(0); i<nbNeuronExc;++i) 
	  {
	    neurons.push_back(new Neuron());
	    neurons[i]->setExcInhib(true);
	    neurons[i]->connexions_fill(i);
	  }
	  
	 for(int j(nbNeuronExc); j<(nbNeuronExc+nbNeuronIn);++j) //je crée 2500 neurones inhibiteurs
	  {
		neurons.push_back(new Neuron());
		neurons[j]->setExcInhib(false);
		neurons[j]->connexions_fill(j);
	  }
	  
	  cout<<"#constructed neurons : "<<neurons.size()<<endl;
  
 }
 
	  /*!
	  * @brief Constructor of the Network composed of 2 neurons to observe the connection between them
	  * We create two excitatory neuron related by a connection from the first to the second
	  */
 Network::Network(Neuron* n1, Neuron* n2)
 {
	 neurons.push_back(n1);
	 neurons.push_back(n2);
	 neurons[0]->setEfficientConnections(vector<int>({1}));
	 neurons[1]->setEfficientConnections(vector<int>({}));
 }					

	  /*!
	  * @brief Destructor of Network (free the pointers) 
	  */
 Network::~Network() 
 {
    for (auto& e : neurons)
     {
        e->setSpike(false);
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
			neurons[i]->update_state(simTime);
			
			for(size_t j(0);j<(neurons[i]->getEfficientConnections().size());j++) 
			{
				 neurons[i]->emit_signal(neurons[neurons[i]->getEfficientConnections()[j]]);
			}									  
			  
		}
		    
	}
			
			
	
		
		

//////////////////getters

	  /*!
	  * @brief getter of neurons of the Network
	  * @return a vector of pointers over the neurons of the Network 
	  */
vector<Neuron*> Network::getNeurons() const
{return neurons;}
		
	
	
	
	
