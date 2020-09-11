#include <iostream>
#include <cmath>

typedef float REAL;
using namespace std;


REAL Sumup(int Nmax)
{
  REAL suma=0.0;
  for(int i=1;i<=Nmax;i++)
    {
      suma+=1.0/i;
    }
  return suma;
}

REAL Sumdown(int Nmax)
{
  REAL suma=0.0;
  for(int i=Nmax;i>=1;i--)
    {
      suma+=1.0/i;
    }
  return suma;

}

int main()
{
  for(int nmax=1;nmax<=100;nmax++)
    {
      cout<<nmax<<"\t"<<fabs(1-Sumdown(nmax)/Sumup(nmax))<<endl;
    }
  
  return 0;

}
