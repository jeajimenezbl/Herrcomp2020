#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

float Raiz1(float x)
{
  return 5-sqrt(10*x+pow((5-x),2));
}

float Raiz2(float x)
{
  return -pow(x,2)/(5+sqrt(25+pow(x,2)));
}

float Raiz3(float x)
{
  return -pow(x,2)/(5+sqrt(10*x + pow((5-x),2)));
}
  
int main(int argc, char *argv[])
{
  cout.precision(7);
  cout.setf(ios::scientific);
  float x,x2;

  for (x=0;x<=1;x+=0.01)
    {
      x2=x*x;      
      cout<<x<<"\t"<<5-sqrt(25+x2)<<"\t"<<Raiz1(x)<<"\t"<<Raiz2(x)<<"\t"<<Raiz3(x)<<endl;

    }
  return 0;
  


}
