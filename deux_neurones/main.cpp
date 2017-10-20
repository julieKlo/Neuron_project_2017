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
	n2.setCanSpike(false); //n2 ne peut que recevoir
	Network N(n1,n2);
	
	int t(tstart);
	 ofstream sortie_pot_memb("membrane_pot.txt"); //ecriture sur le fichier texte
	 
	while(t<tstop)
	{
	t++;
	N.update(t);
	cout<<"n1 "<<N.getNeurons()[0]->getPotMemb()<<endl;
	cout<<"n2 "<<N.getNeurons()[1]->getPotMemb()<<endl;
	sortie_pot_memb<<N.getNeurons()[0]->getPotMemb()<<" dont spike a "<<N.getNeurons()[0]->getTback()<<" ms et n2: "<<N.getNeurons()[1]->getPotMemb()<<" dont spike a "<<N.getNeurons()[1]->getTback()<<endl;
	cout<<t<<endl;
	}
	 sortie_pot_memb.close();

	return 0;
}


 //  C=250 pF
 // Tau=10 mS
 // Tau ref= 2 mS
 // Vreset= -70mV => après un spike
 // dt= 0.1 mS
 
