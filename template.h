#ifndef FITOMEGAETA_H
#define FITOMEGAETA_H
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooFFTConvPdf.h"
#include "RooDataHist.h"
#include "RooLandau.h"
#include "RooGaussian.h"
#include "RooBreitWigner.h"
#include "RooPolynomial.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooPlot.h"
#include "RooCmdArg.h"
#include "RooRealProxy.h"
#include "RooAbsPdf.h"
#include "RooFitResult.h"
#include "RooPrintable.h"
#include "RooStats/RooStatsUtils.h"
#include "TCut.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TH3D.h"
#include "TChain.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TF1.h"
#include "TF2.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraph2D.h"
#include "TMath.h"
#include "TFile.h"
#include "TMinuit.h"
#include "TFumili.h"
#include "TFumiliMinimizer.h"
#include "TComplex.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TStopwatch.h"
#include "TRandom.h"
#include "TLegend.h"
#include "TSystem.h"
#include "TText.h"
#include "TPaveText.h"
#include "TArrow.h"
#include "Rtypes.h"
#include <fstream>
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <unistd.h>          //chdir()
#include <sys/stat.h>        //mkdir()
#include <sys/types.h>       //mkdir()
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>           //perror()
#include <THStack.h>
#include <TH1.h>
#include <TH1F.h>
#include <TLatex.h>
#include <TList.h>
#include <TAxis.h>
#include <math.h> 

using namespace std;

void MyStyle(){
    // Margins for labels etc.
    gStyle->SetPadLeftMargin(0.25);
    gStyle->SetPadBottomMargin(0.25);
    gStyle->SetPadRightMargin(0.12);
    gStyle->SetPadTopMargin(0.1);//0.12
  //  // No Canvas Border
  //  gStyle->SetCanvasBorderMode(0);
  //  gStyle->SetCanvasBorderSize(0);
  //  // White BG
  //  gStyle->SetCanvasColor(10);
  //  // Format for axes
      gStyle->SetTitleFont(42," ");    // set the pad title font
      gStyle->SetTitleSize(0.06," ");   //0.03 set the pad title size
      gStyle->SetTitleOffset(1.09," ");
      gStyle->SetLabelFont(42,"xyz");
      gStyle->SetLabelSize(0.04,"xyz");
      gStyle->SetLabelOffset(0.02,"y");
      gStyle->SetLabelOffset(0.02,"x");
      gStyle->SetLabelOffset(0.02,"z");
      gStyle->SetNdivisions(510,"xyz");
      gStyle->SetTitleFont(42,"xyz");
      gStyle->SetTitleColor(1,"xyz");
      gStyle->SetTitleSize(0.09,"xyz");
      gStyle->SetTitleOffset(1.35,"x");
      gStyle->SetTitleOffset(1.09,"y");
      gStyle->SetOptTitle(1);//0-不显示图的title
  //  gStyle->SetOptStat(0);
  //  gStyle->SetHistLineWidth(2);
  //  // No pad borde
  //  //gStyle->SetPadB
  //  //gStyle->SetPadB
  //  // White BG
  //  gStyle->SetPadColor(10);
  //  // No error bars in x direction
  //  gStyle->SetErrorX(0);
  //  // Format legend
  //  gStyle->SetLegendBorderSize(10);
  //  //
  //  gStyle->SetPadTickX(1);
  //  gStyle->SetPadTickY(1);
}
     //gROOT->SetStyle("Plain");
     //gStyle->SetLabelSize(0.06,"xyz");
     //gStyle->SetNdivisions(405,"xyz");
     //gStyle->SetPadTopMargin(.05);
     //gStyle->SetPadLeftMargin(.15);
     //gStyle->SetPadRightMargin(.05);
     //gStyle->SetPadBottomMargin(.15);
     //gStyle->SetTitleSize(0.06,"xyz");
     //gStyle->SetOptTitle(0);
     //gStyle->SetMarkerSize(1.0);
     //gStyle->SetMarkerColor(2);
     //gStyle->SetTitle("");
     //gStyle->SetOptStat(0);
     //gStyle->SetEndErrorSize(0);
