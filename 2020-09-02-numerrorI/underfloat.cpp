#include<iostream>
#include<cstdlib>

int main(int argc, char *argv[]){

  std::cout.precision(15);
  std::cout.setf(std::ios::scientific);
  
  int i, N;
  double under, over;

  
  under=1.0;
  over=1.0;
  N=atoi(argv[1]);

  for(i=0;i<=N; i++){
    under/=2;
    over*=2;
    std::cout<<i<<"\t"<<under<<"\t"<<over<<"\n";

  }

  return 0;


}
