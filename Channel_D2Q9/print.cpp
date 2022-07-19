#include <iostream> 
#include <vector>
#include <math.h> 
#include<cmath> 
#include<iomanip>
#include<cstdio>
#include<fstream>
#include "lbmD2Q9.h"
typedef double real;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T1, typename T2, int N>
void printMass(lbmD2Q9<T1> &lbModelD2Q9, grid2D<T2,N>& lbGrid, T1 dt)
{
    
int Nx=lbGrid.n1, Ny=lbGrid.n2;
T1 rho,ux,uy,T,sum(0.0);

	for(int j=Ny;j>=1;j--)
	{
	for(int i=1;i<=Nx;i++)
		{
            
			getMoment(lbModelD2Q9,lbGrid,rho,ux,uy,T,i,j,dt);
			sum=sum+rho;
            
		}
	
	}
    std::cout<<sum<<std::endl;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T1, typename T2, int N>
void printVelocity(lbmD2Q9<T1> &lbModelD2Q9, grid2D<T2,N>& lbGrid, int time,T1 dt, double cs)
{
    
  int MAX_Z=1;
  FILE *fpt;
  char *fileName;
  
  int Nx=lbGrid.n1, Ny=lbGrid.n2;
  T1 rho,ux,uy,T; 
  
  fileName = (char *) malloc( (size_t) (45*sizeof(char) ) );
  
  if(!fileName)
  {
    fprintf(stderr, "Memory Allocation failure");
    exit(0);
  }
  sprintf(fileName,"./Velocity_vtk/velocity%d.vtk", time);
  
  fpt = fopen(fileName,"w");
  
  //   vtk file header
  fprintf(fpt,"# vtk DataFile Version 3.0\nVelocity\nASCII\nDATASET STRUCTURED_GRID\n");
  fprintf(fpt,"DIMENSIONS %d %d %d\n", Nx, Ny, MAX_Z);
  
  fprintf(fpt,"POINTS %d double\n", (Nx)*(Ny)*(MAX_Z));
  
  for (int i2=1 ; i2<=Ny;  i2++)
    for (int i1=1 ; i1<=Nx;  i1++)    
      fprintf(fpt,"%d %d 0\n", i1, i2);
    
  fprintf(fpt,"POINT_DATA %d\n", (Nx)*(Ny)*(MAX_Z));
  fprintf(fpt,"VECTORS velocity double\n");
  
  
  
  
  
  for (int i2=1 ; i2<=Ny;  i2++)
    for (int i1=1 ; i1<=Nx;  i1++)
    { 
      getMoment(lbModelD2Q9,lbGrid,rho,ux,uy,T,i1,i2,dt);
      
      fprintf(fpt,"%.7lf %.7lf 0.0\n", ux, uy);    
    }
    
    
    
    
    fclose(fpt);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


