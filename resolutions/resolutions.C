#include "Riostream.h"
#include <iostream>
#include <fstream>
/* 
some code to help us understand why and how resolutions affect our ability to measure the
mass of a particle
*/

// main routine
void resolutions(){

// set up the display
gROOT->Reset();
gROOT->SetStyle("Plain");
gStyle->SetOptStat(0);
gStyle->SetOptFit(11);
gStyle->SetErrorX(0);
c1 = new TCanvas("c1","Our data",200,10,700,500);
c1->SetFillColor(0);
c1->SetBorderMode(0);
c1->SetBorderSize(1);
c1->SetFrameBorderMode(0);


// book some histograms
TH1F *histo1  = new TH1F("histo1","mass",100,50.,150.);

// setup random number generator
gRandom->SetSeed();


}

