#include "GRID_2D.h"
//
enum dv{
    dv_0_0, //zero velocity
    
    dv_P1_0, ///SC-1
    dv_0_P1,
    dv_M1_0,
    dv_0_M1,

    dv_P3_0, ///SC-3
    dv_0_P3,
    dv_M3_0,
    dv_0_M3,

    dv_P1by2_P1by2,  //bcc 1/2
    dv_M1by2_P1by2,
    dv_M1by2_M1by2,
    dv_P1by2_M1by2


};

void advection_integral_velocites( Grid_N_C_2D &grid){    
    
    for(int i = 0 + grid.noghost ; i < grid.n_x_node - (grid.noghost);i++){
        for(int j = 0 + grid.noghost; j < grid.n_y_node -(grid.noghost); j++){ 

            grid.Node(i,j,dv_0_M1) = grid.Node(i, j+1, dv_0_M1 ); //for SC1
            grid.Node(i,j,dv_M1_0) = grid.Node(i+1, j, dv_M1_0 );
            
        } 
    }



    for(int i = grid.n_x_node - (grid.noghost +1); i> grid.noghost-1; i--){
        for(int j = grid.n_y_node - (grid.noghost +1); j> grid.noghost -1; j--){

            grid.Node(i, j, dv_0_P1) = grid.Node(i   , j-1, dv_0_P1); //for SC1;
            grid.Node(i, j, dv_P1_0) = grid.Node(i-1 , j  , dv_P1_0);

        }
    }


}
/**/
/************************************************************************************************************************************/
void advection_oddtime_halfvelocities(Grid_N_C_2D &grid){

    //shifting from node to cells
    for(int i = 0 + grid.noghost ; i < grid.n_x_node - (grid.noghost);i++){
        for(int j = 0+ grid.noghost ; j < grid.n_y_node - (grid.noghost); j++){ 
            grid.Cell(i - grid.noghost,  j - grid.noghost   , dv_M1by2_M1by2)  = grid.Node(i,j,dv_M1by2_M1by2);
            grid.Cell(i - grid.noghost,  j - grid.noghost+1 , dv_M1by2_P1by2)  = grid.Node(i,j,dv_M1by2_P1by2);

        }}

     for(int i = grid.n_x_node - (grid.noghost +1); i> grid.noghost-1; i--){
        for(int j = grid.n_y_node - (grid.noghost +1); j> grid.noghost -1; j--){

            grid.Cell(i - grid.noghost +1, j - grid.noghost  , dv_P1by2_M1by2) = grid.Node(i , j, dv_P1by2_M1by2); 
            grid.Cell(i - grid.noghost +1, j - grid.noghost+1, dv_P1by2_P1by2) = grid.Node(i , j, dv_P1by2_P1by2);

        }
    }


//////copying the boundary nodes 
for ( int j  = 0; j< grid.n_y_cell; j++){
    grid.Cell(0 ,j ,dv_P1by2_P1by2) = grid.Cell(grid.n_x_cell -1, j, dv_P1by2_P1by2); /// copying right most cell to left
    grid.Cell(0 ,j ,dv_P1by2_M1by2) = grid.Cell(grid.n_x_cell -1, j, dv_P1by2_M1by2);

    grid.Cell(grid.n_x_cell -1, j, dv_M1by2_P1by2) = grid.Cell(0,j, dv_M1by2_P1by2); //// copying left most cell to right most
    grid.Cell(grid.n_x_cell -1, j, dv_M1by2_M1by2) = grid.Cell(0,j, dv_M1by2_M1by2);
}

for( int i = 0; i< grid.n_x_cell; i++){

    grid.Cell(i, 0, dv_P1by2_P1by2 ) = grid.Cell(i, grid.n_y_cell - 1, dv_P1by2_M1by2); ////copying top to bottom
    grid.Cell(i, 0, dv_M1by2_P1by2 ) = grid.Cell(i, grid.n_y_cell - 1, dv_M1by2_P1by2);

    grid.Cell(i, grid.n_y_cell - 1, dv_M1by2_M1by2) = grid.Cell(i, 0, dv_M1by2_M1by2); ///copying bottom to top
    grid.Cell(i, grid.n_y_cell - 1, dv_P1by2_M1by2) = grid.Cell(i, 0, dv_P1by2_M1by2);
}
}
/**********************************************************************************************************************************************/


/**********************************************************************************************************************************************/
void advection_eventime_halfvelocities(Grid_N_C_2D &grid){

    for(int i = 0 + grid.noghost ; i < grid.n_x_node - (grid.noghost);i++){
        for(int j = 0+ grid.noghost ; j < grid.n_y_node - (grid.noghost); j++){ 
            grid.Node(i,j,dv_M1by2_M1by2) = grid.Cell( i - grid.noghost +1 ,  j - grid.noghost +1 ,dv_M1by2_M1by2);
            grid.Node(i,j,dv_M1by2_P1by2) = grid.Cell( i - grid.noghost +1 ,  j - grid.noghost    ,dv_M1by2_P1by2);

        }}

     for(int i = grid.n_x_node - (grid.noghost +1); i> grid.noghost-1; i--){
        for(int j = grid.n_y_node - (grid.noghost +1); j> grid.noghost -1; j--){

          grid.Node(i , j, dv_P1by2_M1by2)=  grid.Cell(i - grid.noghost   , j - grid.noghost +1 , dv_P1by2_M1by2) ;
          grid.Node(i , j, dv_P1by2_P1by2)=  grid.Cell(i - grid.noghost   , j - grid.noghost, dv_P1by2_P1by2);

        }
    }


}
/**********************************************************************************************************************************************/







int main(){
    int No_ghost_cell = 2;
    Grid_N_C_2D grid(5,5,No_ghost_cell,5);
    double p = 0.1;

}