void Set_data(TH1F *h1,const char *name)
{
  h1   ->GetXaxis()->SetTitle(name);
  h1   ->SetMarkerStyle(20);
  h1   ->SetMarkerSize(0.7);
  h1   ->SetMarkerColor(kCyan+4);

  h1->GetXaxis()->SetTickLength(0.04);
  h1->GetXaxis()->SetLabelSize(0.04);
  h1->GetYaxis()->SetLabelSize(0.04);
  h1->GetXaxis()->SetTitleOffset(1.1);
  h1->GetXaxis()->SetTitle(name);

  h1->GetYaxis()->SetTickLength(0.04);
  //h1->GetYaxis()->SetTitleOffset(1.5);
  h1->GetYaxis()->SetTitle("events");
  //h1->GetYaxis()->SetRangeUser(0,1.2*h1->GetMaximum());
  //h1->Draw("e");
}


void Set_data(TH1F *h1)
{
  //h1   ->GetXaxis()->SetTitle(name);
  h1   ->SetMarkerStyle(20);
  h1   ->SetMarkerSize(0.4);
  h1   ->SetMarkerColor(kRed);
  //h1->GetXaxis()->SetTickLength(0.04);
  //h1->GetXaxis()->SetLabelSize(0.04);
  //h1->GetXaxis()->SetTitleOffset(1.1);
  ////h1->GetXaxis()->SetTitle(name);

  //h1->GetYaxis()->SetTickLength(0.04);
  //h1->GetYaxis()->SetLabelSize(0.04);
  h1->GetYaxis()->SetTitleOffset(0.5);
  h1->GetXaxis()->SetTitleOffset(0.55);
  //h1->GetYaxis()->SetTitle("events");
  //h1->GetYaxis()->SetRangeUser(0,1.2*h1->GetMaximum());
  //h1->Draw("e");
}
void Set_data(TH1F *h1,Color_t color)
{
  //h1   ->GetXaxis()->SetTitle(name);
  h1   ->SetMarkerStyle(20);
  h1   ->SetMarkerSize(0.7);
  h1   ->SetMarkerColor(color);
  //h1->GetXaxis()->SetTickLength(0.04);
  //h1->GetXaxis()->SetLabelSize(0.04);
  //h1->GetXaxis()->SetTitleOffset(1.1);
  ////h1->GetXaxis()->SetTitle(name);

  //h1->GetYaxis()->SetTickLength(0.04);
  //h1->GetYaxis()->SetLabelSize(0.04);
  h1->GetYaxis()->SetTitleOffset(1.3);
  //h1->GetYaxis()->SetTitle("events");
  //h1->GetYaxis()->SetRangeUser(0,1.2*h1->GetMaximum());
  //h1->Draw("e");
}

void Set_data(TH1F *h1,const char *name,Color_t color)
{
  h1   ->GetXaxis()->SetTitle(name);
  h1   ->SetMarkerStyle(20);
  h1   ->SetMarkerSize(0.7);
  h1   ->SetMarkerColor(color);

  h1->GetXaxis()->SetTickLength(0.04);
  h1->GetXaxis()->SetLabelSize(0.04);
  h1->GetXaxis()->SetTitleOffset(1.1);
  h1->GetXaxis()->SetTitle(name);

  h1->GetYaxis()->SetTickLength(0.04);
  h1->GetYaxis()->SetLabelSize(0.04);
  //h1->GetYaxis()->SetTitleOffset(1.5);
  h1->GetYaxis()->SetTitle("events");
  //h1->GetYaxis()->SetRangeUser(0,1.2*h1->GetMaximum());
  //h1->Draw("e");
}




