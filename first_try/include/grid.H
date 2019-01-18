#ifndef GRID_H
#define GRID_H

#include <vector>
using namespace std;

class Grid {

  private:
    int n;
    double r_c;
    double phi_c;
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    double max_radius2;
    double min_radius2;
    double gridwidth;
    double delta_x;
    double delta_y;
    int N;
    double alpha;
    double eps1;
    double eps2;
    bool debug;
    vector<vector<int*>> grid_p;

  public:
    Grid(int argc, char* argv[]);
    void calc_grid(const int);
    void write_to_file(const int);
    int get_N()                { return N; }
};

#endif /* GRID_H */
