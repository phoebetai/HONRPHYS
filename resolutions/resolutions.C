#include "Riostream.h"
#include <iostream>
#include <fstream>
/* 
some code to help us understand why and how resolutions affect our ability to measure the
mass of a particle
*/

// main routine
void resolutions(){

  // set debug mode
  bool idebug=0;

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
TH1F *histo1  = new TH1F("histo1","mass",1000,0.,200.);

// setup random number generator
gRandom->SetSeed();


// get the secret parameters
 ifstream myfile;
 myfile.open("secretparameters.txt");
 double mass, resE, resA;
 myfile>>mass>>resE>>resA;
 myfile.close();

 // make N bosons at rest
 // each boson will decay to 2 back-to-back daughter particles
 // they will be back-to-back by conservation of momentum, since the momentum of the mother was zero
 // assume that the mass of the daughter particles is small compared to the mother mass so we can
 // assume that their energy will be large compared to their mass and we can treat them as massless.
 // and thus their energy is equal to the magnitude of their momenta
 // by conservations of energy, their energy
 // work in 2D.  Can always choose my coordinate system so that the 2 daughters are in the same plane
 int N=1000;
   double etrue1,etrue2,phitrue1,phitrue2;  // true energy of the 2 daughters
 double e1,px1,py1,phi1;  // smeared 4-momenta of daughter 1
 double e2,px2,py2,phi2;  // smeared 4-momenta of daughter 2
 double masssmeared;
 for(int i=0;i<N;i++) {
   // set true energy
   etrue1=mass/2.;
   etrue2=mass/2.;
   if(idebug) cout<<"etrue "<<etrue1<<" "<<etrue2<<endl;
   // choose phi for daughter 1 and daughter 2
   phitrue1=2*TMath::Pi()*gRandom->Rndm();
   phitrue2 = phitrue1+TMath::Pi();
   if(idebug) cout<<"phitrue "<<phitrue1<<" "<<phitrue2<<endl;
     // smear true energy with resolution of detector
     e1=etrue1+resE*gRandom->Gaus(0.,1.);
     e2=etrue2+resE*gRandom->Gaus(0.,1.);
     if(idebug) cout<<"e "<<e1<<" "<<e2<<endl;
     //smear angles with resolution of the detector
     phi1=phitrue1+resA*gRandom->Gaus(0.,1.);
     phi2=phitrue2+resA*gRandom->Gaus(0.,1.);
     if(idebug) cout<<"phi "<<phi1<<" "<<phi2<<endl;
     //calculate 4 momenta after smearing
     px1=e1*cos(phi1);
     py1=e1*sin(phi1);
     px2=e2*cos(phi2);
     py2=e2*sin(phi2);
     if(idebug) cout<<"pxs "<<px1<<" "<<py1<<" "<<px2<<" "<<py2<<endl;
     // calculate smeared mass
     masssmeared=sqrt((e1+e2)*(e1+e2) - (px1+px2)*(px1+px2) - (py1+py2)*(py1+py2));
     if(idebug) cout<<"masssmeared "<<masssmeared<<endl;
     histo1->Fill(masssmeared);

 }

 histo1->Draw("");
 c1->Update();
 c1->SaveAs("c1.gif");

}

