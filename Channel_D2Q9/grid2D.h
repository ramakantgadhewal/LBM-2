#ifndef _GRID2D_H_
#define _GRID2D_H_

template<typename T, int dV >
struct grid2D
{
    int n1, n2, m1, m2;
    grid2D(int Nx, int Ny, int NG1, int NG2);   //class constructor declaration
    T *data;

    //overload subscript type operator
    
    T  operator()(const int i, const int j, const int m) const {return data[ (m1*dV*j) + (dV*i) + m ];}
    T &operator()(const int i, const int j, const int m)       {return data[ (m1*dV*j) + (dV*i) + m ];}
    
};

//class constructor definition
template<typename T, int dV>
grid2D<T, dV>::grid2D(int Nx, int Ny, int NG1, int NG2)
    {
        n1 = Nx;
        n2 = Ny;
        m1 = n1 + 2*NG1;
        m2 = n2 + 2*NG2;
        
        int size = m1 * m2 * dV;
        data = new T[size];
    }


#endif

