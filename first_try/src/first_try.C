#include <iostream>
using namespace std;

#include "init.H"
#include "point.H"
#include <fstream>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>
#include <list>


int main(int argc, char* argv[]){

  try{
    auto start = chrono::steady_clock::now();

    Init init(argc, argv);
    const int    n   = init.get_n();
    const double r_c   = init.get_r();
    const double phi_c = init.get_phi();
    const double xmin = init.get_xmin();
    const double xmax = init.get_xmax();
    const double ymin = init.get_ymin();
    const double ymax = init.get_ymax();
    const double rmin2 = min(xmax*xmax,ymax*ymax);
    const double gridwidth = init.get_gridwidth();
    const double delta_x = gridwidth==1 ? 0:(xmax-xmin)/(gridwidth-1);
    const double delta_y = gridwidth==1 ? 0:(ymax-ymin)/(gridwidth-1);
    /* this is how Carsten calculates it */
//    const double delta_x = (xmax-xmin)/(gridwidth);
//    const double delta_y = (ymax-ymin)/(gridwidth);
    const int N = init.get_N();
    const double alpha = 2.*M_PI/n;
    const double eps   = (n==2)||(n==4) ? 0. : n==3 ? 20.*M_PI/180 
                         : 4.*M_PI/180;
cout << eps;
    const bool debug = init.get_debug();

    if(debug) cout<<"alpha = " << alpha << "\n";

    /* iterate over steps, each producing one csv-file */
    for(int t=0; t<N/2; t++){
      vector<vector<int>> grid(gridwidth,
                             vector<int>(gridwidth,0));
      vector<vector<int*>> grid_p(gridwidth,vector<int*>(gridwidth));

      Point point(n,r_c,phi_c+2*M_PI*t/N);

      for(int i_y=0; i_y<gridwidth; i_y++){
        double y = ymax - i_y*delta_y;

        for(int i_x=0; i_x<gridwidth; i_x++){
          double x = xmin + i_x*delta_x;

          /* associate grid of pointers with original grid */
          grid_p[i_y][i_x] = &grid[i_y][i_x];
          point.set_point(x,y);
          /* fill zeroth sector and area outside circle */
          double phi = point.get_phi();
          if (x*x+y*y>rmin2 || (0.<=phi && phi<=alpha+eps) ){
            int it = point.get_it();
            grid[i_y][i_x] = it;
          }
          else{
            /* fill missing sectors */
            int sector = point.get_phi()/alpha;
            double phi_org = phi-sector*alpha;
            double r_org   = point.get_r();
            double x_org = r_org*cos(phi_org);
            double y_org = r_org*sin(phi_org);
            int i_x_org = round((x_org-xmin)/delta_x);
            int i_y_org = round((ymax-y_org)/delta_y);
            if(debug && i_y==44 && i_x==46){
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
            grid_p[i_y][i_x] = &grid[i_y_org][i_x_org];
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
      for(vector<vector<int*>>::iterator yrow_it=grid_p.begin();
          yrow_it!=grid_p.end(); ++yrow_it){
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
      for(vector<vector<int*>>::reverse_iterator yrow_rit=grid_p.rbegin();
          yrow_rit!=grid_p.rend(); ++yrow_rit){
        for(vector<int*>::iterator xrow_it=yrow_rit->begin();
            xrow_it!=yrow_rit->end(); ++xrow_it){
          if (xrow_it!=yrow_rit->begin()) myfile2 << "," << **xrow_it;
          else myfile2 << **xrow_it;
        }
        myfile2 << "\n";
      }
      myfile2.close();
    }

    auto end = chrono::steady_clock::now();
    cout << "Elapsed time = " <<
    chrono::duration_cast<chrono::milliseconds>(end-start).count()/1000. << 
    " seconds\n";
  }
  catch(exception& e) {
    cerr << "error: " << e.what() << "\n";
    return 1;
  }
  catch(string &s)  /* exception, if help-option is given */ 
  {
    return 1;
  }
  catch(...) {
    cerr << "Exception of unknown type!\n";
    return 1;
  }

  return 0;
}
