//
// Lexer.hh for Lexer in /home/charla_n/projects/abstractVM/abstractVM
// 
// Made by nicolas charlas
// Login   <charla_n@epitech.net>
// 
// Started on  Tue Feb  5 20:43:09 2013 nicolas charlas
// Last update Fri Feb 15 18:51:01 2013 nicolas charlas
//

#ifndef LEXER_HH_
# define LEXER_HH_

#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include "AbstractException.hpp"

enum eInstructions
  {
    BEGIN_INS,
    BEGIN_IWV = 4,
    END_INS = 15,
    BEGIN_VALUE,
    END_VALUE = 20,
    OPEN_PARENTHESIS,
    CLOSE_PARENTHESIS
  };

class Lexer
{
public:
  Lexer();
  virtual ~Lexer();

  std::list<std::string> const &	getResult() const;
  std::vector<std::string>  const	getGrammar() const;

protected:
  void	getNumber(int, std::string&);
  void	getToken(std::string&);
  void	checkRemaining(const std::string &);
  void	initGrammar();
  bool	isComment(const std::string&) const;
  int	isCommentEnd(const std::string &) const;

  std::list<std::string> const &	getCheck() const;

  std::vector<std::string>	_grammar;
  std::list<std::string>	_result;
  std::list<std::string>	_check;
};

#endif
