#include <iostream>
using namespace std;
#include "neuron.hpp"
#include "Constants.hpp"
#include "Network.hpp"
#include "Simulation.hpp"
#include <fstream>

int main()
{
   int n;
   cout<<"Choose Simulation between : ONE_NEURON, TWO_NEURONS or NETWORK (write 1,2 or 3):"<<endl;
   while((n>3) or (n<1))
   {cin>>n;}
   Simulation S(n);
   
	return 0;
}


 //  C=250 pF
 // Tau=10 mS
 // Tau ref= 2 mS
 // Vreset= -70mV => après un spike
 // dt= 0.1 mS
 
