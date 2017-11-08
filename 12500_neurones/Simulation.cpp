#include "Simulation.hpp"



/*!
 * @brief Consrtuct a simulation chosen by the user thanks to the method choose_simulation()
 *  It chooses a type of simulation according to the simulation chosen by the user
 */ 
Simulation::Simulation()
{
	switch(choose_simulation())
	{
		case ONE_NEURON : simulate_one_neuron();
		     break;
		case TWO_NEURONS : simulate_two_neurons();
			 break;
	    case NETWORK : simulate_Network();
			 break;
		default: cout<<"Your input is wrong, please refer to the README file"<<endl;
	}
}

/*!
 * @brief simulate one neuron's behaviour
 * It creates a Neuron which generates its own current so that it increases its
 * own potential and spikes regularly.
 */ 
void Simulation:: simulate_one_neuron()
{
	Neuron n(true);
	n.setCurrElec(1.01);
	n.setTest(true);
	
	int t(tstart);
	while(t<tstop)
	 {
	  n.update_state(t);
	  t++;

	 }
	 cout<<"times when spikes occur:"<<endl;
	 for(size_t i(0);i<n.getTimes().size();++i)
	 {cout<<"spikes n°"<<i<<" at: "<<n.getTimes()[i]<<endl;}
}

/*!
 * @brief simulates 2 neurons to see if the connection between them works
 */
void Simulation:: simulate_two_neurons()
{
	Network N(new Neuron(true), new Neuron(true));
		
	N.run();
	
	 for(size_t t(0);t<N.getNeurons().size();++t)
	 {	 
       cout<<"times when spikes occured:"<<endl;
	   for(size_t i(0);i<N.getNeurons()[t]->getTimes().size();++i)
	   {cout<<"spikes n°"<<i<<" du neurone "<<t+1<<" at: "<<N.getNeurons()[t]->getTimes()[i]<<endl;}
	 }
	 cout<<"#signaux emis "<<N.countEmittedSignals<<endl;
}

/*!
 * @brief Creates a Network whose dimensions are stored in Constants.hpp file and update it
 * 
 * Here we create a Network with excitatory and inhibitory neurons which are interacting
 * and we store the result of their interactions (time of their spikes) in a txt file by
 * using an ofstream
 */
void Simulation:: simulate_Network()
{   
	Network N = Network();
	
	N.run();
	 
	 
	 ofstream sortie_spikes;
	 sortie_spikes.open("times_spike_neuron.txt");
	 
	 for(size_t i(0);i<N.getNeurons().size();++i)
	 { for(size_t j(0); j<N.getNeurons()[i]->getTimes().size();++j)
		 {
	 sortie_spikes<<N.getNeurons()[i]->getTimes()[j]<<"\t"<<i<<endl;
		 }
	 sortie_spikes<<endl;
	 }
	 	 sortie_spikes.close();   

}

/*!
 * @brief Allows the user to choose the simulation he wants to compute
 * 
 * The user enters a string which is converted into a SIMULATION_TYPE 
 * If it returns OTHER, the program will stop (see constructor)
 */ 
SIMULATION_TYPE Simulation:: choose_simulation() 
{
   string n;
   cout<<"Choose Simulation between : ONE_NEURON, TWO_NEURONS or NETWORK (write down one of those):"<<endl;
   cin>>n;
   if(n=="ONE_NEURON"){return ONE_NEURON ;}
   if(n=="TWO_NEURONS"){return TWO_NEURONS;}
   if(n=="NETWORK"){return NETWORK;}
   else
   {return OTHER;}
}


