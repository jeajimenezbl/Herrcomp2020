#include <iostream>
#include <cstdlib>
#include <eigen3/Eigen/Dense>
#include <chrono>

double Autovalue(int n);
 
int main(int argc, char *argv[])
{
  
   
  std::cout.precision(15);
  std::cout.setf(std::ios::scientific);
  int N = std::atoi(argv[1]); 
  int REPS = std::atoi(argv[2]);

  double t = 0;
  
  for (int irep = 0; irep < REPS; ++irep)
  {
    t += Autovalue(N);
  }
  std::cout << t/REPS << std::endl;

  return 0;
  
}

double Autovalue(int n)
{
  
   Eigen::MatrixXd A;
   A =Eigen::MatrixXd::Random(n, n);
   //std::cout << "Here is the matrix A:\n" << A <<std::endl;
   auto start = std::chrono::steady_clock::now();
   Eigen::SelfAdjointEigenSolver<Eigen::Matrix2d> eigensolver(A);
   if (eigensolver.info() != Eigen::Success) abort();
   eigensolver.eigenvalues();
   eigensolver.eigenvectors();
   auto end = std::chrono::steady_clock::now();
   //std::cout << "The eigenvalues of A are:\n" << eigensolver.eigenvalues() <<std::endl;
   //std::cout << "Here's a matrix whose columns are eigenvectors of A \n"
        // << "corresponding to these eigenvalues:\n"
        //<< eigensolver.eigenvectors() <<std::endl;
   double time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count()*1.0e-9;
   
   return time;

}
