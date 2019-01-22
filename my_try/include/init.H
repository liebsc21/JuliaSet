#ifndef INIT_H
#define INIT_H

#include <boost/program_options.hpp>
namespace po = boost::program_options;
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

using namespace std;

template <class T>
class Init {

  private:
    /* grid parameters */
    T m_xmin, m_xmax, m_ymin, m_ymax;
    int m_gridwidth;
    /* function parameters */
    T m_r, m_phi;
    int m_n;
    /* number of csv-files */
    int m_N;
    /* debugging */
    bool m_debug;

  public:
    Init(int argc, char* argv[]);

    int    get_n()   { return m_n; }
    T get_r()   { return m_r; }
    T get_phi() { return m_phi; }

    T get_xmin() { return m_xmin; }
    T get_xmax() { return m_xmax; }
    T get_ymin() { return m_ymin; }
    T get_ymax() { return m_ymax; }
    int get_gridwidth() { return m_gridwidth; }

    int get_N() { return m_N; }

    bool get_debug() { return m_debug; }
};

#include "init.inl"

#endif /* INIT_H */
