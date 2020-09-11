#include<iostream>
#include<cstdlib>

int main(int argc, char *argv[])
{
  std::cout.precision(15);
  std::cout.setf(std::ios::scientific);
  int n,i;
  double eps,one;
  n=atoi(argv[1]);
  eps=1.0;
  for(i=0;i<=n;i++){
    eps=eps/2;
    one = 1.0 + eps;
    
    std::cout<<i<<"\t"<<one<<"\t"<<"\t"<<eps<<std::endl;

  }
  
  return 0;


}
