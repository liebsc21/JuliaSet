#include <iostream>
#include <iomanip>
#include "grid.H"
#include "init.H"
#include "point.H"

using namespace std;

Grid::Grid(int argc, char* argv[]){

    Init init(argc, argv);

    /* function parameters */
    n     = init.get_n();
    r_c   = init.get_r();
    phi_c = init.get_phi();

    /* grid parameters */
    gridwidth   = init.get_gridwidth();
    xmin        = init.get_xmin();
    xmax        = init.get_xmax();
    ymin        = init.get_ymin();
    ymax        = init.get_ymax();
    max_radius2 = min(xmax*xmax,ymax*ymax);
    min_radius2 = (n==11) ? 0.002*max_radius2 : 0.001*max_radius2;
    delta_x     = gridwidth==1 ? 0:(xmax-xmin)/(gridwidth-1);
    delta_y     = gridwidth==1 ? 0:(ymax-ymin)/(gridwidth-1);
    /* this is how Carsten calculates it */
    //delta_x = (xmax-xmin)/(gridwidth);
    //delta_y = (ymax-ymin)/(gridwidth);
    alpha       = 2.*M_PI/n;
    eps1        = (n==2)||(n==4) ? 0. : 4.*M_PI/180;
    eps2        = (n==8) ? 6.*M_PI/180 : 0;

    /* number of csv-files */
    N = init.get_N();

    debug = init.get_debug();

    /* (re)size grid (which stores iterations for each point
       in the complex plane) to appropriate size */
    grid.resize(gridwidth);
    for(int i=0; i<gridwidth; i++){
      grid[i].resize(gridwidth);
    }

//    if(debug) cout<<"alpha = " << alpha << "\n";
//    if(debug) cout<<"eps1 = " << eps1 << "\n";
//    if(debug) cout<<"eps2 = " << eps1 << "\n";
}



void Grid::calc_grid(const int t){ 

  /* This is an auxiliary grid, which is static, as 'grid' 
     refers to it. It must therefore not go out of scope. */
  static vector<vector<int>> grid_aux(gridwidth,
                         vector<int>(gridwidth,0));

  Point point(n,r_c,phi_c+2*M_PI*t/N);

  for(int i_y=0; i_y<gridwidth; i_y++){
    double y = ymax - i_y*delta_y;

    for(int i_x=0; i_x<gridwidth; i_x++){
      double x = xmin + i_x*delta_x;

      /* associate grid with auxiliary grid */
      grid[i_y][i_x] = &grid_aux[i_y][i_x];

      point.set_point(x,y);
      double phi = point.get_phi();
      double radius2 = x*x+y*y;

      /* fill zeroth sector and area outside circle */
      if (radius2>max_radius2 
          || (0.<=phi && phi<=alpha+eps1)
          || phi>2.*M_PI-eps2
          || radius2<min_radius2 ){
        int it = point.get_it();
        grid_aux[i_y][i_x] = it;
      }

      /* fill missing sectors */
      else{
        int sector = point.get_phi()/alpha;
        double phi_org = phi-sector*alpha;
        double r_org   = point.get_r();
        double x_org = r_org*cos(phi_org);
        double y_org = r_org*sin(phi_org);
        int i_x_org = round((x_org-xmin)/delta_x);
        int i_y_org = round((ymax-y_org)/delta_y);
        if(debug && i_y==45 && i_x==45){
          cout<<"(x,y) = (" << x << "," << y << ")\n";
          cout<<"phi = " << phi << "\n";
          cout<<"(i_x,i_y) = (" << i_x << "," << i_y <<")\n";
          cout<< "sector = " << sector << "\n";
          cout<<"(x_org,y_org) = (" << x_org << "," 
              << y_org << ")\n";
          cout<< "phi_org = " << phi_org << "\n";
          cout<<"(i_x_org,i_y_org) = (" << i_x_org << ","
              << i_y_org <<")\n";
          cout << "--------------\n";
        }
        grid[i_y][i_x] = &grid_aux[i_y_org][i_x_org];
      }
    }
  }
  if(debug){
    for(int i_y=0; i_y<gridwidth; i_y++){
//      double y = ymax - i_y*delta_y;
      for(int i_x=0; i_x<gridwidth; i_x++){
//        double x = xmin + i_x*delta_x;
//        if (x*x+y*y<max_radius2 && *grid[i_y][i_x]==0) 
          cout << "*grid[" << i_y << ", "<< i_x << "] = " 
               << *grid[i_y][i_x] << "\n";
      }
    }
  }
}

void Grid::write_to_file(const int t){

  if(debug){
    cout << "write out\n";
    for(int i_y=0; i_y<gridwidth; i_y++){
//      double y = ymax - i_y*delta_y;
      for(int i_x=0; i_x<gridwidth; i_x++){
//        double x = xmin + i_x*delta_x;
//        if (x*x+y*y<max_radius2 && *grid[i_y][i_x]==0) 
          cout << "*grid[" << i_y << ", "<< i_x << "] = " 
               << *grid[i_y][i_x] << "\n";
      }
    }
  }

  /* write to file 1-N/2 */
  ofstream myfile1, myfile2;
  stringstream ss1, ss2;
  ss1 << setw(3) << setfill('0') << t;
  ss2 << setw(3) << setfill('0') << N-1-t;
  cout << ss1.str() << "\n";
  myfile1.open("output"+ss1.str()+".csv");
  for(vector<vector<int*>>::iterator yrow_it=grid.begin();
      yrow_it!=grid.end(); ++yrow_it){
    for(vector<int*>::iterator xrow_it=yrow_it->begin();
        xrow_it!=yrow_it->end(); ++xrow_it){
      if (xrow_it!=yrow_it->begin()) myfile1 << "," << **xrow_it;
      else myfile1 << **xrow_it;
    }
    myfile1 << "\n";
  }
  myfile1.close();

  /* write to file N/2-N*/
  myfile2.open("output"+ss2.str()+".csv");
  for(vector<vector<int*>>::reverse_iterator yrow_rit=grid.rbegin();
      yrow_rit!=grid.rend(); ++yrow_rit){
    for(vector<int*>::iterator xrow_it=yrow_rit->begin();
        xrow_it!=yrow_rit->end(); ++xrow_it){
      if (xrow_it!=yrow_rit->begin()) myfile2 << "," << **xrow_it;
      else myfile2 << **xrow_it;
    }
    myfile2 << "\n";
  }
  myfile2.close();
}
