#include "md-simul.h"

#include "md-simul.h"

void initial_conditions(Particle & body)
{
  body.Rx = 1.0;
  body.Ry = 1.0;
  body.Rz = 1.0;
  body.Vx = 1.0;
  body.Vy = 5.0;
  body.Vz = 1.0;

  body.rad = 0.25;
  body.mass = 0.3;
}

void compute_force(Particle & body)
{
  // reset force
  body.Fx = body.Fy = body.Fz = 0.0;
  body.U = 0.0;

  // gravitational force
  body.Fy += body.mass*G;
  body.U += -body.mass*G*body.Ry;

  // force with ground
  double delta = body.rad - body.Ry;
  if (delta > 0) {
    body.Fy += K*delta;
    body.U += -0.5*K*delta*delta;
   // body.Fy -= 0.2*body.Vy;
  }

  // force with up wall
  double LY = 2.01;
  delta = body.Ry + body.rad - LY;
  if (delta > 0) {
    body.Fy -= K*delta;
    body.U += 0.5*K*delta*delta;
   // body.Fy -= 0.2*body.Vy;
  }
     
  // force with right wall
  double LX = 2.01;
  delta = body.Rx + body.rad - LX;
  if (delta > 0) {
    body.Fx -= K*delta;
    body.U += 0.5*K*delta*delta;
    //body.Fx -= 0.2*body.Vx;
  }
  
  // force with left wall
  
  delta = body.Rx - body.rad ;
  if (delta < 0) {
    body.Fx -= K*delta;
    body.U += 0.5*K*delta*delta;
    //body.Fx -= 0.2*body.Vx;
  }
   
  // force with front wall
  double LZ = 2.01;
  delta = body.Rz + body.rad - LZ;
  if (delta > 0) {
    body.Fz -= K*delta;
    body.U += 0.5*K*delta*delta;
    //body.Fz -= 0.2*body.Vz;
  }
  
  // force with back wall
  
  delta = body.Rz - body.rad ;
  if (delta < 0) {
    body.Fz -= K*delta;    
    body.U += 0.5*K*delta*delta;
   // body.Fz -= 0.2*body.Vz;
  }
  

}

void start_integration(Particle & body, const double & dt)
{
  body.Vx -= body.Fx*dt/(2*body.mass);
  body.Vy -= body.Fy*dt/(2*body.mass);
  body.Vz -= body.Fz*dt/(2*body.mass);
}

  void time_integration(Particle & body, const double & dt)
{
  // leap-frog
  body.Vx += body.Fx*dt/(body.mass);
  body.Vy += body.Fy*dt/(body.mass);
  body.Vz += body.Fz*dt/(body.mass);
  body.Rx += body.Vx*dt;
  body.Ry += body.Vy*dt;
  body.Rz += body.Vz*dt;

  body.Ek = 0.5*body.mass*((body.Vx*body.Vx)+(body.Vy*body.Vy)+(body.Vz*body.Vz));
}

void print(Particle & body, double time)
{
  std::cout << time << "  "
            << body.Rx << " \t "
            << body.Ry << " \t "
            << body.Rz << " \t "
            << body.Vx << " \t "
            << body.Vy << " \t "
            << body.Vz << " \t "
            << body.Ek << " \t "
            << body.U  << " \t "
            << body.U + body.Ek << " \t "
            << "\n";
}
