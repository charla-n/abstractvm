#include "Overunderflow.hh"

Overunderflow::Overunderflow()
{
  _overunderflow[0] = &Overunderflow::Int8overUnderf;
  _overunderflow[1] = &Overunderflow::Int16overUnderf;
  _overunderflow[2] = &Overunderflow::Int32overUnderf;
  _overunderflow[3] = &Overunderflow::FloatoverUnderf;
  _overunderflow[4] = &Overunderflow::DoubleoverUnderf;
}

Overunderflow::~Overunderflow()
{}

bool          Overunderflow::Int8overUnderf(const double &nbrvalue)
{
  std::ostringstream svalue;

  if (((int)nbrvalue > (int)std::numeric_limits<char>::max() ||
       (int)nbrvalue < (int)std::numeric_limits<char>::min()))
    {
      svalue << nbrvalue;
      std::string exept("Overflow or Underflow detected to make");
      exept += " Int8 with " + svalue.str();
      throw AbstractException(exept);
      return (true);
    }
  return (false);
}

bool          Overunderflow::Int16overUnderf(const double &nbrvalue)
{
  std::ostringstream svalue;

  if ((nbrvalue > std::numeric_limits<short>::max() ||
       nbrvalue < std::numeric_limits<short>::min()))
    {
      svalue << nbrvalue;
      std::string exept("Overflow or Underflow detected to make");
      exept += " Int16 with " + svalue.str();
      throw AbstractException(exept);
      return (true);
    }
  return (false);
}

bool          Overunderflow::Int32overUnderf(const double &nbrvalue)
{
  std::ostringstream svalue;

  if ((nbrvalue > std::numeric_limits<int>::max() ||
       nbrvalue < std::numeric_limits<int>::min()))
    {
      svalue << nbrvalue;
      std::string exept("Overflow or Underflow detected to make");
      exept += " Int32 with " + svalue.str();
      throw AbstractException(exept);
      return (true);
    }
  return (false);
}

bool          Overunderflow::FloatoverUnderf(const double &nbrvalue)
{
  std::ostringstream svalue;

  if ( (nbrvalue > std::numeric_limits<float>::max()/2 ||
	nbrvalue < -(std::numeric_limits<float>::max()/2)) )
    {
      svalue << nbrvalue;
      std::string exept = "Overflow or Underflow detected to make";
      exept += " Float with " + svalue.str();
      throw AbstractException(exept);
      return (true);
    }
  return (false);
}


bool          Overunderflow::DoubleoverUnderf(const double &nbrvalue)
{
  std::ostringstream svalue;

  svalue << nbrvalue;
  if (nbrvalue > std::numeric_limits<double>::max()/2)
    {
      std::string exept("Overflow detected to make");
      exept += " Double with value superior of " + svalue.str();
      throw AbstractException(exept);
      return (true);
    }
  else if (nbrvalue < -(std::numeric_limits<double>::max()/2))
    {
      std::string exept("Underflow detected to make");
      exept += " Double with value inferior of " + svalue.str();
      throw AbstractException(exept);
      return (true);
    }
  return (false);
}

bool          Overunderflow::detectOverUnderFlow(eOperandType type,
                                                const double &nbrvalue)
{
  bool detect_overunderflow = (this->*_overunderflow[type])(nbrvalue);

  if (detect_overunderflow == true)
    return (true);
  return (false);
}
