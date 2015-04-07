#include "Riostream.h"


/* 
make a particle that decays to two daughter particles (narrow width approximation)
decay to two particles with p=m/2 (massless approximation) and isotropic  angular distribution (scalar)
boost using flat rapidity plateau approxmiation to get new energies 

assume calibration using gamma+jets.  make up calibration data
with errors linear in E.  fit.

smear particles energies using fit slope and intercept and errors.
reconstruct mass

store results in ntuple

*/

// function to calculate the z component of momentum from the mass
// and rapidity
Double_t Plong(float mass, float rapidity) {
  float Pl = 0.;
  float a=exp(2.*rapidity);
  float b=a+1.;
  float c=a-1;
  if(c!=0) {
    float d=sqrt(pow(b/c,2)-1);
    Pl= mass/d;
  }
  return Pl;
}


// main routine
void toyMC(){

// set up the display
gROOT->Reset();
gROOT->SetStyle("Plain");
gStyle->SetOptStat(0);
gStyle->SetOptFit(11);
gStyle->SetErrorX(0);
TLatex t;
t.SetTextAlign(22);
t.SetTextSize(0.05);
t.SetTextColor(1);
c1 = new TCanvas("c1","Example Particle Decay",200,10,700,500);
c1->SetFillColor(0);
c1->SetBorderMode(0);
c1->SetBorderSize(1);
c1->SetFrameBorderMode(0);

// open file to store output in ROOT storage format
 TFile *fOUT = new TFile("output.root","RECREATE");

//book ntuple
 float e1,px1,py1,pz1;
 float e2,px2,py2,pz2;
 float eb1,pxb1,pyb1,pzb1;
 float eb2,pxb2,pyb2,pzb2;
 float ebs1,pxbs1,pybs1,pzbs1;
 float ebs2,pxbs2,pybs2,pzbs2;

 TTree t1("t1","a tree");
 t1.Branch("e1",&e1,"e1/F");
 t1.Branch("px1",&px1,"px1/F");
 t1.Branch("py1",&py1,"py1/F");
 t1.Branch("pz1",&pz1,"pz1/F");
 t1.Branch("e2",&e1,"e2/F");
 t1.Branch("px2",&px1,"px2/F");
 t1.Branch("py2",&py1,"py2/F");
 t1.Branch("pz2",&pz1,"pz2/F");
 t1.Branch("eb1",&e1,"eb1/F");
 t1.Branch("pxb1",&px1,"pxb1/F");
 t1.Branch("pyb1",&py1,"pyb1/F");
 t1.Branch("pzb1",&pz1,"pzb1/F");
 t1.Branch("eb2",&e1,"eb2/F");
 t1.Branch("pxb2",&px1,"pxb2/F");
 t1.Branch("pyb2",&py1,"pyb2/F");
 t1.Branch("pzb2",&pz1,"pzb2/F");
 t1.Branch("ebs1",&e1,"ebs1/F");
 t1.Branch("pxbs1",&px1,"pxbs1/F");
 t1.Branch("pybs1",&py1,"pybs1/F");
 t1.Branch("pzbs1",&pz1,"pzbs1/F");
 t1.Branch("ebs2",&e1,"ebs2/F");
 t1.Branch("pxbs2",&px1,"pxbs2/F");
 t1.Branch("pybs2",&py1,"pybs2/F");
 t1.Branch("pzbs2",&pz1,"pzbs2/F");


 // TNtuple *ntuple = new TNtuple("ntuple","data from toy MC","e1:px1:py1:pz1:e2:px2:py2:pz2:eb1:pxb1:pyb1:pzb1:eb2:pxb2:pyb2:pzb2:ebs1:pxbs1:pybs1:pzbs1:ebs2:pxbs2:pybs2:ebs1");

// book some histograms
TH1F *histo1  = new TH1F("histo1","rapidity",20,-5.,5.);
TH1F *histo2  = new TH1F("histo2","Pl",40,-1000.,1000.);
TH1F *histo3  = new TH1F("histo3","theta",400,0.,4.);
TH1F *histo4  = new TH1F("histo4","beta",40,0.,1.);
TH1F *histo5  = new TH1F("histo5","mass test",400,100.,300.);
TH1F *histo6  = new TH1F("histo6","boosted jet energy",400,0.,1000.);
TH1F *histo7  = new TH1F("histo7","smeared mass",400,100.,300.);


// setup random number generator
gRandom->SetSeed();

// set the properties of the mother particle
  float m=200; // GeV
  float raprange = 2.; // size of rapidity plateau

// setup the resolution of the calorimeter
  float sampling = 0.8;  // sampling term
  float noise = 0.1;  // noise term
  float constant = 0.01; // constant term

// make a series of bosons
   for (int i=0;i<10000;i++) {   // number of particles made
// get theta of boson decay product in boson rest frame
     float costheta = gRandom->Rndm();
     float theta1 = acos(costheta);
     if(gRandom->Rndm()<0.5) theta1=TMath::Pi()-theta1;
     float theta2 = TMath::Pi()-theta1;
     histo3->Fill(theta1);
// get phi of boson decay
     float phi1 = 2.*TMath::Pi()*gRandom->Rndm();
     float phi2 = phi1+TMath::Pi();
// calculate momenta of decay products in boson rest frame
     e1=m/2.;
     float p1 = e1; // massless
     px1 = p1*sin(theta1)*cos(phi1);
     py1 = p1*sin(theta1)*sin(phi1);
     pz1 = p1*cos(theta1);
     e2=m/2.;
     float p2 = e2; // massless
     px2 = p2*sin(theta2)*cos(phi2);
     py2 = p2*sin(theta2)*sin(phi2);
     pz2 = p2*cos(theta2);
// get rapidity of boson
     float rapidity = -1.*raprange + gRandom->Rndm() * 2. * raprange;
     histo1->Fill(rapidity);
// calculate pZ of boson
     Double_t pl=Plong(m,rapidity);
     if(gRandom->Rndm()<=0.5) pl=-1.*pl;
     histo2->Fill(pl);
// calculate beta of boson
     float e=sqrt(pow(m,2.)+pow(pl,2.));
     float beta = pl/e;
     float gamma = 1./sqrt(1.-pow(beta,2.));
     histo4->Fill(beta);
// calculate boosted momentum of decay products
     eb1 = gamma*e1-beta*gamma*pz1;
     pxb1 = px1;
     pyb1 = py1;
     pzb1 = -gamma*beta*e1+gamma*pz1;
     float thetab1 = acos(pzb1/eb1);
     eb2 = gamma*e2-beta*gamma*pz2;
     pxb2 = px2;
     pyb2 = py2;
     pzb2 = -gamma*beta*e2+gamma*pz2;
     float thetab2 = acos(pzb2/eb2);
     histo6->Fill(eb1);
     histo6->Fill(eb2);
// check mass
     float ee=eb1+eb2;
     float pxx = pxb1+pxb2;
     float pyy = pyb1+pyb2;
     float pzz = pzb1+pzb2;
     float mm = sqrt(pow(ee,2.)-pow(pxx,2.)-pow(pyy,2.)-pow(pzz,2.));
     histo5->Fill(mm);


// simulate detector response

// get smeared momentum
     float res1=eb1*sqrt(pow(sampling/sqrt(eb1),2)+pow(constant,2)+pow(noise/eb1,2));
     ebs1 = eb1+res1*gRandom->Gaus(0.,1.);
     pxbs1 = ebs1 * sin(thetab1) * cos(phi1);
     pybs1 = ebs1 * sin(thetab1) * sin(phi1);
     pzbs1 = ebs1 * cos(thetab1);
     float res2=eb2*sqrt(pow(sampling/sqrt(eb2),2)+pow(constant,2)+pow(noise/eb2,2));
     ebs2 = eb2+res2*gRandom->Gaus(0.,1.);
     pxbs2 = ebs2 * sin(thetab2) * cos(phi2);
     pybs2 = ebs2 * sin(thetab2) * sin(phi2);
     pzbs2 = ebs2 * cos(thetab2);
// get smeared mass
     float ees=ebs1+ebs2;
     float pxxs = pxbs1+pxbs2;
     float pyys = pybs1+pybs2;
     float pzzs = pzbs1+pzbs2;
     float mms = sqrt(pow(ees,2.)-pow(pxxs,2.)-pow(pyys,2.)-pow(pzzs,2.));
     histo7->Fill(mms);
//********************************************************************
     // fill ntuple

     //     ntuple->Fill(e1,px1,py1,pz1,e2,px2,py2,pz2,eb1,pxb1,pyb1,pzb1,eb2,pxb2,pyb2,pzb2,ebs1,pxbs1,pybs1,pzbs1,ebs2,pxbs2,pybs2,pzbs2);
     t1.Fill();
     //     ntuple->Fill(e1,px1,py1,pz1,e2,px2,py2,pz2,eb1,pxb1,pyb1,pzb1,eb2,pxb2,pyb2,ebs1);

   }

// look at one of the histograms right now, fit it to a gaussian, and display it
histo7->Fit("gaus","","",190.,210.);
histo7->SetLineColor(2);
histo7->Draw("");
c1->Update();
c1->SaveAs("c1.gif");

//output data to a file
 fOUT->Write();
}

