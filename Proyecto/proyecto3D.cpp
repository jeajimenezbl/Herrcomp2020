#include <iostream>
#include <cmath>
#include "Vector.h"
#include <random>
using namespace std;
//---- declarar constantes ---
const double K=1.0e4;
const double Lx=100, Ly=100, Lz=100; //dimensiones de caja
const int Nx=2, Ny=2, Nz=2, N=Nx*Ny*Nz; //número de moleculas en x y y.

const double epsilon=0.1786178958448091e00;
const double lambda=-0.2123418310626054e00;
const double chi=-0.6626458266981849e-1;
const double lambda2=(1.0-2.0*lambda)/2.0;
const double chiepsilon=1.0-2.0*(chi+epsilon);
//--- declarar clases -----
class Cuerpo;
class Colisionador;
//---- interface e implementacion de clases ----
//---- clase cuerpo ---
class Cuerpo{
private:
  vector3D r,V,F; double m,R;
public:
  void Inicie(double x0,double y0,double z0,double Vx0,double Vy0,double Vz0,double m0,double R0);
  void BorreFuerza(){F.cargue(0,0,0);};
  void AdicioneFuerza(vector3D F0){F+=F0;};
  void Mueva_r(double dt, double Coeficiente);
  void Mueva_V(double dt, double Coeficiente);
  void Dibujese(void);
  double Getx(void){return r.x();}; //inline
  double Gety(void){return r.y();}; //inline
  double Getz(void){return r.z();}; //inline  
  double Getv(void){return norma(V);}; //inline
  friend class Colisionador;
};
void Cuerpo::Inicie(double x0,double y0,double z0,double Vx0,double Vy0,double Vz0,double m0,double R0){
  r.cargue(x0,y0,z0); V.cargue(Vx0,Vy0,Vz0);  m=m0;  R=R0; 
} 
void Cuerpo::Mueva_r(double dt, double Coeficiente){
  r+=V*(Coeficiente*dt);
}
void Cuerpo::Mueva_V(double dt, double Coeficiente){
  V+=F*(Coeficiente*dt/m);
}
void Cuerpo::Dibujese(void){
  cout<<" , "<<r.x()<<"+"<<R<<"*cos(v)*cos(u),"<<r.y()<<"+"<<R<<"*cos(v)*sin(u),"<<r.z()<<"+"<<R<<"*sin(v)";
}
//--- clase Colisionador ----
class Colisionador{
private:
public:
  void CalculeFuerzas(Cuerpo * Molecula);
  void CalculeFuerzaEntre(Cuerpo & Molecula1, Cuerpo & Molecula2);
};
void Colisionador::CalculeFuerzas(Cuerpo * Molecula){
  int i,j;
  //--- Borrar todas las fuerzas ---
  for(i=0;i<N+6;i++)
    Molecula[i].BorreFuerza();
  //--- Calcular Fuerzas entre pares de Moleculas ---
  for(i=0;i<N;i++)
    for(j=i+1;j<N+6;j++)
      CalculeFuerzaEntre(Molecula[i], Molecula[j]);
}
void Colisionador::CalculeFuerzaEntre(Cuerpo & Molecula1, Cuerpo & Molecula2){
  vector3D r21=Molecula2.r-Molecula1.r;
  double d=norma(r21), s=Molecula1.R+Molecula2.R-d;
  if(s>0){
    vector3D n=r21*(1.0/d);
    vector3D F2=n*(K*pow(s,1.5)); //Ley de Hertz para la colisión
    Molecula2.AdicioneFuerza(F2);   Molecula1.AdicioneFuerza(F2*(-1));
  }   
}
//----------------- Funciones de Animacion ----------
void InicieAnimacion(void){
  cout<<"set terminal gif animate"<<endl; 
  cout<<"set output 'Gas2D.gif'"<<endl;
  cout<<"unset key"<<endl;
  cout<<"set xrange[-10:"<<Lx+10<<"]"<<endl;
  cout<<"set yrange[-10:"<<Ly+10<<"]"<<endl;
  cout<<"set zrange[-10:"<<Lz+10<<"]"<<endl;
  cout<<"set size ratio -1"<<endl;
  cout<<"set parametric"<<endl;
  cout<<"set urange [0:2*pi]"<<endl;
  cout<<"set vrange [-pi/2:pi/2]"<<endl;
  cout<<"set isosamples 30"<<endl;  
}

void InicieCuadro(void){
  cout<<"splot 0,0,0 ";
  cout<<" , "<<Lx<<"/(2*pi)*u,0,0";  
  cout<<" , "<<Lx<<"/(2*pi)*u,"<<Ly<<",0";
  cout<<" , "<<Lx<<"/(2*pi)*u,0,"<<Lz;
  cout<<" , "<<Lx<<"/(2*pi)*u,"<<Ly<<","<<Lz;
  cout<<" , 0,"<<Ly<<"/(2*pi)*u,0";
  cout<<" , "<<Lx<<","<<Ly<<"/(2*pi)*u,0";
  cout<<" , 0,"<<Ly<<"/(2*pi)*u,"<<Lz;
  cout<<" , "<<Lx<<","<<Ly<<"/(2*pi)*u,"<<Lz;	
  cout<<" , 0,0,"<<Lz<<"/(2*pi)*u";	
  cout<<" , "<<Lx<<",0,"<<Lz<<"/(2*pi)*u";
  cout<<" , 0,"<<Ly<<","<<Lz<<"/(2*pi)*u";
  cout<<" , "<<Lx<<","<<Ly<<","<<Lz<<"/(2*pi)*u";
}

