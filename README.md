# WaveformAna
A waveform analysis program for PMT & SiPM
## Compile Need
CERN ROOT
## Compile Command
g++ waveformAna.cc -Wall `root-config --cflags` `root-config --libs` -lRooFit -lFumili -lpthread -o WaveAna
## Type of input data
Because of the data requirment system we use, there are always two column in the input txt, the first column is the data we need, the other is useless. Just like this.

-0.001875	-0.001875
-0.002031	-0.002031
-0.002188	-0.002188
-0.002031	-0.002031
-0.001875	-0.001875
-0.001875	-0.001875
-0.001719	-0.001719
-0.002031	-0.002031
-0.002500	-0.002500
-0.002188	-0.002188
-0.001719	-0.001719
-0.001719	-0.001719
-0.002500	-0.002500

The program also can accept the input file who has only one column. It's necessary to set the first argument input in the command line (1: one line type, 2: two line type). If type 1 is chosen, the program also can due with input file who has one waveform per line.

For convenience, all waveform data were put into one txt file. (This step can be achieved by "type \*.txt >> ../input.txt" command in windows cmd")
## Command
Input arguments:

1. "./WaveAna"
2. Input data type.
3. The path of input file.
4. Lower bound.
5. Higher bound.
6. Scale.
7. The number of sample points.
8. The number of waveforms.
9. Threshold (default 1mV).

### An example:
```bash
./WaveAna 2 ./waveforms.txt 500 700 0.2 1400 20000 0.5
```

