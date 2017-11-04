#include "Network.hpp"
#include <iostream>
#include "gtest/include/gtest/gtest.h"
#include "Constants.hpp"

	  /*!
	  * @brief Test if the membrane potential is well computed at the first step
	  * we don't consider PoissonGeneration as the neuron is alone and it's difficult to
	  * test because it's random.
	  */
TEST (NeuronTest, MembPotential) 
{
	Neuron n;
	n.setCurrElec(1.0);
	n.setTest(true);
	
	n.update_state(0);
	
	EXPECT_EQ(tau*(1.0-exp(-tstart/tau)), n.getPotMemb());
	cout<<"			Right initial Membrane Potential"<<endl;
}

	  /*!
	  * @brief Test if after one step the computation of the membrane potential is still right
	  * we don't consider PoissonGeneration as the neuron is alone and it's difficult to
	  * test because it's random.
	  */
TEST (NeuronTest, MembPotInTime)
{
	Neuron n;
	n.setCurrElec(1.0);
	n.setTest(true);
	
	n.update_state(1);
	EXPECT_EQ(tau*(1.0-exp(-1/tau)), n.getPotMemb());
	cout<<"			Right time for membrane Potential"<<endl;
}

	  /*!
	  * @brief test if the number of spikes is right
	  * we don't consider PoissonGeneration as the neuron is alone and it's difficult to
	  * test because it's random.
	  */
TEST (NeuronTest, NbSpikes)
{
	Neuron n;
	n.setCurrElec(23.0);
	n.setTest(true);
	
	n.update_state(1);
	EXPECT_EQ(0,n.getNbSpikes());
	
	int t(tstart);
	while(t<tstop)
	{
		n.update_state(t);
		++t;
	}
	EXPECT_EQ(4,n.getNbSpikes()); //approximation car dépend de Cext
	cout<<"			Right Number of Spikes generated"<<endl;
	
	EXPECT_EQ(false,n.getTimes().empty());
	cout<<"		       Spike times have been stored"<<endl;

	
}

	  /*!
	  * @brief test if the connection between 2 neurons is well generated
	  */
TEST (NeuronTest, ConnexionGeneration)
{
	Neuron n1;
	n1.connexions_fill(1);
	EXPECT_EQ(conn_exc+conn_inh,n1.getNbConn());
	cout<<"			Connections generated"<<endl;
	
}

	  /*!
	  * @brief test if when 2 neurons are connected the signal is well transmitted
	  */
TEST (NetworkTest, ReceiveSignal)
{

	Network N(new Neuron,new Neuron);
	
	N.getNeurons()[0]->setSpike(true);
	N.getNeurons()[0]->emit_signal(N.getNeurons()[1]);
	EXPECT_EQ(Je,N.getNeurons()[1]->getBufferDelay()[D]);
	cout<<"			Excitatory signal generated from one neuron to the other"<<endl;
	
	N.getNeurons()[1]->setBufferDelay(D,0);
	N.getNeurons()[0]->setSpike(true);
	N.getNeurons()[0]->setExcInhib(false);
	N.getNeurons()[0]->emit_signal(N.getNeurons()[1]);
	EXPECT_EQ(Ji,N.getNeurons()[1]->getBufferDelay()[D]);
	cout<<"			Inhibitory signal generated from one neuron to the other"<<endl;

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

	  /*!
	  * @brief test if the attitude of various neurons is coherent
	  */



int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}
