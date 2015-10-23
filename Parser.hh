//
// Parser.hh for Parser in /home/charla_n/projects/abstractVM/abstractVM
// 
// Made by nicolas charlas
// Login   <charla_n@epitech.net>
// 
// Started on  Tue Feb  5 20:28:04 2013 nicolas charlas
// Last update Mon Feb 11 15:38:44 2013 nicolas charlas
//

#ifndef PARSER_HH_
# define PARSER_HH_

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "Lexer.hh"
#include "AbstractException.hpp"

class Parser : public Lexer
{
  std::string	_needValue;

  void	checkValidity();
  int	checkInstruction(const std::string &) const;
  bool	checkValue(const std::string &) const;
  bool	checkNumber(const std::string &) const;
public:
  Parser();
  virtual ~Parser();

  void	parseStr(std::string &);
};

#endif
