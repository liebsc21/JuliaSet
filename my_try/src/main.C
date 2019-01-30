#include <chrono>
#include <iostream>
#include "init.H"
#include "point.H"
#include "grid.H"

using namespace std;


int main(int argc, char* argv[]){

  try{
    auto start = chrono::steady_clock::now();
  
    Grid<double> grid(argc, argv);
    int N = grid.get_N();
  
    /* iterate over steps, each producing one csv-file */
    for(int t=0; t<(N+1)/2; t++){
      grid.calc_grid(t);
      grid.write_to_file(t);
    }
  
    auto end = chrono::steady_clock::now();
    cout << "Elapsed time = " <<
    chrono::duration_cast<chrono::milliseconds>(end-start).count()
    /1000. << " seconds\n";
  }
  
  catch(exception& e) {
    cerr << "error: " << e.what() << "\n";
    cerr << "type '--help' to view options\n";
    return 1;
  }
  catch(int &i)  /* exception, if help-option is given */ 
  {
    return 1;
  }
  catch(...) {
    cerr << "Exception of unknown type!\n";
    return 1;
  }
  
  return 0;
}
