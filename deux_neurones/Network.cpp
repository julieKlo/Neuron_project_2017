#include "Network.hpp"


//////////////////Constructeurs Destructeurs

 Network::Network(Neuron n1, Neuron n2)
 {
	 neurons.push_back(n1);
	 neurons.push_back(n2);
	 
	 connexions=vector<vector<int> >({{0,0},{1,0}}); //1er neurone n'est pas connecté au 1er 
 }											   //mais au 2e et 2e connecté à rien


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
		for(int i(0); i<neurons.size();i++) //j'update chaque neurone du tableau
		{
			neurons[i]->update_state(dt, curr_elec, simTime);
			
			
			for(int j(0);j<connexions[i].size();j++) //je regarde si la connexion à un autre neurone existe
			{
			  if((j<neurons.size()))  
			  { if((connexions[i][j]!=0) or (!connexions[i][j]).empty())
				{
				 neurons[i]->emit_signal(neurons[j]); //si mon neurone i est connecté et a emis un spike
				}									  //je lui fait emettre un signal à son neurone conncté
			  }
		    }
		    
		}
			
			
	}
		
		
		
		
	
	
	
	
