#include <iostream> 
#include <vector>
#include <math.h> 
#include<cmath> 
#include<iomanip>
#include<cstdio>
#include<fstream>

typedef double myReal;


template<typename T1, typename T2, int N>
inline void getStress(lbmD2Q9<T1> &lbModelD2Q9, grid2D<T2,N> lbGrid, myReal  &Pxx, myReal  &Pyy, myReal  &Pxy, int X, int Y){
  
  
  Pxx = lbGrid(X,Y,1) + lbGrid(X,Y,3);
  Pyy = lbGrid(X,Y,2) + lbGrid(X,Y,4);
  Pxy = lbGrid(X,Y,5) + lbGrid(X,Y,7);
  
  myReal    den = Pxy + lbGrid(X,Y,8) + lbGrid(X,Y,6);
  myReal  minus = -lbGrid(X,Y,8) - lbGrid(X,Y,6);
  
  
  Pxx += den;
  Pyy += den;
  Pxy += minus;
  
  Pxx = Pxx*(lbModelD2Q9.Cx[1]*lbModelD2Q9.Cx[1]);
  Pyy = Pyy*(lbModelD2Q9.Cx[1]*lbModelD2Q9.Cx[1]);
  Pxy = Pxy*(lbModelD2Q9.Cx[1]*lbModelD2Q9.Cx[1]);
  
}

template<typename T1>
inline void getFgrad(myReal fEq[9], lbmD2Q9<T1> &lbModelD2Q9, myReal rho, myReal  ux, myReal  uy, myReal Pxx, myReal Pyy, myReal Pxy, myReal T, myReal Tinv){
  
  
  myReal dot1(0.0), dot2a(0.0), dot2b(0.0), dot2c(0.0);
  myReal cx2,cy2;
  
  for(int dV=0;dV<9;dV++)
  {
    dot1 = (ux*lbModelD2Q9.Cx[dV] + uy*lbModelD2Q9.Cy[dV])*Tinv*rho;
    cx2 = lbModelD2Q9.Cx[dV]*lbModelD2Q9.Cx[dV];
    cy2 = lbModelD2Q9.Cy[dV]*lbModelD2Q9.Cy[dV];
    
    dot2a = (Pxx - rho*T)*(cx2 - T);
    dot2b = (Pyy - rho*T)*(cy2 - T);
    dot2c = 2.0 * Pxy * (lbModelD2Q9.Cx[dV]*lbModelD2Q9.Cy[dV]);

    fEq[dV] = lbModelD2Q9.W[dV] * (  rho + dot1 + 0.5*Tinv*Tinv*( dot2a + dot2b + dot2c ) );    
  }
  
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<typename T1>
void getEq(myReal fEq[9], lbmD2Q9<T1> &lbModelD2Q9, myReal rho, myReal ux, myReal uy)
{
  for(int dV=0;dV<9;dV++)
  {
    real dot1 = 0.0,dot2 = 0;
    dot1 = ( lbModelD2Q9.Cx[dV]*ux + lbModelD2Q9.Cy[dV]*uy) * lbModelD2Q9.thetaInverse ;
    dot2 = ((lbModelD2Q9.Cx[dV]*ux + lbModelD2Q9.Cy[dV]*uy)*(lbModelD2Q9.Cx[dV]*ux + lbModelD2Q9.Cy[dV]*uy) - (ux*ux + uy*uy)* lbModelD2Q9.theta0)* 0.5 * lbModelD2Q9.thetaInverse * lbModelD2Q9.thetaInverse;
    fEq[dV] = lbModelD2Q9.W[dV] * rho *(1.0 + dot1 + dot2 ) ;
  }
}



template<typename T1, typename T2, int N>
void getMoment(lbmD2Q9<T1> &lbModelD2Q9, grid2D<T2,N> lbGrid, myReal &rhoTemp, myReal &uxTemp, myReal &uyTemp, myReal &T, int X, int Y, T1 dt)
{
  rhoTemp=0.0;
  uxTemp=0.0;
  uyTemp=0.0;
  real ux_temp=0.0, uy_temp=0.0;
  for(int dV=0;dV<9;dV++)
  {
    rhoTemp += lbGrid(X,Y,dV);
    ux_temp += lbGrid(X,Y,dV)*lbModelD2Q9.Cx[dV];
    uy_temp += lbGrid(X,Y,dV)*lbModelD2Q9.Cy[dV];
    
  }
  uxTemp = ux_temp/rhoTemp ;
  uyTemp = uy_temp/rhoTemp ;
  
  T  = (lbModelD2Q9.Cx[1]*lbModelD2Q9.Cx[1])/3.0;
  
}
