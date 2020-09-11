#include <iostream>
#include <cmath>
#include <cstdlib>

typedef float REAL;
using namespace std;

REAL Suma1(int N)
{
  REAL suma;
  suma=0;
  for(int n=1;n<=N;n++)
    {
      suma=suma + 1.0/(2*n*(2*n+1));
    }
  return suma;
}

REAL Suma2(int N)
{
  REAL sum1,sum2;
  sum1=0;
  sum2=0;
  for(int n =1; n<=N;n++)
    {
      sum1+=2.0*n/(2.0*n+1);
      sum2+=(2.0*n-1)/(2.0*n);
    }
  return sum1-sum2;
}

REAL Suma3(int N)
{
  int a;
  REAL suma;
  suma=0;
  a=-1;
  for(int n=1;n<=2*N;n++)
    {
      suma+=a*(n/(n+1.0));
      a*=-1;
    }
  return suma;

}
int main(int argc, char *argv[])
{
  cout.precision(6);
  cout.setf(ios::scientific);

  int N;
  N=atoi(argv[1]);
  
  for(int i=1;i<=N;i+=5)
    {
      cout<<i<<"\t"<<abs(Suma3(i)-Suma2(i))/Suma3(i)<<"\t"<<abs(Suma3(i)-Suma1(i))/Suma3(i)<<endl;
    }
  return 0;

}
