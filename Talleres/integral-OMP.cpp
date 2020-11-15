#include <iostream>
#include <cmath>
#include <cstdlib>
#include <chrono>

const double N=10e8;
const double DX=10/N;

double Funcion(double x);

void print_elapsed(auto start, auto end);

double Integral(double dx);

int main(int argv , char * argc[])
{
    std::cout.precision(7);
    std::cout.setf(std::ios::scientific);
    
    auto start = std::chrono::steady_clock::now();
    std::cout<<Integral(DX)<<"\n";
    auto end = std::chrono::steady_clock::now();
    print_elapsed(start,end);
    return 0;
}

double Funcion(double x)
{
    return x*x;
}

void print_elapsed(auto start , auto end)
{
    std::cout<<"Elapsed time in seconds: "
             <<std::chrono::duration_cast <std::chrono::milliseconds>
              (end-start).count()/1000.0<<"\n";
}

double Integral(double dx )
{
    double sum=0;
    for(int k=1;k<=N;k++)
    {
        sum += Funcion(k*dx) + Funcion(k*dx - dx);
    }
    

    return 0.5*dx*sum;   
    
}
