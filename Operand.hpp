//
// Operand.hpp for Operand in /home/charla_n/projects/abstractVM/abstractVM
// 
// Made by nicolas charlas
// Login   <charla_n@epitech.net>
// 
// Started on  Mon Feb  4 19:38:23 2013 nicolas charlas
// Last update Fri Feb 15 16:04:06 2013 nicolas charlas
//

#ifndef OPERAND_HPP_
# define OPERAND_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <stdint.h>
#include "IOperand.hh"
#include "AbstractException.hpp"
#include "Overunderflow.hh"

template<typename T>
class Operand : public IOperand
{
  eOperandType		_type;
  std::string		_string;

public:
  Operand(const T &value, const eOperandType type) :
    _type(type)
  {
    std::ostringstream	stream;

    stream << value;
    _string = stream.str();
  }

  virtual ~Operand(){}

  Operand(const IOperand &op, double value)
  {
    std::ostringstream	stream;

    stream << value;
    _string = stream.str();
    _type = op.getType();
  }

  virtual std::string const	&toString() const
  {
    return (_string);
  }

  virtual int			getPrecision() const
  {
    return (_type);
  }

  virtual eOperandType		getType() const
  {
    return (_type);
  }

  virtual IOperand*		operator+(const IOperand &rhs) const
  {
    IOperand		*op = NULL;
    double		v1;
    double		v2;
    std::istringstream	stream;
    Overunderflow *ou_flow = new Overunderflow;    

    stream.str(rhs.toString());
    stream >> v1;
    stream.clear();
    stream.str(toString());
    stream >> v2;
    if (rhs.getType() > _type)
      {
	if (ou_flow->detectOverUnderFlow(rhs.getType(), v1 + v2) == false)
	  op = new Operand(rhs, v1 + v2);
      }
    else
      {
	if (ou_flow->detectOverUnderFlow(this->getType(), v1 + v2) == false)
	  op = new Operand(*this, v1 + v2);
      }
    delete ou_flow;
    return (op);
  }

  virtual IOperand*		operator-(const IOperand &rhs) const
  {
    IOperand		*op = NULL;
    double		v1;
    double		v2;
    std::istringstream	stream;
    Overunderflow *ou_flow = new Overunderflow;

    stream.str(rhs.toString());
    stream >> v1;
    stream.clear();
    stream.str(toString());
    stream >> v2;
    if (rhs.getType() > _type)
      {
	if (ou_flow->detectOverUnderFlow(rhs.getType(), v1 - v2) == false)
	  op = new Operand(rhs, v1 - v2);
      }
    else
      {
	if (ou_flow->detectOverUnderFlow(this->getType(), v1 - v2) == false)
	  op = new Operand(*this, v1 - v2);
      }
    delete ou_flow;
    return (op);
  }

  virtual IOperand*		operator/(const IOperand &rhs) const
  {
    IOperand		*op = NULL;
    double		v1;
    double		v2;
    std::istringstream	stream;
    Overunderflow *	ou_flow = new Overunderflow;
    
    stream.str(rhs.toString());
    stream >> v1;
    stream.clear();
    stream.str(toString());
    stream >> v2;
    if (!v2)
      throw AbstractException("Division by zero");
    if (rhs.getType() > _type)
      {
	if (ou_flow->detectOverUnderFlow(rhs.getType(), v1 / v2) == false)
	  op = new Operand(rhs, v1 / v2);
      }
    else
      {
	if (ou_flow->detectOverUnderFlow(this->getType(), v1 / v2) == false)
	  op = new Operand(*this, v1 / v2);
      }
    delete ou_flow;
    return (op);
  }

  virtual IOperand*		operator*(const IOperand &rhs) const
  {
    IOperand		*op = NULL;
    double		v1;
    double		v2;
    std::istringstream	stream;
    Overunderflow *	ou_flow = new Overunderflow;    

    stream.str(rhs.toString());
    stream >> v1;
    stream.clear();
    stream.str(toString());
    stream >> v2;
    if (rhs.getType() > _type)
      {
	if (ou_flow->detectOverUnderFlow(rhs.getType(), v1 * v2) == false)
	  op = new Operand(rhs, v1 * v2);
      }
    else
      {
	if (ou_flow->detectOverUnderFlow(this->getType(), v1 * v2) == false)
	  op = new Operand(*this, v1 * v2);
      }
    delete ou_flow;
    return (op);
  }