void TermineCuadro(void){
    cout<<endl;
}

void Paredes(double masa, Cuerpo * Molecula){
  double Rpared=1000*Lx, Mpared=9e9*masa;

  //------------------(       x0,       y0,       z0,Vx0,Vy0,Vz0,    m0,    R0) 
  Molecula[N+0].Inicie(     Lx/2,Ly+Rpared,     Lz/2,  0,  0,  0,Mpared,Rpared); //Pared de arriba
  Molecula[N+1].Inicie(     Lx/2,  -Rpared,     Lz/2,  0,  0,  0,Mpared,Rpared); //Pared de abajo
  Molecula[N+2].Inicie(Lx+Rpared,     Ly/2,     Lz/2,  0,  0,  0,Mpared,Rpared); //Pared derecha
  Molecula[N+3].Inicie(  -Rpared,     Ly/2,     Lz/2,  0,  0,  0,Mpared,Rpared); //Pared izquierda
  Molecula[N+4].Inicie(     Lx/2,     Ly/2,Lz+Rpared,  0,  0,  0,Mpared,Rpared); //Pared del frente
  Molecula[N+5].Inicie(     Lx/2,     Ly/2,  -Rpared,  0,  0,  0,Mpared,Rpared); //Pared del fondo
}

void InicializarMoleculas(double kT, double m0, double R0, Cuerpo * Molecula){
  mt19937 gen (0);
  normal_distribution <double> normal (kT/m0, kT/m0);
  double vx=0, vy=0, vz=0, v=0;
  double dx=Lx/(Nx+1), dy=Ly/(Ny+1), dz=Lz/(Nz+1);

  for(int ix=0;ix<Nx;ix++){
    for(int iy=0;iy<Ny;iy++){
      for(int iz=0;iz<Nz;iz++){
        vx= normal (gen);
        vy= normal (gen);
        vz= normal (gen);
        v = sqrt (vx*vx + vy*vy + vz*vz); //boltzmann dist
      
        //--------------------------------(       x0,       y0,       z0,Vx0,Vy0,Vz0, m0,R0)
        Molecula[Nx*Nx*ix+Ny*iy+iz].Inicie((ix+1)*dx,(iy+1)*dy,(iz+1)*dz, vx, vy, vz, m0,R0);
      }
    }
  }
}


//-----------  Programa Principal --------------  
int main(void){
  double m0=1, R0=2, kT=1, V0=sqrt(2*kT/m0);
  int i;
  Cuerpo Molecula[N+6];
  Colisionador Hertz;
  
  double t=0 ,tdibujo=0,tmax=12*(Lx/V0),tcuadro=tmax/1000,dt=1e-3;
  
  //InicieAnimacion(); //Dibujar
  Paredes (m0, Molecula);   //Inicializar las paredes
  InicializarMoleculas(kT, m0, R0, Molecula);   //Ini moleculas
  
  
  for (int ii=0; ii < N ; ++ii) {	
    cout << Molecula[ii].Getv() << "\n" ;  //histograma
    } 
  
  
  //EVOLUCION DEL SISTEMA
  //for(t=0,tdibujo=0 ; t<tmax ; t+=dt,tdibujo+=dt){
  for(t=0,tdibujo=0 ; t<100 ; t+=dt ,tdibujo+=dt){

    /*
    //Dibujar
    if(tdibujo>tcuadro){
      
      InicieCuadro();
      for(i=0;i<N;i++) Molecula[i].Dibujese();
      TermineCuadro();
      
      tdibujo=0;
      } */
    
    //--- Muevase por Omelyan (PEFRL) ---
    for(i=0;i<N;i++)Molecula[i].Mueva_r(dt,epsilon);
    Hertz.CalculeFuerzas(Molecula);
    for(i=0;i<N;i++)Molecula[i].Mueva_V(dt,lambda2);
    for(i=0;i<N;i++)Molecula[i].Mueva_r(dt,chi);
    Hertz.CalculeFuerzas(Molecula);
    for(i=0;i<N;i++)Molecula[i].Mueva_V(dt,lambda);
    for(i=0;i<N;i++)Molecula[i].Mueva_r(dt,chiepsilon);
    Hertz.CalculeFuerzas(Molecula);
    for(i=0;i<N;i++)Molecula[i].Mueva_V(dt,lambda);
    for(i=0;i<N;i++)Molecula[i].Mueva_r(dt,chi);
    Hertz.CalculeFuerzas(Molecula);
    for(i=0;i<N;i++)Molecula[i].Mueva_V(dt,lambda2);
    for(i=0;i<N;i++)Molecula[i].Mueva_r(dt,epsilon);

  }   
  
  
  return 0;
}
