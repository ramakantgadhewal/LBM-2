#include<iostream>

class Grid_N_C_3D{
public:
int nNodes , nCell,dv,total_mem_node,total_mem_cell;

int n_x_node,n_y_node,n_z_node,
    n_x,n_y,n_z,
    n_x_cell,n_y_cell,n_z_cell,d_v;

double *data_node,*data_cell;

Grid_N_C_3D(int nx, int ny, int nz, int dv){
    
    n_x = nx;
    n_y = ny;
    n_z = nz;


    n_x_node = nx +6;    //3 ghost nodes in each direction
    n_y_node = ny +6;
    n_z_node = nz +6;
    d_v = dv;            //No of population
    

    n_x_cell = nx +1;   // +1 total no of cells compared to physical domain
    n_y_cell = ny +1;
    n_z_cell = nz +1;

   
    nNodes = (n_x_node)*(n_y_node)*(n_z_node); 
    nCell  = (n_x_cell)*(n_y_cell)*(n_z_cell);    
   

    total_mem_node = nNodes*dv;
    total_mem_cell = nCell*dv;
   
   
    data_node = new double[total_mem_node];
    data_cell = new double[total_mem_cell];
}



double Node(const int i,const int j,const int k,const int dv) const{return data_node[((i*n_y_node +j)*n_z_node + k)*d_v + dv ];}
double& Node(const int i, const int j,const  int k,const  int dv) {return data_node[((i*n_y_node +j)*n_z_node + k)*d_v + dv ];}

double Cell(const int i,const int j,const int k,const int dv) const{return data_cell[((i*n_y_node +j)*n_z_node + k)*d_v + dv ];}
double& Cell(const int i, const int j,const  int k,const  int dv) {return data_cell[((i*n_y_cell +j)*n_z_cell + k)*d_v + dv ];}



~Grid_N_C_3D(){
    delete [] data_node;
    delete [] data_cell;
}


};



