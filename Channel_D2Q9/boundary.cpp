template<typename T1, typename T2, int N>
void Periodic_Top_Bottom(lbmD2Q9<T1> &lbModelD2Q9, grid2D<T2,N>& lbGrid)
{
    
    int Nx=lbGrid.n1, Ny=lbGrid.n2;

    for(int i=0; i<=Nx; i++)
    {
      for(int dV=0;dV<9;dV++){
        lbGrid(i,0,dV)    = lbGrid(i,Ny,dV);
        lbGrid(i,Ny+1,dV) = lbGrid(i,1,dV); 
        }
    }
        
}

template<typename T1, typename T2, int N>
void Periodic_Left_Right(lbmD2Q9<T1> &lbModelD2Q9, grid2D<T2,N>& lbGrid)
{
    
    int Nx=lbGrid.n1, Ny=lbGrid.n2;

    for(int j=0; j<=Ny; j++)
    {
        for(int dV=0;dV<9;dV++){
            lbGrid(0,j,dV)    = lbGrid(Nx,j,dV);
            lbGrid(Nx+1,j,dV) = lbGrid(1,j,dV); 
        }
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T1, typename T2, int N>
void prepare_Wall(lbmD2Q9<T1> &lbModelD2Q9, grid2D<T2,N>& lbGrid)
{
    int Nx=lbGrid.n1, Ny=lbGrid.n2;
                              
    for(int i=0;i<=Nx+1;i++)
            for(int dV=0;dV<9;dV++)
                    {
                            lbGrid(i,0   ,dV) = lbGrid(i,1 ,dV);
                            lbGrid(i,Ny+1,dV) = lbGrid(i,Ny,dV);
                    }
                            
    
}

template<typename T1, typename T2, int N>
void apply_Wall_BounceBack(lbmD2Q9<T1> &lbModelD2Q9, grid2D<T2,N>& lbGrid)
{
    int Nx=lbGrid.n1, Ny=lbGrid.n2;

    
   // -y bounce back  
     
        for(int i=1;i<=Nx;i++)  
        {  
                lbGrid(i,1,dV_M1_P1)   = lbGrid(i,0,dV_P1_M1);  
                lbGrid(i,1,dV_ZERO_P1) = lbGrid(i,0,dV_ZERO_M1);  
                lbGrid(i,1,dV_P1_P1)   = lbGrid(i,0,dV_M1_M1);  
        }  
       
        // +y bounce back  
     
        for(int i=1;i<=Nx;i++)  
        {  
                lbGrid(i,Ny,dV_P1_M1)   = lbGrid(i,Ny+1,dV_M1_P1);  
                lbGrid(i,Ny,dV_ZERO_M1) = lbGrid(i,Ny+1,dV_ZERO_P1);  
                lbGrid(i,Ny,dV_M1_M1)   = lbGrid(i,Ny+1,dV_P1_P1);  
              
              
        }  
     
}




	  
          





