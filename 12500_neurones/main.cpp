#include <iostream>
using namespace std;
#include "neuron.hpp"
#include "Constants.hpp"
#include "Network.hpp"
#include <fstream>

int main()
{
	Network Net;
	
	int t(tstart);
	 //ofstream sortie_pot_memb("membrane_pot.txt"); //ecriture sur le fichier texte
	 
	while(t<tstop)
	{
	cout<<t<<endl;
	t++;
	Net.update(t);
	
	//sortie_pot_memb<<N.getNeurons()[0]->getPotMemb()<<" dont spike a "<<N.getNeurons()[0]->getTback()<<" ms et n2: "<<N.getNeurons()[1]->getPotMemb()<<" dont spike a "<<N.getNeurons()[1]->getTback()<<endl;
	cout<<t<<endl;
	}
	 //sortie_pot_memb.close();

	return 0;
}


 //  C=250 pF
 // Tau=10 mS
 // Tau ref= 2 mS
 // Vreset= -70mV => après un spike
 // dt= 0.1 mS
 
