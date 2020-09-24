# include <iostream>
# include <cmath>
# include <cstdlib>

double sumup(int N)
{
    double an,an1,fN;
    an1=1.0;
    fN=0;
    
    for(int n=1; n<=N;n++)
    {
        an=an1;
        an1=an/(1.0+(2.0/n)+an);
        fN+=an;             
    }
    return fN;
}
double sumdown(int N)
{
    double an,an1,gN;
    an1=1.0/(N*N);
    gN=0;
    
    for(int n=N;n>=1;n--)
    {
        an=an1;
        an1=an/(1.0-(2.0/n)+an);
        gN+=an;
    }
    return gN;
}


int main(int argc, char **argv)
{
std::cout.precision(15); std::cout.setf(std::ios::scientific);
const double exact = M_PI*M_PI/6.0;
const int NMAX = std::atoi(argv[1]);
double df = std::fabs(sumup(NMAX) - exact)/exact;
double dg = std::fabs(sumdown(NMAX) - exact)/exact;
std::cout << df << "\t" << dg << std::endl;
return 0;
}
