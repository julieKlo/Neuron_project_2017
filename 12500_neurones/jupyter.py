import numpy as np
import matplotlib.pyplot as pl

data = np.genfromtxt('times_spike_neuron.txt')

select= np.array([d for d in data if d[1] < 30])
data1= select.transpose()
pl.scatter(0.1*data1[0],data1[1],alpha=0.8, edgecolors='none', s=10);
pl.xlabel("Time (ms)")
pl.ylabel("#neurons")
pl.show();

n, bins, patches = pl.hist(0.1*data1[0], 50, normed=0, alpha=0.75)
pl.xlabel("Time (ms)")
pl.ylabel("Number of spikes")
pl.show();

OR



import numpy as np
import pylab as pl

raw_data = np.genfromtxt('times_spike_neuron.txt')

select = np.array([d for d in raw_data if d[1] < 50])
data = select.transpose()

fig = pl.figure(dpi = 200)


# Main plot
main_scatter = fig.add_subplot(211)
main_scatter.scatter(0.1 * data[0], data[1], alpha = 0.8, edgecolors = 'none', s = 10)
main_scatter.set_ylabel('Neuron ID')
pl.xlim([100, 300])


# Histogram
histo = fig.add_subplot(212)
histo.hist(0.1 * data[0], 50, normed = 0, alpha = 0.75)
histo.set_xlabel('t [ms]')
histo.set_ylabel('rate [Hz]')
pl.xlim([100, 300])





# Show graph
pl.show()



OR 
 

import numpy as np
import pylab as pl

raw_data = np.genfromtxt('times_spike_neuron.txt')

select = np.array([d for d in raw_data if d[1] < 50])
data = select.transpose()

fig = pl.figure(dpi = 200)


# Main plot
main_scatter = fig.add_subplot(211)
main_scatter.scatter(0.1 * data[0], data[1], alpha = 0.8, edgecolors = 'none', s = 10)
main_scatter.set_ylabel('Neuron index')
pl.xlim([0, 1000])


# Histogram
histo = fig.add_subplot(212)
histo.hist(0.1 * data[0], 50, normed = 0, alpha = 0.75)
histo.set_xlabel('time (ms)')
histo.set_ylabel('Frequence (Hz)')
pl.xlim([0, 1000])





# Show graph
pl.show()
