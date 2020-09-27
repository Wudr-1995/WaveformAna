#include "wavefromAna.h"

using namespace std;
void main(int argc, char* argv) {
	if (waveformAna(argc, argv))
		cout << "Success!" << endl;
	else
		cout << "Error!" << endl;
}
