# include <cmath>
# include <cstdlib>
# include <iostream>

double myatan(double x, int n)
{
    double a,b,c,d,E,f;
    E=pow(2.0,-n);
    a=pow(2.0,-n/2.0);
    b=x/(1+sqrt(1+x*x));
    c=1;
    d=1;

    while (E < 1-a)
    {
        c=2.0*c/(1.0+a);
        
        d=2.0*a*b/(1+b*b);        
        d=d/(1+sqrt(1-d*d));
        d=(b+d)/(1-b*d);        
               
        b=d/(1+sqrt(1+d*d));        
        a=2.0*sqrt(a)/(1+a);

        f= c*log((1+b)/(1-b));
    }
    return f;
}

int main(int argc, char **argv)
{
std::cout.precision(15); std::cout.setf(std::ios::scientific);

const int NSTEPS = std::atoi(argv[1]);// 53
const double x = std::atof(argv[2]); // 4.2
const double exact = std::atan(x);

double my = myatan(x, NSTEPS);
double diff = std::fabs(my-exact)/exact;
std::cout << diff << std::endl;
return 0;
}
