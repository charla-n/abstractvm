//
// ListOperands.cpp for ListOperands in /home/charla_n/projects/abstractVM/abstractVM
// 
// Made by nicolas charlas
// Login   <charla_n@epitech.net>
// 
// Started on  Tue Feb  5 14:36:52 2013 nicolas charlas

//

#include <limits>
#include <stdint.h>
#include "ListOperands.hh"

ListOperands::ListOperands()
{
  _ptrs[0] = &ListOperands::createInt8;
  _ptrs[1] = &ListOperands::createInt16;
  _ptrs[2] = &ListOperands::createInt32;
  _ptrs[3] = &ListOperands::createFloat;
  _ptrs[4] = &ListOperands::createDouble;
}

ListOperands::~ListOperands()
{
  for (std::list<IOperand*>::iterator it = _operands.begin();
       it != _operands.end(); ++it)
    {
      delete *it;
      it = _operands.erase(it);
    }
}

void	ListOperands::push(IOperand *op)
{
  _operands.push_front(op);
}

IOperand*	ListOperands::pop()
{
  IOperand	*op = NULL;

  _operands.size() ? op = _operands.front() :
    throw AbstractException("Pop on empty stack");
  _operands.erase(_operands.begin());
  return (op);
}

void	ListOperands::dump() const
{
  std::cout << "Dump" << std::endl;
  for (std::list<IOperand*>::const_iterator it = _operands.begin();
       it != _operands.end(); it++)
    std::cout << (*it)->toString() << std::endl;
}

IOperand*	ListOperands::createOperand(eOperandType type,
					    const std::string &value)
{
  double		nbrvalue;
  std::istringstream	iss(value);
  IOperand		*nOperand = NULL;
  Overunderflow		*ou_flow = new Overunderflow;

  _stream.clear();
  _stream.str(value);
  iss >> nbrvalue;
  if (ou_flow->detectOverUnderFlow(type, nbrvalue) == false)
    {
      nOperand = (this->*_ptrs[type])(value);
      _operands.push_front(nOperand);
    }
  delete ou_flow;
  return (nOperand);
}

void		ListOperands::getTopTwice(IOperand **op1, IOperand **op2)
{
  *op1 = top();
  _operands.erase(_operands.begin());
  *op2 = top();
  _operands.erase(_operands.begin());
}

void		ListOperands::doAdd()
{
  IOperand	*op1;
  IOperand	*op2;

  getTopTwice(&op1, &op2);
  _operands.push_front((*op1) + (*op2));
  delete op1;
  delete op2;
}

void	ListOperands::doMinus()
{
  IOperand	*op1;
  IOperand	*op2;

  getTopTwice(&op1, &op2);
  _operands.push_front((*op2) - (*op1));
  delete op1;
  delete op2;
}

void	ListOperands::doDiv()
{
  IOperand	*op1;
  IOperand	*op2;

  getTopTwice(&op1, &op2);
  _operands.push_front((*op2) / (*op1));
  delete op1;
  delete op2;
}

void	ListOperands::doMul()
{
  IOperand	*op1;
  IOperand	*op2;

  getTopTwice(&op1, &op2);
  _operands.push_front((*op2) * (*op1));  
  delete op1;
  delete op2;
}

void	ListOperands::doMod()
{
  IOperand	*op1;
  IOperand	*op2;

  getTopTwice(&op1, &op2);
  _operands.push_front((*op2) % (*op1));  
  delete op1;
  delete op2;
}

void	ListOperands::doAnd()
{
  IOperand	*op1;
  IOperand	*op2;

  getTopTwice(&op1, &op2);
  if (op1->getType() > 2 || op2->getType() > 2)
    throw AbstractException("Cannot use & operator on double or float");
  _operands.push_front((*op2) & (*op1));  
  delete op1;
  delete op2;
}

void	ListOperands::doOr()
{
  IOperand	*op1;
  IOperand	*op2;

  getTopTwice(&op1, &op2);
  if (op1->getType() > 2 || op2->getType() > 2)
    throw AbstractException("Cannot use | operator on double or float");
  _operands.push_front((*op2) | (*op1));  
  delete op1;
  delete op2;
}

void	ListOperands::doXor()
{
  IOperand	*op1;
  IOperand	*op2;

  getTopTwice(&op1, &op2);
  if (op1->getType() > 2 || op2->getType() > 2)
    throw AbstractException("Cannot use ^ operator on double or float");
  _operands.push_front((*op2) ^ (*op1));  
  delete op1;
  delete op2;
}

void	ListOperands::doDecalG()
{
  IOperand	*op1;
  IOperand	*op2;

  getTopTwice(&op1, &op2);
  if (op1->getType() > 2 || op2->getType() > 2)
    throw AbstractException("Cannot use << operator on double or float");
  _operands.push_front((*op2) << (*op1));  
  delete op1;
  delete op2;
}

void	ListOperands::doDecalD()
{
  IOperand	*op1;
  IOperand	*op2;

  getTopTwice(&op1, &op2);
  if (op1->getType() > 2 || op2->getType() > 2)
    throw AbstractException("Cannot use >> operator on double or float");
  _operands.push_front((*op2) >> (*op1));  
  delete op1;
  delete op2;
}

bool		ListOperands::print() const
{
  std::istringstream	stream;
  int16_t		v;

  if (!_operands.size())
    throw AbstractException("Stack is empty");
  if ((*_operands.begin())->getType() == Int8)
    {
      stream.str((*_operands.begin())->toString());
      stream >> v;
      std::cout << (char)v << std::endl;
      return (true);
    }
  throw AbstractException("Value at the top is not type of Int8");
  return (false);
}

IOperand*               ListOperands::createInt8(const std::string&)
{
  int16_t               int8;

  _stream >> int8;
  return (new Operand<int16_t>(int8, Int8));
}

IOperand*     ListOperands::createInt16(const std::string &)
{
  int16_t               int16;

  _stream >> int16;
  return (new Operand<int16_t>(int16, Int16));
}

IOperand*     ListOperands::createInt32(const std::string &)
{
  int32_t               int32;

  _stream >> int32;
  return (new Operand<int32_t>(int32, Int32));
}

IOperand*     ListOperands::createFloat(const std::string &)
{
  float         f;

  _stream >> f;
  return (new Operand<float>(f, Float));
}

IOperand*     ListOperands::createDouble(const std::string &)
{
  double        d;

  _stream >> d;
  return (new Operand<double>(d, Double));
}

IOperand*	ListOperands::top() const
{
  if (!_operands.size())
    throw AbstractException("Cannot top on empty stack");
  return (*(_operands.begin()));
}
