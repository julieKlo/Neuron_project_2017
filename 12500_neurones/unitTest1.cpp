#include "Network.hpp"
#include <iostream>
#include "gtest/include/gtest/gtest.h"
#include "Constants.hpp"

	  /*!
	  * @brief Tests if the membrane potential is well computed at the first step
	  * we don't consider PoissonGeneration as the neuron is alone and it's difficult to
	  * test because it's random.
	  */
TEST (NeuronTest, MembPotential) 
{
	Neuron n(true);
	n.setCurrElec(1.01);
	n.setTest(true);
	
	n.update_state(0);
	
	EXPECT_EQ(n.getCurrElec()* tau/C * (1-exp(-dt/tau)), n.getPotMemb());
	cout<<"			Right initial Membrane Potential"<<endl;
}

	  /*!
	  * @brief Tests if the times when spikes occur for a single neuron are right (as expcted)
	  */
TEST (NeuronTest, SpikesInTime)
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
	 
	EXPECT_EQ(924, n.getTimes()[0]);
	EXPECT_EQ(1868, n.getTimes()[1]);
	EXPECT_EQ(2812, n.getTimes()[2]);
	
	cout<<"			Right times for spikes"<<endl;
}

	  /*!
	  * @brief test if the number of spikes generated is right (as many as expected)
	  * we don't consider PoissonGeneration as the neuron is alone and it's difficult to
	  * test because it's random.
	  */
TEST (NeuronTest, NbSpikes)
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
	
	EXPECT_EQ(10,n.getNbSpikes()); 
	cout<<"			Right Number of Spikes generated"<<endl;
	
	EXPECT_EQ(10,n.getTimes().size());
	cout<<"		    Right number of spike times have been stored"<<endl;

	
}


   /*!
    * @brief tests if the attribution of the amplitude of the signal the neuron will transmit is right
    */ 
TEST (NeuronTest, J_Value)
{
	Neuron n1(true);
	EXPECT_EQ(Je,n1.getJconnect());
	
	Neuron n2(false);
	EXPECT_EQ(Ji,n2.getJconnect());
	
	cout<<"			Right attribution of J value"<<endl;
}

	  /*!
	  * @brief tests if when 2 neurons are connected the signals are well transmitted
	  */
TEST (NetworkTest, ReceiveSignal)
{
	Network N(new Neuron(true), new Neuron(true));
	N.run();
	
	EXPECT_FALSE(N.getNeurons()[0]->getTimes().empty());
	EXPECT_FALSE(N.getNeurons()[1]->getTimes().empty());
	cout<<"			Both neurons spiked"<<endl;

	EXPECT_FALSE(N.countEmittedSignals==0);
	cout<<"			Neurons were connected and sent signals"<<endl;
	

 }					
 
	  /*!
	  * @brief test if the right number of neurons is generated
	  */
TEST (NetworkTest, CreateNeurons)
{
	Network N;
	
	EXPECT_EQ(nbNeuronExc+nbNeuronIn,N.getNeurons().size());
	cout<<"		    Right number of neurons"<<endl;
	
	int exc(0);
	int inh(0);
	for(size_t t(0);t<N.getNeurons().size();++t)
	{
		if(N.getNeurons()[t]->getExcInhib()) {exc+=1;}
		else{inh+=1;}
	}
	EXPECT_EQ(nbNeuronExc,exc);
	cout<<"		    Right number of excitatory neurons"<<endl;
	EXPECT_EQ(nbNeuronIn,inh);
	cout<<"		    Right number of inhibitory neurons"<<endl;
}





int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}
