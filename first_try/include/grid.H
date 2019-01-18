#ifndef GRID_H
#define GRID_H

#include <vector>
using namespace std;

class Grid {

  private:
    /* function parameters */
    int n;
    double r_c;
    double phi_c;

    /* grid parameters */
    double gridwidth;
    double xmin, xmax, ymin, ymax;
    double max_radius2, min_radius2;
    double delta_x, delta_y;
    double alpha;
    double eps1, eps2;

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

#endif /* GRID_H */
