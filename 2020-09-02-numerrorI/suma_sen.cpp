#include <iostream>
#include <cstdlib>
#include<cmath>

typedef double REAL;
using namespace std;

REAL Seno(int Nmax, REAL x)
{
  int i;
  REAL suma,a0,a1;
  a0=x;
  a1=pow(-x,3)/6;
  suma=a0+a1;
  
  for(i=1;i<Nmax-1;i++)
    {
      a0=a1;
      a1=(-pow(x,2)/((2*i + 3)*(2*i + 2)))*a0;
      suma=suma + a1;
    }
  return suma;

}

int main( int argc, char *argv[])
{
  cout.precision(15);
  cout.setf(ios::scientific);
  int Nmax,n;
  Nmax=atoi(argv[1]); //numero de terminos de la serie
  n= atoi(argv[2]); //numero de terminos de x
  //cout<<"*\t x \t "<<"\t valor teorico \t"<<"\t valor estimado \t"<< "\t error \t"<<endl;
  for(REAL x=0;x<=n;x+=0.1)
    {
      cout<<x<<"\t"<<sin(x)<<"\t"<<Seno(Nmax,x)<<"\t"<<(sin(x)-Seno(Nmax,x))/sin(x)<<endl;
    }
  return 0;
  

}
