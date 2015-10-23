#include <string>
#include <limits>
#include <sstream>
#include <iostream>
#include <stdint.h>
#include "AbstractException.hpp"
#include "IOperand.hh"

class Overunderflow
{
  typedef       bool (Overunderflow::*overunderflow)(const double&);
  overunderflow                 _overunderflow[5];

public:
  Overunderflow();
  ~Overunderflow();
  bool	Int8overUnderf(const double &);
  bool	Int16overUnderf(const double &);
  bool	Int32overUnderf(const double &);
  bool	FloatoverUnderf(const double &);
  bool	DoubleoverUnderf(const double &);
  bool	detectOverUnderFlow(eOperandType , const double &);
};
