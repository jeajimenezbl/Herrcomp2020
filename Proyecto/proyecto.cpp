// Simular el movimiento de N moleculas en un cuadrado 2D
#include <iostream>
#include <cmath>
#include "Vector.h"
#include <random>
using namespace std;

//---- declarar constantes ---
const double K=1.0e4;
const double Lx=100, Ly=100; //dimensiones de caja
const int Nx=200, Ny=200, N=Nx*Ny; //número de moleculas en x y y.

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
  void Inicie(double x0,double y0,double Vx0,double Vy0,double m0,double R0);
  void BorreFuerza(){F.cargue(0,0,0);};
  void AdicioneFuerza(vector3D F0){F+=F0;};
  void Mueva_r(double dt, double Coeficiente);
  void Mueva_V(double dt, double Coeficiente);
  void Dibujese(void);
  double Getx(void){return r.x();}; //inline
  double Gety(void){return r.y();}; //inline
  double Getv(void){return norma(V);}; //inline
  friend class Colisionador;
};
void Cuerpo::Inicie(double x0,double y0,double Vx0,double Vy0,double m0,double R0){
  r.cargue(x0,y0,0); V.cargue(Vx0,Vy0,0);  m=m0;  R=R0; 
} 
void Cuerpo::Mueva_r(double dt, double Coeficiente){
  r+=V*(Coeficiente*dt);
}
void Cuerpo::Mueva_V(double dt, double Coeficiente){
  V+=F*(Coeficiente*dt/m);
}
void Cuerpo::Dibujese(void){
  cout<<" , "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t)";
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
  for(i=0;i<N+4;i++)
    Molecula[i].BorreFuerza();
  //--- Calcular Fuerzas entre pares de Moleculas ---
  for(i=0;i<N;i++)
    for(j=i+1;j<N+4;j++)
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
  cout<<"set size ratio -1"<<endl;
  cout<<"set parametric"<<endl;
  cout<<"set trange [0:7]"<<endl;
  cout<<"set isosamples 12"<<endl;  
}
void InicieCuadro(void){
    cout<<"plot 0,0 ";
    cout<<" , "<<Lx/7<<"*t,0";        //pared de abajo
    cout<<" , "<<Lx/7<<"*t,"<<Ly;     //pared de arriba
    cout<<" , 0,"<<Ly/7<<"*t";        //pared de la izquierda
    cout<<" , "<<Lx<<","<<Ly/7<<"*t"; //pared de la derecha
}
void TermineCuadro(void){
    cout<<endl;
}

//-----------  Programa Principal --------------  
int main(void){
  double m0=1, R0=2, kT=10, V0=sqrt(2*kT/m0);
  int i;
  Cuerpo Molecula[N+4];
  Colisionador Hertz;

  mt19937 gen (0);
  uniform_real_distribution <double> dist (0,1);
  normal_distribution <double> boltz (-kT/m0, kT/m0);
  double vx, vy, vz, v;
  
  int ix,iy;
  double t,tdibujo,tmax=12*(Lx/V0),tcuadro=tmax/1000,dt=1e-3;
  double dx=Lx/(Nx+1), dy=Ly/(Ny+1);//posiciones iniciales de las moleculas
  double Theta;
  
  //InicieAnimacion(); //Dibujar

  //Inicializar las paredes
  double Rpared=100*Lx, Mpared=10000*m0;
  //------------------(  x0,       y0,Vx0,Vy0,    m0,    R0) 
  Molecula[N+0].Inicie(Lx/2,Ly+Rpared,  0,  0,Mpared,Rpared); //Pared de arriba
  Molecula[N+1].Inicie(Lx/2,  -Rpared,  0,  0,Mpared,Rpared); //Pared de abajo
  Molecula[N+2].Inicie(Lx+Rpared,Ly/2,  0,  0,Mpared,Rpared); //Pared derecha
  Molecula[N+3].Inicie(  -Rpared,Ly/2,  0,  0,Mpared,Rpared); //Pared izquierda
  //Inicializar las moléculas
  for(ix=0;ix<Nx;ix++)
    for(iy=0;iy<Ny;iy++){
      //Theta=2*M_PI*dist(gen);

      vx= boltz (gen);
      vy= boltz (gen);
      vz= boltz (gen);
      v = sqrt (vx*vx + vy*vy + vz*vz); //boltz dist
      
      //-----------------------(   x0,   y0,          Vx0,          Vy0, m0,R0)
      //Molecula[Nx*iy+ix].Inicie((ix+1)*dx,(iy+1)*dy,v*cos(Theta),v*sin(Theta), m0,R0);//OJO
      Molecula[Nx*iy+ix].Inicie((ix+1)*dx,(iy+1)*dy, vx, vy, m0,R0);//OJO
    }
  
  for (int ii=0; ii < N ; ++ii) {	
    //cout << ii << "\t"<< Molecula[ii].Getv() << "\n" ;
    cout << Molecula[ii].Getv() << "\n" ;
    } 

  /*

  //EVOLUCION DEL SISTEMA
  //for(t=0,tdibujo=0 ; t<tmax ; t+=dt,tdibujo+=dt){
  for(t=0,tdibujo=0 ; t< 1000000 ; t+=100 ,tdibujo+=dt){

    
    //Dibujar
    if(tdibujo>tcuadro){
      
      InicieCuadro();
      for(i=0;i<N;i++) Molecula[i].Dibujese();
      TermineCuadro();
      
      tdibujo=0;
    }

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

  */
  
  return 0;
}
