# WaveformAna
A waveform analysis program for PMT &amp; SiPM
## Compile Need
CERN ROOT
## Compile Command
g++ waveformAna.cc -Wall `root-config --cflags` `root-config --libs` -lRooFit -lFumili -lpthread -o WaveAna
## Type of input data
Because of the data requirment system used, there are always two column in the input txt, the first column is the data we need, the other is useless. Just like this.
Data	Others
