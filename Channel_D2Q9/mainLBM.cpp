#include<stdio.h>
#include<cmath>
#include<iomanip>
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include "grid2D.h"
#include "matrix.h"
#include "lbmD2Q9.h"
#include "advection.cpp"
#include "collide.cpp"
#include "boundary.cpp"
#include "print.cpp"
#include "equi.cpp"


typedef double myReal;

int main()
{
  myReal aspectRatio(4), Ny(50);  
  myReal Nx             = aspectRatio*Ny ;
  myReal X1GHOST(1),X2GHOST(1);
  myReal c              =  1.0;  
  myReal cs2            = (c*c)/3.0;   
  myReal cs             = sqrt(cs2);
  myReal rho            = 1.0;

  myReal Ly             = Ny;
  myReal Lx             = Nx; 
  myReal dX             = 1.0;
  myReal dt             = dX/c;
  myReal Re             = 10.0;        // Re = UX0 * D/ kinVisc          
  myReal Ma             = 0.05;
  
  myReal UX0            = Ma*cs;
  myReal UY0            = 0.0;
  myReal kinVisc        = UX0*Ly/Re;
  myReal tau            = kinVisc/cs2;
  myReal tauNdim        = tau/dt;
  myReal beta           = 1.0/(2.0*tauNdim + 1.0);
  myReal convectionTime = Nx/UX0;
  
  double gx = 1.0*UX0*UX0/(Ly*Re);
  double gy = 0.0;
  
  const int NUM_DV = 9;
  myReal fEqInitial[9];
    
  lbmD2Q9<myReal> lbModelD2Q9(c , cs2);
  grid2D<myReal, NUM_DV> lbGrid(Nx,Ny,X1GHOST,X2GHOST);
    
  
  //-------------------------------- Initialize ---------------------------------------------//
  
  for(int j = 0; j <= Ny+1; j++){
    for(int i = 0; i <= Nx+1; i++){
      
               getEq(fEqInitial, lbModelD2Q9, rho, 0.0, 0.0);
               
               for(int dV = 0; dV < 9; dV++){
                   lbGrid(i,j,dV)=fEqInitial[dV]; 
      }
    
    }

  }
       
  printMass(lbModelD2Q9,lbGrid, dt);   
  printVelocity(lbModelD2Q9,lbGrid,0, dt, cs);
  
  //-------------------------------- -------------------------------------------------------//

    
  int SimulationTime = 20.0* convectionTime/dt;
  for(int step=1; step<=SimulationTime; step++)    
  {
    
    collide(lbModelD2Q9, lbGrid , beta, dX, dt, kinVisc, tau, gx, gy);
    Periodic_Left_Right(lbModelD2Q9, lbGrid);
    prepare_Wall(lbModelD2Q9, lbGrid);
    advection(lbModelD2Q9, lbGrid);
    apply_Wall_BounceBack(lbModelD2Q9, lbGrid);
    
    if(step%1000==0){
         printMass(lbModelD2Q9,lbGrid, dt);   
         printVelocity(lbModelD2Q9,lbGrid,step, dt, cs);
    }
      
  }
  
      
  return 0;
  
}
