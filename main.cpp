#include<iostream>
#include<math.h>

using namespace std;

  const int a = 7141;
  const int c = 54773;
  const int mmod=259200;


double mranflat(int& inew) {
  double mranflat=0.;
  inew = inew%mmod;
  double aa =double(inew)/double(mmod);
  mranflat=aa;
  inew= a*inew+c;
  return mranflat;
}


int main () {
  int inew=111111;
  int ihist[10] = {0,0,0,0,0,0,0,0,0,0};
  double aa;
  int ii=0;
  while(ii<1000) {
    aa=mranflat(inew);
    cout<<"random number is "<<aa<<" and seed is "<<inew<<endl<<endl;
    if(aa<0.1) {
      ihist[0]++;
    } else if ( (aa>=0.1) && (aa<0.2) ) {
      ihist[1]++;
    } else if ( (aa>=0.2) && (aa<0.3) ) {
      ihist[2]++;
    } else if ( (aa>=0.3) && (aa<0.4) ) {
      ihist[3]++;
    } else if ( (aa>=0.4) && (aa<0.5) ) {
      ihist[4]++;
    } else if ( (aa>=0.5) && (aa<0.6) ) {
      ihist[5]++;
    } else if ( (aa>=0.6) && (aa<0.7) ) {
      ihist[6]++;
    } else if ( (aa>=0.7) && (aa<0.8) ) {
      ihist[7]++;
    } else if ( (aa>=0.8) && (aa<0.9) ) {
      ihist[8]++;
    } else {
      ihist[9]++;
    }
    ii++;
  }

  ii=0;
  while(ii<10) {
    cout<<" ihist["<<ii<<"]="<<ihist[ii]<<" ";
    ii++;
  }
  cout<<endl;


  return 0;
}


