// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/* The simplest usage of the library.
 */

#include <boost/program_options.hpp>
namespace po = boost::program_options;
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <iostream>
#include <iterator>
using namespace std;

int main(int argc, char* argv[])
{
  try {
    boost::program_options::positional_options_description p;
    p.add("card", -1);
    /* program options */
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
      ("help", "produce help message")
      ("gridwidth", po::value<int>(), "")
      ("card", po::value<string>() -> default_value("RunCards/Run_1.ini"), "path to a run card (including run card)");
  
    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    boost::program_options::notify(vm);
  
    if (vm.count("help")) {
      cout << desc << '\n';
      return 1;
    }
  
    string card = vm["card"].as<string>();
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini( card, pt );
  
    int gridwidth = pt.get<int>("grid parameters.gridwidth");
//    std::cout << "gridwidth  = " << gridwidth << "\n";

    if(vm.count("gridwidth")) {
      const int new_gridwidth = vm["gridwidth"].as<const int>(); 
//      cout << "Resetting gridwidth to " << new_gridwidth << "\n";
      gridwidth = new_gridwidth;
    }

  }
  catch(exception& e) {
    cerr << "error: " << e.what() << "\n";
    return 1;
  }
  catch(...) {
    cerr << "Exception of unknown type!\n";
    return 1;
  }

  return 0;
}