void Set_inMC(TH1F *h1,const char *name)
{
  h1   ->GetXaxis()->SetTitle(name);
  h1   ->SetFillColor(kSpring+7);
  //h1   ->SetLineWidth(2);
  //h1   ->SetLineStyle(7);

  h1   ->GetXaxis()->SetTickLength(0.04);
  h1   ->GetXaxis()->SetLabelSize(0.04);
  h1   ->GetXaxis()->SetTitleOffset(1.1);

  h1   ->GetYaxis()->SetTickLength(0.04);
  h1   ->GetYaxis()->SetLabelSize(0.04);
  h1   ->GetYaxis()->SetTitleOffset(1.8);
  h1   ->GetYaxis()->SetTitle("events");
  //h1   ->GetYaxis()->SetRangeUser(0,1.2*h1->GetMaximum());
  //h1   ->Draw("same");
}
void Set_inMC(TH1F *h1)
{
  //h1   ->GetXaxis()->SetTitle(name);
  h1   ->SetFillColor(kSpring+7);
  //h1   ->SetLineWidth(2);
  //h1   ->SetLineStyle(7);

  //h1   ->GetXaxis()->SetTickLength(0.04);
  //h1   ->GetXaxis()->SetLabelSize(0.04);
  //h1   ->GetXaxis()->SetTitleOffset(1.1);

  //h1   ->GetYaxis()->SetTickLength(0.04);
  //h1   ->GetYaxis()->SetLabelSize(0.04);
  //h1   ->GetYaxis()->SetTitleOffset(1.8);
  //h1   ->GetYaxis()->SetTitle("events");
  //h1   ->GetYaxis()->SetRangeUser(0,1.2*h1->GetMaximum());
  //h1   ->Draw("same");
}
void Set_inMC(TH1F *h1,const char *name,Color_t color)
{
  h1   ->GetXaxis()->SetTitle(name);
  h1   ->SetFillColor(color);
  //h1   ->SetLineWidth(2);
  //h1   ->SetLineStyle(7);

  h1   ->GetXaxis()->SetTickLength(0.04);
  h1   ->GetXaxis()->SetLabelSize(0.04);
  h1   ->GetXaxis()->SetTitleOffset(1.1);

  h1   ->GetYaxis()->SetTickLength(0.04);
  h1   ->GetYaxis()->SetLabelSize(0.04);
  h1   ->GetYaxis()->SetTitleOffset(1.8);
  h1   ->GetYaxis()->SetTitle("events");
  //h1   ->GetYaxis()->SetRangeUser(0,1.2*h1->GetMaximum());
  //h1   ->Draw("same");
}



void Set_exMC(TH1F *h1,const char *name)
{
  h1   ->GetXaxis()->SetTitle(name);
  h1   ->SetLineColor(kViolet);
  h1   ->SetLineWidth(2);
  h1   ->SetLineStyle(2);
  //h1   ->SetLineStyle(7);
  h1->GetXaxis()->SetTickLength(0.04);
  h1->GetXaxis()->SetLabelSize(0.04);
  h1->GetXaxis()->SetTitleOffset(0.8);
  h1->GetXaxis()->SetTitle(name);

  h1->GetYaxis()->SetTickLength(0.04);
  h1->GetYaxis()->SetLabelSize(0.04);
  h1->GetYaxis()->SetTitleOffset(0.8);
  //h1->GetYaxis()->SetTitle("events");
  //h1->GetYaxis()->SetRangeUser(0,1.2*h1->GetMaximum());
  //h1->Draw("e");
}
void Set_exMC(TH1F *h1)
{
  //h1   ->GetXaxis()->SetTitle(name);
  h1   ->SetLineColor(kBlue);
  h1   ->SetLineWidth(2);
  h1   ->SetLineStyle(2);
  //h1   ->SetLineStyle(7);

  h1   ->GetXaxis()->SetTickLength(0.04);
  h1   ->GetXaxis()->SetLabelSize(0.04);
  h1   ->GetXaxis()->SetTitleOffset(1.1);

  h1   ->GetYaxis()->SetTickLength(0.04);
  h1   ->GetYaxis()->SetLabelSize(0.04);
  h1   ->GetYaxis()->SetTitleOffset(1.8);
  h1   ->GetYaxis()->SetTitle("events");
  //h1->GetYaxis()->SetRangeUser(0,1.2*h1->GetMaximum());
  //h1->Draw("same");
}
void Set_exMC(TH1F *h1,const char *name,Color_t color)
{
  h1   ->GetXaxis()->SetTitle(name);
  h1   ->SetLineColor(color);
  h1   ->SetLineWidth(2);
  h1   ->SetLineStyle(2);
  //h1   ->SetLineStyle(7);

  h1   ->GetXaxis()->SetTickLength(0.04);
  h1   ->GetXaxis()->SetLabelSize(0.04);
  h1   ->GetXaxis()->SetTitleOffset(1.1);

  h1   ->GetYaxis()->SetTickLength(0.04);
  h1   ->GetYaxis()->SetLabelSize(0.04);
  h1   ->GetYaxis()->SetTitleOffset(1.8);
  h1   ->GetYaxis()->SetTitle("events");
  //h1->GetYaxis()->SetRangeUser(0,1.2*h1->GetMaximum());
  //h1->Draw("same");
}


        //归一到事例数 scale就是事例数比事例数  归一到面积scale就是面积比面积  归一到峰值scale就是峰值比峰值
