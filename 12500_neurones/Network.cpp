#include "Network.hpp"
#include <random>


//////////////////Constructeurs Destructeurs


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
 
 Network::Network(Neuron n1, Neuron n2)
 {
	 neurons.push_back(new Neuron(n1));
	 neurons.push_back(new Neuron(n2));
	 n1.setConnexions(vector<int>({0,1}));
	 n2.setConnexions(vector<int>({1,0}));
 }					

 
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

vector<Neuron*> Network::getNeurons() const
{return neurons;}
		
	
	
	
	
