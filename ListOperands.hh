//
// ListOperands.hh for ListOperands in /home/charla_n/projects/abstractVM/abstractVM
// 
// Made by nicolas charlas
// Login   <charla_n@epitech.net>
// 
// Started on  Tue Feb  5 14:36:44 2013 nicolas charlas
// Last update Mon Feb 11 17:50:36 2013 nicolas charlas
//

#ifndef LISTOPERANDS_HH_
# define LISTOPERANDS_HH_

#include <iostream>
#include <string>
#include <list>
#include "Operand.hpp"
#include "AbstractException.hpp"

class ListOperands
{
  typedef	IOperand* (ListOperands::*ptrs)(const std::string&);
  typedef	bool (ListOperands::*overunderflow)(const double&);
  ptrs				_ptrs[5];
  overunderflow			_overunderflow[5];
  std::stringstream             _stream;
  std::list<IOperand*>		_operands;

  IOperand*     createInt8(const std::string &value);
  IOperand*     createInt16(const std::string &value);
  IOperand*     createInt32(const std::string &value);
  IOperand*     createFloat(const std::string &value);
  IOperand*     createDouble(const std::string &value);

  void		getTopTwice(IOperand **, IOperand **);

public:
  ListOperands();
  ~ListOperands();

  void		push(IOperand*);
  IOperand*	pop();
  void		dump() const;
  IOperand*	top() const;
  bool		print() const;
  
  IOperand*	createOperand(eOperandType type, const std::string& value);
  void		doAdd();
  void		doMinus();
  void		doDiv();
  void		doMul();
  void		doMod();
  void		doAnd();
  void		doOr();
  void		doXor();
  void		doDecalG();
  void		doDecalD();
};

#endif
