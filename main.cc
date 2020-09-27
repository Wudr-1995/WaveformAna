#include "waveformAna.h"

using namespace std;
int main(int argc, char **argv) {
	if (waveformAna(argc, argv))
		cout << "Success!" << endl;
	else
		cout << "Error!" << endl;
	return 0;
}
