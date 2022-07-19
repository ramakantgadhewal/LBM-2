


template<typename T1, typename T2, int N>
void advection(lbmD2Q9<T1> &lbModelD2Q9, grid2D<T2,N>& lbGrid)
{
    int Nx=lbGrid.n1, Ny=lbGrid.n2;
	
                
        for(int j=1;j<=Ny;j++)
        {
            for(int i=1;i<=Nx;i++)
            {
                lbGrid(i,j,dV_M1_ZERO)=lbGrid(i+1,j,dV_M1_ZERO); 
                lbGrid(i,j,dV_ZERO_M1)=lbGrid(i,j+1,dV_ZERO_M1); 
                lbGrid(i,j,dV_M1_M1)=lbGrid(i+1,j+1,dV_M1_M1);   
                lbGrid(i,j,dV_P1_M1)=lbGrid(i-1,j+1,dV_P1_M1);   

            }
        }
    
    
   
        for(int j=Ny;j>0;j--)
        {
            for(int i=Nx;i>0;i--)
            {
                lbGrid(i,j,dV_P1_ZERO)=lbGrid(i-1,j,dV_P1_ZERO);
                lbGrid(i,j,dV_ZERO_P1)=lbGrid(i,j-1,dV_ZERO_P1);
                lbGrid(i,j,dV_P1_P1)=lbGrid(i-1,j-1,dV_P1_P1);  
                lbGrid(i,j,dV_M1_P1)=lbGrid(i+1,j-1,dV_M1_P1);  


            }
        }
    
}


