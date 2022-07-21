#include "GRID_2D.h"

enum velocityDir{ 
dV_ZERO_ZERO,
dV_P1_ZERO, dV_ZERO_P1, dV_M1_ZERO, dV_ZERO_M1,
dV_P3_ZERO, dV_ZERO_P3, dV_M3_ZERO, dV_ZERO_M3,
dV_PH1_PH1, dV_MH1_PH1, dV_MH1_MH1, dV_PH1_MH1
}; 






template<typename T>
void advection(Grid_N_C_2D<T> &grid){
    

        for(int i = 0 + grid.noghost ; i < grid.n_x_node - (grid.noghost);i++){
        for(int j = 0 + grid.noghost ; j < grid.n_y_node - (grid.noghost); j++){ 
            
            grid.Node(i,j,dV_ZERO_M1) = grid.Node(i  ,j+1, dV_ZERO_M1 ); //for SC1 -Node
            grid.Node(i,j,dV_M1_ZERO) = grid.Node(i+1,j  , dV_M1_ZERO );

            grid.Cell(i,j,dV_ZERO_M1) = grid.Cell(i  ,j+1, dV_ZERO_M1 ); //for SC1 -cell
            grid.Cell(i,j,dV_M1_ZERO) = grid.Cell(i+1,j  , dV_M1_ZERO );

            ///half velocities
            std::cout<<grid.Node(i,j,dV_MH1_MH1)<<"before "<<i<<j <<std::endl;
            grid.Node(i,j,dV_MH1_MH1) = grid.Cell(i  ,j  , dV_MH1_MH1);
            grid.Node(i,j,dV_MH1_PH1) = grid.Cell(i  ,j-1, dV_MH1_PH1);
            
            grid.Cell(i,j,dV_MH1_MH1) = grid.Node(i+1,j+1, dV_MH1_MH1);
            grid.Cell(i,j,dV_MH1_PH1) = grid.Node(i+1,j  , dV_MH1_PH1);

            //3 velocities

            grid.Node(i,j,dV_ZERO_M3) = grid.Node(i  ,j+3, dV_ZERO_M3);
            grid.Node(i,j,dV_M3_ZERO) = grid.Node(i+3,j  , dV_M3_ZERO);

            grid.Cell(i,j,dV_ZERO_M3) = grid.Cell(i  ,j+3, dV_ZERO_M3);
            grid.Cell(i,j,dV_M3_ZERO) = grid.Cell(i+3,j  , dV_M3_ZERO);
            std::cout<<grid.Node(i,j,dV_MH1_MH1) <<" "<<i<<j<<std::endl;
        } 
    }

        for(int i = grid.n_x_node - (grid.noghost +1); i> grid.noghost-1; i--){
        for(int j = grid.n_y_node - (grid.noghost +1); j> grid.noghost-1; j--){

            //SC1

            grid.Node(i,j, dV_ZERO_P1) = grid.Node(i  ,j-1, dV_ZERO_P1);
            grid.Node(i,j, dV_P1_ZERO) = grid.Node(i-1,j  , dV_P1_ZERO);

            grid.Cell(i,j,dV_ZERO_P1) = grid.Cell(i  ,j-1, dV_ZERO_P1 );
            grid.Cell(i,j,dV_P1_ZERO) = grid.Cell(i-1,j  , dV_P1_ZERO );
      
            ///half velocities
            grid.Node(i,j,dV_PH1_MH1) = grid.Cell(i-1,j  , dV_PH1_MH1);
            grid.Node(i,j,dV_PH1_PH1) = grid.Cell(i-1,j-1, dV_PH1_PH1);


            grid.Cell(i,j,dV_PH1_MH1) = grid.Node(i  ,j+1, dV_PH1_MH1);
            grid.Cell(i,j,dV_PH1_PH1) = grid.Node(i  ,j  , dV_PH1_PH1);

            //SC3
            grid.Node(i,j, dV_ZERO_P3) = grid.Node(i  ,j-3, dV_ZERO_P3);
            grid.Node(i,j, dV_P3_ZERO) = grid.Node(i-3,j  , dV_P3_ZERO);


            grid.Cell(i,j,dV_ZERO_P3) = grid.Cell(i  ,j-3, dV_ZERO_P3 );
            grid.Cell(i,j,dV_P3_ZERO) = grid.Cell(i-3,j  , dV_P3_ZERO );

        
        }}

}


