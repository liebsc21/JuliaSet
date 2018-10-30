//#include <boost/program_options.hpp>
//namespace po = boost::program_options;
//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/ini_parser.hpp>
//
#include <iostream>
//#include <iterator>
using namespace std;

#include "init.H"
#include "point.H"


int main(int argc, char* argv[]){

  try{
    Init init(argc, argv);
    const double n   = init.get_n();
    const double r   = init.get_r();
    const double phi = init.get_phi();
    Point point(n,r,phi);
    point.set_point(0.5,0.5);
    point.get_it();
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
