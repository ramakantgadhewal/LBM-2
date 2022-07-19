
#include <iostream> 
#include <vector>
#include <math.h> 
#include<cmath> 
#include<iomanip>
#include<cstdio>
#include<fstream>

typedef double real;

//getEq shifted to main
template<typename T1, typename T2, int N>
void collide(lbmD2Q9<T1> &lbModelD2Q9, grid2D<T2,N>& lbGrid,  double beta, double dX, double dt, double kinVisc, double tau, double gx, double gy)
{
  real fEq[9], G[9];
  real ux, uy, rho, T;
  int Nx=lbGrid.n1, Ny=lbGrid.n2;
  
  for(int j=1;j<=Ny;j++)
  {
    
    for(int i=1;i<=Nx;i++)
    {
                
      getMoment(lbModelD2Q9,lbGrid, rho, ux, uy, T, i,j, dt); //calculates rho,ux,uy
      getEq(fEq, lbModelD2Q9, rho, ux, uy);                   //calculates fEq 
      
      
      for(int dV=0;dV<9;dV++)
      {
          G[dV] = rho * lbModelD2Q9.W[dV] * lbModelD2Q9.thetaInverse * 
                     ( (lbModelD2Q9.Cx[dV])*gx + (lbModelD2Q9.Cy[dV])*gy )  ;
                     
          lbGrid(i,j,dV) = lbGrid(i,j,dV) + 2.0*beta*(fEq[dV] - lbGrid(i,j,dV)) + (2.0*beta*tau*G[dV]);
	
        }
    
    }
  }
  
}

