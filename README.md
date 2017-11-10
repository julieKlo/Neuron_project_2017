Neurons Project SV 2017
Julie Kloeckner SCIPER:269816

I. DESCRIPTION

The aim of the program is to simulate a Network composed of neurons connected one with each other. 
There are two types of neurons: excitatory and inhibitory. The excitatory ones send a positive amplitude when they spike so that they increase the membrane potential of the neurons they are connected to.
The inhibitory ones send a negative amplitude when they spike so that they decrease the membrane potential of the neurons they are connected to. As there is both of these neuron types in the Network during a simulation, the membrane potential of each neuron tends to an equilibrum. Thus we can see it on the graphs.


II. COMPILATION

To compile the project it is only necessary to be in the right folder and input "make" on the terminal. As we use CMake, it will compile all the program.

To execute the program you write: "./Neurons" on the terminal

If you want to test the program it is: "./Neurons_unittest1" on the terminal


III. UTILISATION

Once the program started, it will ask for a simulation type. You only have to write:

"ONE_NEURON" if you want to simulate one neuron
"TWO_NEURONS" if you want to simulate 2 neurons
"NETWORK" if you want to simulate the whole Network

WARNING: if you don't write one of those, the program won't work and you will have to start again.This is to avoid aberrent results.

In the file named "Constants.hpp" you can modify the parameters of the Network and the neuron (number of excitatory/inhibitory neurons and excitatory/inhibitory connections, simulation time, maximum membrane potential, amplitude of transmitted signal, tau, capacity, delay, extern capacity and extern potential, ETA and G).

If you start NETWORK, the spike times of all the neurons will be stored on a file named "times_spike_neuron.txt" which you could use to create a graph of the simulation on : 
https://cs116-plot.antoinealb.net/
or on:
https://try.jupyter.org/ by choosing in jupyter.py how to compute the graph
