#include <iostream>
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <omp.h>

//Definimos las constantes
const double N=10e8; //Numero de intervalos
const double DX=10/N; //Longitud de cada intervalo

//----------Funciones----------------

double Funcion(double x);

void print_elapsed(auto start, auto end);

double Integral(double dx,int n, int nth);


//----------Funcion Principal ---------------

int main(int argc , char * argv[])
{
    std::cout.precision(7);
    std::cout.setf(std::ios::scientific);

    int NTH=std::atoi(argv[1]);
    
    auto start = std::chrono::steady_clock::now();
    std::cout<<Integral(DX,N,NTH)<<"\n";
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


double Integral(double dx,int n, int nth )
{
    double sum=0;

#pragma omp parallel for num_threads (nth) reduction (+:sum)  
    for(int kk=1;kk<= n ;++kk)
    {
        sum += Funcion(kk*dx) + Funcion(kk*dx - dx);
    }
    
    return 0.5*dx*sum;   
}
