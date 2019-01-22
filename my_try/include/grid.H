#ifndef GRID_H
#define GRID_H

#include <vector>
//#include <list>// TODO: Check whether using list somewhere is faster
using namespace std;

template <class T>
class Grid {

  private:
    /* function parameters */
    int n;
    T r_c;
    T phi_c;

    /* grid parameters */
    T gridwidth;
    T xmin, xmax, ymin, ymax;
    T max_radius2, min_radius2;
    T delta_x, delta_y;
    T alpha;
    T eps1, eps2;

    /* number of csv-files */
    int N;

    bool debug;

    /* grid, which stores iterations for each point
       in the complex plane */
    vector<vector<int*>> grid;

  public:
    Grid(int argc, char* argv[]);
    void calc_grid(const int);
    void write_to_file(const int);
    int get_N()                { return N; }
};

#include "grid.inl"

#endif /* GRID_H */