void norm_Entries(TH1F *h1,TH1F *h2)//h1--data  
{
    double norm1 = h1          ->   GetEntries();    
    double intergral_2 =  h2   ->   GetEntries();
    double scale_2 = norm1/intergral_2  ;
    h2                         ->   Scale(scale_2);
}
void norm_Integral(TH1F *h1,TH1F *h2)//h1--data
{
    double norm1 = h1          ->   Integral();
    double intergral_2 =  h2   ->   Integral();
    double  scale_2 = norm1/intergral_2  ;
    h2                         ->   Scale(scale_2);
}
void norm_Maximum(TH1F *h1,TH1F *h2)//h1--data     
{
    double norm1 = h1          ->   GetMaximum();
    double intergral_2 =  h2   ->   GetMaximum();
    double  scale_2 = norm1/intergral_2  ;
    h2                         ->   Scale(scale_2);
}
void normalization(TH1F *h1,TH1F *h2,TH1F *h3,int i,int j)//h1--data  h2--inMC  h3--exMC    i,j 为1,2,3分别为归一到事例数,积分,峰值  归一到data的事例数
{
    if(i==1)norm_Entries(h1,h2); 
    if(i==2)norm_Integral(h1,h2); 
    if(i==3)norm_Maximum(h1,h2); 

    if(j==1)norm_Entries(h1,h3); 
    if(j==2)norm_Integral(h1,h3); 
    if(j==3)norm_Maximum(h1,h3); 
}


void Set_Legend(TLegend *leg ){
    leg ->SetBorderSize(0);
    leg ->SetTextSize(0.035);
    leg ->SetLineColor(10);
    leg ->SetFillColor(10);
}


void draw_all(TH1F *h1,TH1F *h2,TH1F *h3,TLegend *leg)//h1--data  h2--inMC  h3--exMC {
{
    double high1 = h1->GetMaximum();
    double high2 = h2->GetMaximum();
    double high3 = h3->GetMaximum();
    double high = 0;
    if(high1>high2 && high1>high3) high=high1;
    else if(high2 > high3) high=high2;
    else high = high3;

    h1->GetYaxis()->SetRangeUser(0,1.2*high);
    h1 -> Draw("e");
    h2 -> Draw("same");
    h3 -> Draw("same");
    h1 -> Draw("e,same");
    leg -> Draw();
}

void draw_DataInMC(TH1F *h1,TH1F *h2,TLegend *leg)//h1--data  h2--inMC  {
{
    double high1 = h1->GetMaximum();
    double high2 = h2->GetMaximum();
    double high = 0;
    if(high1>high2 ) high=high1;
    else high=high2;

    h1->GetYaxis()->SetRangeUser(0,1.2*high);
    h1 -> Draw("e");
    h2 -> Draw("same");
    h1 -> Draw("e,same");
    leg -> Draw();
}

#endif
