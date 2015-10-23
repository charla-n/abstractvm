//
// Parser.cpp for Parser in /home/charla_n/projects/abstractVM/abstractVM
// 
// Made by nicolas charlas
// Login   <charla_n@epitech.net>
// 
// Started on  Tue Feb  5 20:37:52 2013 nicolas charlas

//

#include "Parser.hh"

Parser::Parser() : Lexer()
{
  _needValue = "push|assert";
}

Parser::~Parser(){}

int		Parser::checkInstruction(const std::string &ins) const
{
  int		rFind;

  for (unsigned int i = BEGIN_INS; i <= END_INS; i++)
    {
      rFind = _needValue.find(ins);
      if (ins == _grammar[i] &&
	  (rFind == -1 || rFind == (int)_grammar[i].length()))
	return (0);
      else if (ins == _grammar[i] &&
	       rFind != -1 && rFind != (int)_grammar[i].length())
	return (1);
    }
  return (-1);
}

bool	Parser::checkValue(const std::string &value) const
{
  for (int i = BEGIN_VALUE; i <= END_VALUE; i++)
    if (value == _grammar[i])
      return (true);
  return (false);
}

bool	Parser::checkNumber(const std::string &numb) const
{
  int	i;

  numb[0] == '-' ? i = 1 : i = 0;
  for (; (numb[i] && numb[i] >= '0' && numb[i] <= '9') ||
	 (numb[i] && numb[i] == '.'); i++);
  return ((!numb[i]) ? true : false);
}

void	Parser::checkValidity()
{
  int					rIns;
  std::list<std::string>::iterator	it = _check.begin();

  rIns = checkInstruction(*it);
  if (rIns == -1)
    throw AbstractException("Bad instruction");
  if (!rIns && it != _check.end())
    {
      ++it;
      if (it != _check.end())
	throw AbstractException("Instruction was not written properly 1");
    }
  else if (*it == "push" || *it == "assert")
    {
      ++it;
      !checkValue(*it) ? throw AbstractException("Bad value given") :
	++it;
      _grammar[OPEN_PARENTHESIS] != (*it) ?
	throw AbstractException("No open parenthesis") :
	it = _result.erase(it);
      !checkNumber(*it) ? throw AbstractException("Bad number") :
	++it;
      _grammar[CLOSE_PARENTHESIS] != (*it) ?
	throw AbstractException("No closed parenthesis") :
	it = _result.erase(it);
      if (it != _check.end())
	throw AbstractException("Instruction was not written properly 2");
    }
  for (it = _check.begin(); it != _check.end(); it++)
    _result.push_back(*it);
}

void	Parser::parseStr(std::string &str)
{
  getToken(str);
  if (_check.size())
    checkValidity();
}
