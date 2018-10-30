#include <iostream>

#include "point.H"

void Point::set_point(const double &re, const double &im){
  m_z  = {re,im};
//    cout << "z = " << m_z << "\n";
  m_it = 0;
}

complex<double> Point::f(){
  m_it++;
  m_z = pow(m_z,m_n) + m_r*exp(I*m_phi);
}

int Point::get_it(){
  while(abs(m_z)<=2 && m_it<=300) {
//    cout << "z = " << m_z << "\n";
//    cout << "|z| = " << abs(m_z) << "\n";
    f();
//    cout << "Number of iterations = " << m_it << "\n" ;
  }
  return m_it;
}
