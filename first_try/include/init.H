#ifndef INIT_H
#define INIT_H

#include <boost/program_options.hpp>
namespace po = boost::program_options;
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <iostream>
#include <iterator>

using namespace std;

class Init {
  private:
    /* grid parameters */
    double m_xmin, m_xmax, m_ymin, m_ymax;
    int m_gridwidth;
    /* function parameters */
    double m_r, m_phi;
    int m_n;
    /* animation parameters*/
    int m_N;

  public:
    Init(int argc, char* argv[]);

    int    get_n()   { return m_n; }
    double get_r()   { return m_r; }
    double get_phi() { return m_phi; }

    double get_xmin() { return m_xmin; }
    double get_xmax() { return m_xmax; }
    double get_ymin() { return m_ymin; }
    double get_ymax() { return m_ymax; }
    int get_gridwidth() { return m_gridwidth; }

    int get_N() { return m_N; }
};

#endif /* INIT_H */