template<typename T>
void periodic(Grid_N_C_2D<T> &grid){

    //---------------------------------top bottom---------------------------------------//
    for(int i = 0; i<grid.n_x_node; i++){
        ///-------top to bottom----///
        //SC1
        grid.Node(i,grid.noghost -1,dV_ZERO_P1) = grid.Node(i, grid.n_y_node - (grid.noghost +1),dV_ZERO_P1); ///copying to first adjacent ghost node from last node physical domain
        grid.Cell(i,grid.noghost -1,dV_ZERO_P1) = grid.Cell(i, grid.n_y_node - (grid.noghost +1),dV_ZERO_P1); 

        //SC3
        grid.Node(i,0,dV_ZERO_P3) = grid.Node(i, grid.n_y_node - (grid.noghost +1),dV_ZERO_P3);         
        grid.Cell(i,0,dV_ZERO_P3) = grid.Cell(i, grid.n_y_node - (grid.noghost +1),dV_ZERO_P3);

        grid.Node(i,1,dV_ZERO_P3) = grid.Node(i, grid.n_y_node - (grid.noghost +2),dV_ZERO_P3);
        grid.Cell(i,1,dV_ZERO_P3) = grid.Cell(i, grid.n_y_node - (grid.noghost +2),dV_ZERO_P3);

        grid.Node(i,2,dV_ZERO_P3) = grid.Node(i, grid.n_y_node - (grid.noghost +3),dV_ZERO_P3);
        grid.Cell(i,2,dV_ZERO_P3) = grid.Cell(i, grid.n_y_node - (grid.noghost +3),dV_ZERO_P3);

        //SC-1/2
        grid.Cell(i,grid.noghost -1,dV_PH1_PH1) = grid.Cell(i, grid.n_y_node - (grid.noghost +1),dV_PH1_PH1); //top cell to bottom
        grid.Cell(i,grid.noghost -1,dV_MH1_PH1) = grid.Cell(i, grid.n_y_node - (grid.noghost +1),dV_MH1_PH1);

        ///-------bottom to top------///
        //SC -1
        grid.Node(i,grid.n_y_node - grid.noghost,dV_ZERO_M1) = grid.Node(i, grid.noghost,dV_ZERO_M1);
        grid.Cell(i,grid.n_y_node - grid.noghost,dV_ZERO_M1) = grid.Cell(i, grid.noghost,dV_ZERO_M1);

        //SC3
        grid.Node(i,grid.n_y_node - (grid.noghost),dV_ZERO_M3)   = grid.Node(i,grid.noghost,dV_ZERO_M3);
        grid.Cell(i,grid.n_y_node - (grid.noghost),dV_ZERO_M3)   = grid.Cell(i,grid.noghost,dV_ZERO_M3);

        grid.Node(i,grid.n_y_node - (grid.noghost-1),dV_ZERO_M3) = grid.Node(i,grid.noghost+1,dV_ZERO_M3);
        grid.Cell(i,grid.n_y_node - (grid.noghost-1),dV_ZERO_M3) = grid.Cell(i,grid.noghost+1,dV_ZERO_M3);
        
        grid.Node(i,grid.n_y_node - (grid.noghost-2),dV_ZERO_M3) = grid.Node(i,grid.noghost+2,dV_ZERO_M3);
        grid.Cell(i,grid.n_y_node - (grid.noghost-2),dV_ZERO_M3) = grid.Cell(i,grid.noghost+2,dV_ZERO_M3);


        //SC-1/2
        grid.Node(i,grid.n_y_node - (grid.noghost),dV_PH1_MH1) = grid.Node(i,grid.noghost,dV_PH1_MH1);
        grid.Node(i,grid.n_y_node - (grid.noghost),dV_MH1_MH1) = grid.Node(i,grid.noghost,dV_MH1_MH1);

    }


    //--------------------------------------------------left right-----------------------------------------------//

    for(int j =0; grid.n_y_node;j++){
        //--------right to left-------//
        grid.Node(grid.noghost -1,j,dV_P1_ZERO) = grid.Node( grid.n_y_node - (grid.noghost +1),j,dV_P1_ZERO); ///copying to first adjacent ghost node from last node physical domain
        grid.Cell(grid.noghost -1,j,dV_P1_ZERO) = grid.Cell( grid.n_y_node - (grid.noghost +1),j,dV_P1_ZERO);

        //SC3
        grid.Node(0,j,dV_P3_ZERO) = grid.Node(grid.n_x_cell - (grid.noghost +1),j,dV_P3_ZERO);         
        grid.Cell(0,j,dV_P3_ZERO) = grid.Cell(grid.n_x_cell - (grid.noghost +1),j,dV_P3_ZERO);

        grid.Node(1,j,dV_P3_ZERO) = grid.Node(grid.n_x_cell - (grid.noghost +2),j,dV_P3_ZERO);
        grid.Cell(1,j,dV_P3_ZERO) = grid.Cell(grid.n_x_cell - (grid.noghost +2),j,dV_P3_ZERO);

        grid.Node(2,j,dV_P3_ZERO) = grid.Node(grid.n_x_cell - (grid.noghost +3),j,dV_P3_ZERO);
        grid.Cell(2,j,dV_P3_ZERO) = grid.Cell(grid.n_x_cell - (grid.noghost +3),j,dV_P3_ZERO);

        //SC-1/2
        grid.Cell(grid.noghost -1,j,dV_PH1_PH1) = grid.Cell(grid.n_x_cell - (grid.noghost +1),j,dV_PH1_PH1); 
        grid.Cell(grid.noghost -1,j,dV_PH1_MH1) = grid.Cell(grid.n_x_cell - (grid.noghost +1),j,dV_PH1_MH1);

        ///-------left to right-----///
        //SC -1
        grid.Node(grid.n_x_cell - grid.noghost,j,dV_M1_ZERO) = grid.Node(grid.noghost,j,dV_M1_ZERO);
        grid.Cell(grid.n_x_cell - grid.noghost,j,dV_M1_ZERO) = grid.Cell(grid.noghost,j,dV_M1_ZERO);

        //SC3
        grid.Node(grid.n_x_cell - (grid.noghost)  ,j,dV_M3_ZERO)   = grid.Node(grid.noghost  ,j,dV_M3_ZERO);
        grid.Cell(grid.n_x_cell - (grid.noghost)  ,j,dV_M3_ZERO)   = grid.Cell(grid.noghost  ,j,dV_M3_ZERO);

        grid.Node(grid.n_x_cell - (grid.noghost-1),j,dV_M3_ZERO)   = grid.Node(grid.noghost+1,j,dV_M3_ZERO);
        grid.Cell(grid.n_x_cell - (grid.noghost-1),j,dV_M3_ZERO)   = grid.Cell(grid.noghost+1,j,dV_M3_ZERO);

        grid.Node(grid.n_x_cell - (grid.noghost-2),j,dV_M3_ZERO)   = grid.Node(grid.noghost+2,j,dV_M3_ZERO);
        grid.Cell(grid.n_x_cell - (grid.noghost-2),j,dV_M3_ZERO)   = grid.Cell(grid.noghost+2,j,dV_M3_ZERO);


        //SC-1/2
        grid.Node(grid.n_x_cell - (grid.noghost),j,dV_MH1_PH1) = grid.Node(grid.noghost,j,dV_MH1_PH1);
        grid.Node(grid.n_x_cell - (grid.noghost),j,dV_MH1_MH1) = grid.Node(grid.noghost,j,dV_MH1_MH1);





    }







}





int main (){

    Grid_N_C_2D<double> grid1(5,5,3,13);
    ///Initialize
    for (int i =0; i<grid1.n_x_node;i++){
        for( int j = 0; j< grid1.n_x_node; j++){
            for(int dv = 0; dv<13; dv++){
                grid1.Node(i,j,dv) = 1.1;
                grid1.Cell(i,j,dv) = 1.2;

            }
        }
    }

// for (int i =0; i<grid1.n_x_node;i++){
//         for( int j = 0; j< grid1.n_x_node; j++){
//             for(int dv = 0; dv<13; dv++){
//                 std::cout<<grid1.Node(i,j,dv)<<" Node "<<dv<<std::endl;
//                 std::cout<<grid1.Cell(i,j,dv)<<"cell  "<<dv<<std::endl;

//             }
//         }
//     }



}