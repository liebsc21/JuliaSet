#include <iostream>
//#include <iterator>
using namespace std;

#include "init.H"
#include "point.H"
#include <fstream>
#include <chrono>
//using namespace std::chrono_literals;


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
    const double delta_x = (xmax-xmin)/gridwidth;
    const double delta_y = (ymax-ymin)/gridwidth;

    Point point(n,r,phi);
    ofstream myfile;
    myfile.open("output_1.csv");

    for(int i_x=0; i_x<=gridwidth; i_x++){
      double x = xmin + i_x*delta_x;
      for(int i_y=0; i_y<=gridwidth; i_y++){
        double y = ymax - i_y*delta_y;
//        cout << "x = " << x << ", y = " << y << "\n";
        point.set_point(x,y);
        int it = point.get_it();
        if (i_y==0) myfile << it;
        else myfile << "," << it;
      }
      myfile << "\n";
    }
    myfile.close();

    auto end = chrono::steady_clock::now();
    cout << "Elapsed time = " <<
    chrono::duration_cast<chrono::milliseconds>(end-start).count() << 
    " miliseconds\n";
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
