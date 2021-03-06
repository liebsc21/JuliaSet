#include <iostream>

#include "point.H"

void Point::set_point(const double &re, const double &im){
  m_z  = {re,im};
  m_it = 0;
}

complex<double> Point::f(){
  m_it++;
  m_z = pow(m_z,m_n) + m_c;
}

int Point::get_it(){
  while(abs(m_z)<=2 && m_it<=300) {
    f();
  }
  return m_it;
}
