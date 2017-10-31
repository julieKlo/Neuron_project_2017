#include "Network.hpp"
#include <random>


//////////////////Constructeurs Destructeurs

	  /*!
	  * @brief Constructor of the Network 
	  */
 Network::Network()
 {
   //création de mon tableau de neurones
	 for(int i(0); i<nbNeuronExc;++i) //je crée 10000 neurones excitateurs
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
	  
	  //cout<<"#neurones: "<<neurons.size()<<endl;
  
 }
 
	  /*!
	  * @brief Constructor of the Network composed of 2 neurons to observe the connection between them
	  */
 Network::Network(Neuron n1, Neuron n2)
 {
	 neurons.push_back(new Neuron(n1));
	 neurons.push_back(new Neuron(n2));
	 n1.setConnexions(vector<int>({0,1}));
	 n2.setConnexions(vector<int>({1,0}));
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
 
 

//////////////////Action sur les connexions


	  /*!
	  * @brief update the Network at each step of time
	  * @param an int corresponding to the simulation time
	  * 
	  * it updates each neuron of the Network one at a time
	  * and them check the connections between each neuron to
	  * send the signals if necessary 
	  */
	void Network:: update(int simTime)
	{
		for(size_t i(0); i<neurons.size();i++) //j'update chaque neurone du tableau
		{
			neurons[i]->update_state(simTime);
			
			for(size_t j(0);j<(neurons[i]->getConnexions().size());j++) //je regarde si la connexion à un autre neurone existe
			{
			   if(neurons[i]->getConnexions()[j]!=0)
				{
				 neurons[i]->emit_signal(neurons[j],neurons[i]->getConnexions()[j]);       //si mon neurone i est connecté et a emis un spike
				 //cout<<"j'ai lu une connexion de n"<<i+1<<" a n"<<j+1<<endl;  		   //je lui fait emettre autant de signaux qu'il 
																						   //y a de connexions d'un neurone vers l'autre
				}									  
			  
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
		
	
	
	
	
