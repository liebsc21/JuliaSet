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
    const double r   = init.get_r();
    const double phi = init.get_phi();
    const double xmin = init.get_xmin();
    const double xmax = init.get_xmax();
    const double ymin = init.get_ymin();
    const double ymax = init.get_ymax();
    const double gridwidth = init.get_gridwidth();
    const double delta_x = gridwidth==1 ? 0:(xmax-xmin)/(gridwidth-1);
    const double delta_y = gridwidth==1 ? 0:(ymax-ymin)/(gridwidth-1);
    /* this is how Carsten calculates it */
//    const double delta_x = (xmax-xmin)/(gridwidth);
//    const double delta_y = (ymax-ymin)/(gridwidth);
    const int N = init.get_N();
    const double alpha = 2.*M_PI/n;
//cout<<"alpha = " << alpha << "\n";

    /* iterate over steps, each producing one csv-file */
    for(int t=0; t<N/2; t++){
      vector<vector<double>> grid(gridwidth,
                             vector<double>(gridwidth,0));
      vector<vector<double>> &grid_ref = grid;
      Point point(n,r,phi+2*M_PI*t/N);

      for(int i_y=0; i_y<gridwidth; i_y++){
        double y = ymax - i_y*delta_y;

        for(int i_x=0; i_x<gridwidth; i_x++){
          double x = xmin + i_x*delta_x;

//cout<<"x = " << x << "\n";
//cout<<"y = " << y << "\n";
          point.set_point(x,y);
//cout<<"arg = " << point.phi() << "\n";
          if (x*x+y*y>ymax*ymax || 
              (0.<=point.phi() && point.phi()<alpha) ){
            int it = point.get_it();
            grid[i_y][i_x] = it;
          }
          else grid[i_y][i_x] = 0;
        }
      }

      /* write to file 1-N/2 */
      ofstream myfile1, myfile2;
      stringstream ss1, ss2;
      ss1 << setw(3) << setfill('0') << t;
      ss2 << setw(3) << setfill('0') << N-1-t;
      cout << ss1.str() << "\n";
      myfile1.open("output"+ss1.str()+".csv");
      for(vector<vector<double>>::iterator yrow_it=grid.begin();
          yrow_it!=grid.end(); ++yrow_it){
        for(vector<double>::iterator xrow_it=yrow_it->begin();
            xrow_it!=yrow_it->end(); ++xrow_it){
          if (xrow_it!=yrow_it->begin()) myfile1 << "," << *xrow_it;
          else myfile1 << *xrow_it;
        }
        myfile1 << "\n";
      }
      myfile1.close();

      /* write to file N/2-N*/
      myfile2.open("output"+ss2.str()+".csv");
      for(vector<vector<double>>::reverse_iterator yrow_rit=grid.rbegin();
          yrow_rit!=grid.rend(); ++yrow_rit){
        for(vector<double>::iterator xrow_it=yrow_rit->begin();
            xrow_it!=yrow_rit->end(); ++xrow_it){
          if (xrow_it!=yrow_rit->begin()) myfile2 << "," << *xrow_it;
          else myfile2 << *xrow_it;
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
