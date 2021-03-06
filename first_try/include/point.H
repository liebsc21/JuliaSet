#ifndef POINT_H
#define POINT_H

#include <complex>
#include <cmath>

using namespace std;

class Point {
  private:
    const complex<double> I = {0.0,1.0};
    const complex<double> m_c;
    const int m_n;
    complex<double> m_z;
    int m_it;
  public:
    Point(const int &n, const double &r, const double &phi) : 
      m_n(n), m_c(polar(r,phi)) {}
    void set_point(const double &re, const double &im);
    complex<double> f();
    int get_it();
};

#endif /* POINT_H */
