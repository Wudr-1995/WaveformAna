#include "waveformAna.h"

using namespace std;

int main(int argc, char **argv) {
	if (waveformAna(argc, argv))
		return 1;
	else
		return 0;
}

bool waveformAna(int argc, char **argv)
{
	if (argc == 2) {
		cout << "Input arguments:" << endl;
		cout << "[0]: 'WaveAna'" << endl;
		cout << "[1]: Input data type." << endl;
		cout << "[2]: The path of input file." << endl;
		cout << "[3]: Lower bound." << endl;
		cout << "[4]: Higher bound." << endl;
		cout << "[5]: Scale." << endl;
		cout << "[6]: The number of sample points." << endl;
		cout << "[7]: The number of waveforms." << endl;
		cout << "[8]: Threshold (default 1mV)." << endl;
		return false;
	}
	if (argc != 8 && argc != 9) {
		cout << "Caution!" << endl;
		cout << "Input arguments:" << endl;
		cout << "[0]: 'WaveAna'" << endl;
		cout << "[1]: Input data type." << endl;
		cout << "[2]: The path of input file." << endl;
		cout << "[3]: Lower bound." << endl;
		cout << "[4]: Higher bound." << endl;
		cout << "[5]: Scale." << endl;
		cout << "[6]: The number of sample points." << endl;
		cout << "[7]: The number of waveforms." << endl;
		cout << "[8]: Threshold (default 1mV)." << endl;
		cout << "Wrong number ("<< argc <<") of input arguments!" << endl;
		return false;
	}
	// Input arguments:
	// [0]: "./WavemAna"
	// [1]: Input data type.
	// [2]: The path of input file.
	// [3]: Lower bound.
	// [4]: Higher bound.
	// [5]: Scale.
	// [6]: The number of sample points.
	// [7]: The number of waveforms.
	// [8]: Threshold (default 1mV).
	
	double Scale, Nsize, RangeA, RangeB, Threshold = 1, Hsize = 401, WavNum;
	int type;
	sscanf(argv[1], "%d", &type);
	TString name(argv[2]);
	sscanf(argv[3], "%lf", &RangeA);
	sscanf(argv[4], "%lf", &RangeB);
	sscanf(argv[5], "%lf", &Scale);
	sscanf(argv[6], "%lf", &Nsize);
	sscanf(argv[7], "%lf", &WavNum);
	if (argc == 8)
		sscanf(argv[8], "%lf", &Threshold);
	if (RangeA < 0) {
		cout << "Error: lower bound (" << RangeA <<") is smaller than 0." << endl;
		return false;
	}
	if (RangeB > Nsize) {
		cout << "Error: higher bound (" << RangeB << ") is bigger than the number of sample points (" << Nsize << ")." << endl;
		return false;
	}
	if (RangeA > RangeB) {
		cout << "Error: lower bound (" << RangeA << ") is bigge than higher bound (" << RangeB << ")." << endl;
		return false;
	}
	TString ro(".root");
	TString tx(".txt");
	TFile * file = new TFile(name + ro, "recreate");
	ifstream in;
	ofstream out;
	in.open(name + tx);
	out.open(name + "_wf" + tx);
	double Ori_signal, baseline, point, amp, peak;
	double nan;
	double rise_low = 0, rise_high = 0, fall_low = 0, fall_high = 0, rise_half = 0, fall_half = 0, val;
	double FWHM, risetime, falltime, Q, Ped, SPE, t, S, P;
	Int_t n, count = 0;
	TH1F *h1 = new TH1F("An_input_waveform", "An_input_waveform", Nsize, 0, 1400);
	TH1F *h2 = new TH1F("Average_waveform", "Average_waveform", Hsize, 0, 80);
	TH1F *h3 = new TH1F("waveform", "```", Nsize, 0, 1400);
	TH1F *h4 = new TH1F("Amp_spectrum", "Amp_spectrum", 200, 0, 40);
	TH1F *h4_inte = new TH1F("Integration_of_Amp_Spec", "Integration", 200, 0, 40);
	TH1F *h5 = new TH1F("Charge_spectrum", "Charge_spectrum", 1300, -1, 12);
	TH1F *h5_inte = new TH1F("Integration_of_Charge_Spec", "Integration", 1300, -1, 12);
	TH1F *h6 = new TH1F("Rise", "Rise", 75, 0, 30);
	TH1F *h7 = new TH1F("Fall", "Fall", 75, 0, 30);
	TH1F *h8 = new TH1F("FWHM", "FWHM", 75, 0, 30);
	TH2D *QvA = new TH2D("Charge_vs_Amplitude", "Charge_vs_Amplitude;/ pC;/ mV", 1300, -1, 12, 200, 0, 40);
	//h2->GetYaxis()->SetRangeUser(-50, 5);
	for (Int_t i = 0; i < Hsize; i ++)
		h2->SetBinContent(i + 1, 0);
	if (!in.good()) {
		cout << "Open input file Wrong" << endl;
		return false;
	}
	for (Int_t i = 0; i < WavNum; i ++)
	{
		for (Int_t j = 0; j < Nsize; j ++)
		{
			if (type == 2)	
				in >> Ori_signal >> nan;
			else
				in >> Ori_signal;
			h1->SetBinContent(j + 1, 1000 * Ori_signal);
		}
		baseline = 0;
		for (Int_t j = 0; j < 300; j ++)
		{
			point = h1->GetBinContent(j + 1);
			baseline = baseline + point;
		}
		baseline = baseline / 300;
		h1->GetXaxis()->SetRangeUser(RangeA, RangeB);
		peak = h1->GetMinimumBin();
		if (peak < RangeA || peak > RangeB)
			continue;
		amp = baseline - h1->GetBinContent(peak);
		h4->Fill(amp);
		h1->GetXaxis()->SetRangeUser(0, Nsize);
		double charge = 0;
		for (Int_t j = RangeA; j < RangeB; j ++)
			charge = charge + baseline - h1->GetBinContent(j);
		h5->Fill(charge * Scale / 50);
		QvA->Fill(charge * Scale / 50, amp);
		if (amp > Threshold)
		{
			count ++;
			n = peak - 200;
			for (Int_t j = 0; j < Hsize; j ++)
			{
				h2->SetBinContent(j + 1, h2->GetBinContent(j + 1) + h1->GetBinContent(n) - baseline);
				n ++;
			}
		}
		for (Int_t j = peak - 150; j < peak; j ++)
		{
			val = baseline - h1->GetBinContent(j);
			if (val < 0.1 * amp)
				rise_low = j;
			if (val < 0.9 * amp)
				rise_high = j;
			if (val < 0.5 * amp)
				rise_half = j;
		}
		for (Int_t j = 0; j < Nsize; j ++)
		{
			h3->SetBinContent(j + 1, h1->GetBinContent(Nsize - j));
		}
		peak = Nsize - peak + 1;
		for (Int_t j = peak - 150; j < peak; j ++)
		{
			val = baseline - h3->GetBinContent(j);
			if (val < 0.1 * amp)
				fall_low = Nsize - j + 1;
			if (val < 0.9 * amp)
				fall_high = Nsize - j + 1;
			if (val < 0.5 * amp)
				fall_half = Nsize - j + 1;
		}
		risetime = (rise_high - rise_low) * Scale;
		falltime = (fall_low - fall_high) * Scale;
		FWHM = (fall_half - rise_half) * Scale;
		if (amp > 3)
		{
			h6->Fill(risetime);
			h7->Fill(falltime);
			h8->Fill(FWHM);
		}
	}
	for (Int_t j = 1; j <= 600; j ++)
		h4_inte->SetBinContent(j, h4->Integral(j, 600));
	for (Int_t j = 1; j <= 2000; j ++)
		h5_inte->SetBinContent(j, h5->Integral(j, 2000));
	Ped = h5->GetMaximumBin();
	SPE = 0;
	t = 0;
	for (Int_t j = Ped + 25; j < 150; j ++)
		if (h5->GetBinContent(j) > t)
		{
			SPE = j;
			t = h5->GetBinContent(j);
		}
	TF1 * f1 = new TF1("f1", "gaus", Ped * 0.01 - 1 - 0.1, Ped * 0.01 - 1 + 0.1);
	TF1 * f2 = new TF1("f2", "gaus", SPE * 0.01 - 1 - 0.2, SPE * 0.01 - 1 + 0.3);
	f1->SetParameter(1, Ped * 0.01 - 1);
	f2->SetParameter(1, SPE * 0.01 - 1);
	h5->Fit("f1", "R");
	h5->Fit("f2", "R+");
	P = f1->GetParameter(1);
	S = f2->GetParameter(1);
	double gain = (S - P) / 0.16;
	for (Int_t i = 0; i < Hsize; i ++)
		if (count)
			h2->SetBinContent(i + 1, h2->GetBinContent(i + 1) / count);
	for (Int_t i = 0; i < Hsize; i ++)
		out << h2->GetBinContent(i + 1) << endl;
	cout << "amp" << amp << endl;
	cout << "count" << count << endl;
	cout << "baseline" << baseline <<endl;
	peak = h2->GetMinimumBin();
	amp = baseline - h2->GetBinContent(peak);
	for (Int_t i = peak - 20 / 0.4; i < peak; i ++)
	{
		val = baseline - h2->GetBinContent(i);
		if (val < 0.1 * amp)
			rise_low = i;
		if (val < 0.9 * amp)
			rise_high = i;
		if (val < 0.5 * amp)
			rise_half = i;
	}
	for (Int_t i = 0; i < Hsize; i ++)
	{
		h3->SetBinContent(i + 1, h2->GetBinContent(Hsize - i));
	}
	peak =h3->GetMinimumBin();
	for (Int_t i = peak - 40 / 0.4; i < peak; i ++)
	{
		val = baseline - h3->GetBinContent(i);
		if (val < 0.1 * amp)
			fall_low = Hsize - i + 1;
		if (val < 0.9 * amp)
			fall_high = Hsize - i + 1;
		if (val < 0.5 * amp)
			fall_half = Hsize - i + 1;
	}
	Q = 0;
	for (Int_t i = rise_low; i < fall_low; i ++)
	{
		Q = Q + (baseline - h2->GetBinContent(i)) * 0.0000001 / 50000000;
	}
	risetime = (rise_high - rise_low) * Scale;
	falltime = (fall_low - fall_high) * Scale;
	FWHM = (fall_half - rise_half) * Scale;
	cout << "Risetime" << risetime << endl;
	cout << "Falltime" << falltime << endl;
	cout << "FWHM" << FWHM << endl;
	cout << "Q" << Q <<endl;
	cout << "Gain: " << gain << endl;

	h1->GetXaxis()->SetTitle("/ns");
	h1->GetYaxis()->SetTitle("/mV");
	h2->GetXaxis()->SetTitle("/ns");
	h2->GetYaxis()->SetTitle("/mV");
	h4->GetXaxis()->SetTitle("/mV");
	h4_inte->GetXaxis()->SetTitle("/mV");
	
	
	file->cd();
	h2->Write();
	h1->Write();
	h4->Write();
	h4_inte->Write();
	h5->Write();
	h6->Write();
	h7->Write();
	h8->Write();
	QvA->Write();
	in.close();
	out.close();
	file->Close();
	// auto c = new TCanvas();
	// c->Divide(1, 2, 0, 0);
	// c->cd(1);
	// c->GetPad(1)->SetGridx();
	// c->GetPad(1)->SetRightMargin(.01);
	// h4->Draw();
	// c->cd(2);
	// c->GetPad(2)->SetGridx();
	// h4_inte->Draw();

	// auto c1 = new TCanvas();
	// c1->Divide(1, 2, 0, 0);
	// c1->cd(1);
	// c1->GetPad(1)->SetGridx();
	// h5->Draw();
	// c1->cd(2);
	// c1->GetPad(2)->SetGridx();
	// h5_inte->Draw();

	// auto c2 = new TCanvas();
	// c2->Divide(1, 1);
	// c2->GetPad(1)->SetGridx();
	// QvA->Draw("colz");


	return true;
}
