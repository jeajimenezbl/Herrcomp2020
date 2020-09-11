#include <iostream>
#include <cstdlib>
#include<cmath>

typedef float REAL;
using namespace std;

REAL Exp(int Nmax, REAL x)
{
  int i;
  REAL suma,a0,a1;
  a0=1;
  a1=-x;
  suma=a0+a1;
  
  for(i=1;i<Nmax-1;i++)
    {
      a0=a1;
      a1=(-x/(i+1))*a0;
      suma=suma + a1;
    }
  return suma;

}




int main( int argc, char *argv[])
{
  cout.precision(7);
  cout.setf(ios::scientific);
  int Nmax,n;
  Nmax=atoi(argv[1]);
  n= atoi(argv[2]);
  for(REAL x=0;x<=n;x+=0.1)
    {
      cout<<x<<"\t"<<Exp(Nmax,x)<<endl;
    }
  return 0;
  

}
