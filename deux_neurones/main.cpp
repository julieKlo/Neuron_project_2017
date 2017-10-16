#include <iostream>
using namespace std;
#include "neuron.hpp"
#include "Constants.hpp"
#include "Network.hpp"
#include <fstream>

int main()
{
	Neuron n1;
	Neuron n2;
	Network N(n1,n2);
	
	int t(tstart);
	 ofstream sortie_pot_memb("membrane_pot.txt"); //ecriture sur le fichier texte
	 
	while(t<tstop)
	{
	t++;
		
	N.update(t);
	sortie_pot_memb<<n1.getPotMemb()<<" dont spike a "<<n1.getTback()<<" ms et n2: "<<n2.getPotMemb()<<" dont spike a "<<n2.getTback()<<endl;
	}
	 sortie_pot_memb.close();

	return 0;
}


 //  C=250 pF
 // Tau=10 mS
 // Tau ref= 2 mS
 // Vreset= -70mV => après un spike
 // dt= 0.1 mS
 
