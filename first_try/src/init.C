#include "init.H"

Init::Init(int argc, char* argv[]){
  boost::program_options::positional_options_description p;
  p.add("card", -1);
  /* program options */
  boost::program_options::options_description desc("Allowed options");
  desc.add_options()
    ("help", "produce help message")
    ("gridwidth", po::value<int>(), "")
    ("steps", po::value<int>(), "")
    ("card", po::value<string>() -> default_value("RunCards/Run_1.ini"), "path to a run card (including run card)");

  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
  boost::program_options::notify(vm);

  if (vm.count("help")) {
    cout << desc << '\n';
    throw "help";
  }

  string card = vm["card"].as<string>();
  boost::property_tree::ptree pt;
  boost::property_tree::ini_parser::read_ini( card, pt );

  m_xmin      = pt.get<double>("grid parameters.xmin");
  m_xmax      = pt.get<double>("grid parameters.xmax");
  m_ymin      = pt.get<double>("grid parameters.ymin");
  m_ymax      = pt.get<double>("grid parameters.ymax");
  m_gridwidth = pt.get<int>("grid parameters.gridwidth");
  m_n   = pt.get<int>("function parameters.n");
  m_r   = pt.get<double>("function parameters.r");
  m_phi = pt.get<double>("function parameters.phi");
  m_N = pt.get<int>("animation parameters.N");

  if(vm.count("gridwidth"))
     m_gridwidth = vm["gridwidth"].as<const int>();
  if(vm.count("steps"))
     m_N = vm["steps"].as<const int>();
}
