#ifndef INIT_INL
#define INIT_INL

#include <iostream>
//#include "init.H"

template <typename T>
Init<T>::Init(int argc, char* argv[]){

  /* TODO: comment */
  boost::program_options::positional_options_description p;
  p.add("card", -1);

  /* program options */
  boost::program_options::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "produce help message")
    ("gridwidth,g", po::value<int>(), "number of pixels in x- and y-direction")
    ("steps,s"    , po::value<int>(), "number of csv-files")
    ("exponent,e" , po::value<int>(), "n in f(z)=z**n+c")
    ("radius,r"   , po::value<T>(), "r in c=r*exp(i*phi)")
    ("phi,p"      , po::value<T>(), "phi in c=r*exp(i*phi)")
    ("card,c"     , po::value<string>() -> default_value("RunCards/Run_1.ini"), 
    "path to a run card (including run card)")
    ("debug,d"    , po::value<int>() -> default_value(0), 
    "display debugging information");

  /* TODO: comment */
  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
  boost::program_options::notify(vm);

  /* print out help-message if specified */
  if (vm.count("help")) {
    cout << desc << '\n';
    throw 1;
  }

  /* TODO: comment */
  m_debug = vm["debug"].as<const int>();
  string card = vm["card"].as<string>();
  boost::property_tree::ptree pt;
  boost::property_tree::ini_parser::read_ini( card, pt );

  /* grid parameters */
  m_gridwidth = pt.get<int>   ("grid parameters.gridwidth");
  m_xmin      = pt.get<T>("grid parameters.xmin");
  m_xmax      = pt.get<T>("grid parameters.xmax");
  m_ymin      = pt.get<T>("grid parameters.ymin");
  m_ymax      = pt.get<T>("grid parameters.ymax");

  /* function parametes */
  m_n   = pt.get<int>   ("function parameters.n");
  m_r   = pt.get<T>("function parameters.r");
  m_phi = pt.get<T>("function parameters.phi");

  /* number of csv-files */
  m_N = pt.get<int>("animation parameters.N");

  /* overwrite options from RunCard, if given on command line */
  if(vm.count("gridwidth"))
     m_gridwidth = vm["gridwidth"].as<const int>();
  if(vm.count("steps"))
     m_N = vm["steps"].as<const int>();
  if(vm.count("exponent"))
     m_n = vm["exponent"].as<const int>();
  if(vm.count("radius"))
     m_r = vm["radius"].as<const T>();
}

#endif /* INIT_INL */
