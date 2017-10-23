#include "Network.hpp"
#include <iostream>
#include "gtest/include/gtest/gtest.h"
#include "Constants.hpp"

TEST (Neuron, MembPotential) 
{
	Neuron n;
	n.setCurrElec(1.0);
	
	n.update_state(dt,n.getClock());
	
	EXPECT_EQ(tau*(1.0-exp(-dt/tau)), n.getPotMemb());
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}