  virtual IOperand*		operator%(const IOperand &rhs) const
  {
    IOperand		*op = NULL;
    double		v1;
    double		v2;
    std::istringstream	stream;
    Overunderflow *	ou_flow = new Overunderflow;    

    stream.str(rhs.toString());
    stream >> v1;
    stream.clear();
    stream.str(toString());
    stream >> v2;
    if (!v2)
      throw AbstractException("Modulo by zero");
    if (rhs.getType() > _type)
      {
	if (ou_flow->detectOverUnderFlow(rhs.getType(), fmod(v1,v2)) == false)
	  op = new Operand(rhs, fmod(v1, v2));
      }
    else
      {
	if (ou_flow->detectOverUnderFlow(this->getType(), fmod(v1,v2))== false)
	  op = new Operand(*this, fmod(v1, v2));
      }
    delete ou_flow;
    return (op);
  }  

  virtual IOperand*		operator&(const IOperand &rhs) const
  {
    IOperand		*op = NULL;
    int32_t		v1;
    int32_t		v2;
    std::istringstream	stream;
    Overunderflow *	ou_flow = new Overunderflow;

    stream.str(rhs.toString());
    stream >> v1;
    stream.clear();
    stream.str(toString());
    stream >> v2;
    if (rhs.getType() > _type)
      {
	if (ou_flow->detectOverUnderFlow(rhs.getType(), v1 & v2) == false)
	  op = new Operand(rhs, v1 & v2);
      }
    else
      {
	if (ou_flow->detectOverUnderFlow(this->getType(), v1 & v2)== false)
	  op = new Operand(*this, v1 & v2);
      }
    delete ou_flow;
    return (op);
  }

  virtual IOperand*		operator|(const IOperand &rhs) const
  {
    IOperand		*op = NULL;
    int32_t		v1;
    int32_t		v2;
    std::istringstream	stream;
    Overunderflow *	ou_flow = new Overunderflow;    

    stream.str(rhs.toString());
    stream >> v1;
    stream.clear();
    stream.str(toString());
    stream >> v2;
    if (rhs.getType() > _type)
      {
	if (ou_flow->detectOverUnderFlow(rhs.getType(), v1 | v2) == false)
	  op = new Operand(rhs, v1 | v2);
      }
    else
      {
	if (ou_flow->detectOverUnderFlow(this->getType(), v1 | v2)== false)
	  op = new Operand(*this, v1 | v2);
      }
    delete ou_flow;
    return (op);
  }

  virtual IOperand*		operator^(const IOperand &rhs) const
  {
    IOperand		*op = NULL;
    int32_t		v1;
    int32_t		v2;
    std::istringstream	stream;
    Overunderflow *	ou_flow = new Overunderflow;

    stream.str(rhs.toString());
    stream >> v1;
    stream.clear();
    stream.str(toString());
    stream >> v2;
    if (rhs.getType() > _type)
      {
	if (ou_flow->detectOverUnderFlow(rhs.getType(), v1 ^ v2) == false)
	  op = new Operand(rhs, v1 ^ v2);
      }
    else
      {
	if (ou_flow->detectOverUnderFlow(this->getType(), v1 ^ v2)== false)
	  op = new Operand(*this, v1 ^ v2);
      }
    delete ou_flow;
    return (op);
  }

  virtual IOperand*		operator<<(const IOperand &rhs) const
  {
    IOperand		*op = NULL;
    int32_t		v1;
    int32_t		v2;
    std::istringstream	stream;
    Overunderflow *	ou_flow = new Overunderflow;
    
    stream.str(rhs.toString());
    stream >> v1;
    stream.clear();
    stream.str(toString());
    stream >> v2;
    if (rhs.getType() > _type)
      {
	if (ou_flow->detectOverUnderFlow(rhs.getType(), v1 << v2) == false)
	  op = new Operand(rhs, v1 << v2);
      }
    else
      {
	if (ou_flow->detectOverUnderFlow(this->getType(), v1 << v2)== false)
	  op = new Operand(*this, v1 << v2);
      }
    delete ou_flow;
    return (op);
  }

  virtual IOperand*		operator>>(const IOperand &rhs) const
  {
    IOperand		*op = NULL;
    int32_t		v1;
    int32_t		v2;
    std::istringstream	stream;
    Overunderflow *	ou_flow = new Overunderflow;    

    stream.str(rhs.toString());
    stream >> v1;
    stream.clear();
    stream.str(toString());
    stream >> v2;
    if (rhs.getType() > _type)
      {
	if (ou_flow->detectOverUnderFlow(rhs.getType(), v1 >> v2) == false)
	  op = new Operand(rhs, v1 >> v2);
      }
    else
      {
	if (ou_flow->detectOverUnderFlow(this->getType(), v1 >> v2)== false)
	  op = new Operand(*this, v1 >> v2);
      }
    delete ou_flow;
    return (op);
  }
};

#endif
