#include<iostream>
#include<fstream>
#include<math.h>

using namespace std;



int main () {

  int jj=10;
  int* ii = &jj;
  cout<<ii<<" "<<jj<<" "<<(*ii)<<endl;

  return 0;
}


