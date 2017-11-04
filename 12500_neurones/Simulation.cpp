#include "Simulation.hpp"



/*!
 * @brief Consrtuct a simulatin according to n, an int chosen by the user on the terminal
 * @param n, an int corresponding to the user's choice
 * The main ask for a type of simulation and the user choose by entering an int 
 * (1=ONE_NEURON,2=TWO_NEURONS,3=NETWORK).
 */ 
Simulation::Simulation(int n)
{
	if(n==1)
	{simulate_one_neuron();}
	if(n==2)
	{simulate_two_neurons();}
	if(n==3)
	{simulate_Network();}
}

/*!
 * @brief simulate one neuron's behaviour
 * It creates a Neuron which generates its own current so that it increases its
 * own potential and spikes regularly.
 */ 
void Simulation:: simulate_one_neuron()
{
	Neuron n;
	n.setCurrElec(23.0);
	n.setTest(true);
	
	int t(tstart);
	while(t<tstop)
	 {
	  t++;
	  n.update_state(t);
	  //if(n.getClock()%100==0){cout<<"membrane potential="<<n.getPotMemb()<<endl;}
	 }
	 cout<<"times when spikes occur:"<<endl;
	 for(size_t i(1);i<n.getTimes().size();++i)
	 {cout<<"spikes n°"<<i<<" at: "<<n.getTimes()[i]<<endl;}
}

/*!
 * @brief simulates 2 neurons to see if the connection between them works
 */
void Simulation:: simulate_two_neurons()
{
	Network N(new Neuron,new Neuron);
	int t(tstart);
	while(t<tstop)
	 {
	  t++;
	  N.update(t);
	 }
	 for(size_t t(0);t<N.getNeurons().size();++t)
	 {	 
       cout<<"times when spikes occured:"<<endl;
	   for(size_t i(1);i<N.getNeurons()[t]->getTimes().size();++i)
	   {cout<<"spikes n°"<<i<<" du neurone "<<t+1<<" at: "<<N.getNeurons()[t]->getTimes()[i]<<endl;}
	 }
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
	Network N;
	int t(tstart);
	while(t<tstop)
	 {
	  t++;
	  N.update(t);
	  cout<<"t="<<t<<endl;
	 }
	 
	 
	 ofstream sortie_spikes("times_spike_neuron.txt");
	 
	 for(size_t i(0);i<N.getNeurons().size();++i)
	 { for(size_t j(1); j<N.getNeurons()[i]->getTimes().size();++j)
		 {
	 sortie_spikes<<"n"<<i+1<<" spiked at time "<<N.getNeurons()[i]->getTimes()[j]<<endl;
		 }
	 sortie_spikes<<endl;
	 }
	 	 sortie_spikes.close();   



}



