//
// AbstractVM.hh for AbstractVM in /home/charla_n/projects/abstractVM/abstractVM
// 
// Made by nicolas charlas
// Login   <charla_n@epitech.net>
// 
// Started on  Wed Feb  6 13:12:17 2013 nicolas charlas
// Last update Fri Feb 15 17:23:26 2013 nicolas charlas
//

#ifndef ABSTRACTVM_HH_
# define ABSTRACTVM_HH_

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include "Parser.hh"
#include "ListOperands.hh"

class AbstractVM
{
  typedef void (ListOperands::*ptrs)();
  std::vector<ptrs>	_ptrFuncsOps;
  ListOperands		_ops;
  Parser		_parser;

  void	doInstructionValues(std::list<std::string>::const_iterator&,
			    std::vector<std::string> const);
  void	doInstructionChecks(std::list<std::string>::const_iterator&,
                            std::vector<std::string> const );
  void	interpret(const std::list<std::string>&,
		  std::vector<std::string> const );
  bool	isExit(const std::string &);

public:
  AbstractVM();
  ~AbstractVM();

  void	run(std::ifstream&);
  void	run(std::string&);
};

bool	found_colon(std::string const line);

#endif
