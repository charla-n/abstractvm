//
// AbstractVM.cpp for AbstractVM in /home/charla_n/projects/abstractVM/abstractVM
// 
// Made by nicolas charlas
// Login   <charla_n@epitech.net>
// 
// Started on  Wed Feb  6 13:12:30 2013 nicolas charlas

//

#include <limits>
#include "AbstractVM.hh"

AbstractVM::AbstractVM()
{
  _ptrFuncsOps.push_back(&ListOperands::doAdd);
  _ptrFuncsOps.push_back(&ListOperands::doMinus);
  _ptrFuncsOps.push_back(&ListOperands::doMul);
  _ptrFuncsOps.push_back(&ListOperands::doDiv);
  _ptrFuncsOps.push_back(&ListOperands::doMod);
  _ptrFuncsOps.push_back(&ListOperands::doAnd);
  _ptrFuncsOps.push_back(&ListOperands::doOr);
  _ptrFuncsOps.push_back(&ListOperands::doXor);
  _ptrFuncsOps.push_back(&ListOperands::doDecalG);
  _ptrFuncsOps.push_back(&ListOperands::doDecalD);
  _ptrFuncsOps.push_back(NULL);
  _ptrFuncsOps.push_back(NULL);
}

AbstractVM::~AbstractVM()
{
}

bool	AbstractVM::isExit(const std::string &str)
{
  int	position;

  position = str.find("exit");
  if (position != -1 && position != str.length())
    {
      for (int i = 0; i < position; i++)
	if (str[i] != ' ' && str[i] != '\t')
	  return (false);
      for (int i = position + 4; i < str.length(); i++)
	{
	  if (str[i] == ';')
	    return (true);
	  if (str[i] != ' ' && str[i] != '\t')
	    return (false);
	}
      return (true);
    }
  return (false);
}

void	AbstractVM::run(std::ifstream &input)
{
  std::string	line;
  bool		exit_present = false;
  int		numLine = 0;

  try
    {
      while (getline(input, line))
	{
	  if (isExit(line))
	    exit_present = true;
	  else
	    _parser.parseStr(line);
	  numLine++;
	}
      interpret(_parser.getResult(), _parser.getGrammar());
      if (exit_present == false)
	throw AbstractException("Exit is not present at the end !");
    }
  catch (AbstractException &e)
    {
      std::cout << "Line " << numLine + 1 << " : " << e.what() << std::endl;
    }
}

void	AbstractVM::run(std::string &str)
{
  static bool	exit_present = false;

  if (found_colon(str) == true && exit_present == false)
    throw AbstractException("Exit is not present at the end !");
  if (isExit(str))
    exit_present = true;
  else if (found_colon(str) == false)
    _parser.parseStr(str);
  else if (_parser.getResult().size())
    {
      std::cout << "================= RES =================" << std::endl;
      interpret(_parser.getResult(), _parser.getGrammar());
    }
}

void	AbstractVM::doInstructionValues(std::list<std::string>::const_iterator
					&it,
					std::vector<std::string> const grammar)
{
  if ((*it) == "pop")
    delete _ops.pop();
  else if ((*it) == "push")
    {
      ++it;
      for (int i = BEGIN_VALUE; i <= END_VALUE; i++)
	{
	  if (grammar[i] == *it)
	    {
	      ++it;
	      _ops.createOperand((eOperandType)(i - BEGIN_VALUE),
				 *it);
	      return ;
	    }
	}
    }
}

void	AbstractVM::doInstructionChecks(std::list<std::string>::const_iterator
                                        &it,
					std::vector<std::string> const grammar)
{
  bool	find = false;

  if (*it == "print")
    _ops.print();
  else
    {
      ++it;
      for (int i = BEGIN_VALUE; i <= END_VALUE; i++)
	{
	  if (grammar[i] == *it && (i - BEGIN_VALUE) == _ops.top()->getType())
	    {
	      find = true;
	      break;
	    }
	}
      if (!find)
	throw AbstractException("Not the same type at the top");
      ++it;
      if (_ops.top()->toString() != (*it))
	throw AbstractException("Not the same value at the top");
    }
}

void	AbstractVM::interpret(const std::list<std::string> &result,
			      std::vector<std::string> const grammar)
{
  std::list<std::string>::const_iterator	it = result.begin();

  while (it != result.end())
    {
      if ((*it) == "push" || (*it) == "pop")
	doInstructionValues(it, grammar);
      else if ((*it) == "assert" || (*it) == "print")
	doInstructionChecks(it, grammar);
      else
	{
	  if (*it == "dump")
	    _ops.dump();
	  else
	    for (int i = BEGIN_IWV; i <= END_INS; i++)
	      if ((*it) == grammar[i] && _ptrFuncsOps[i - BEGIN_IWV])
		(_ops.*_ptrFuncsOps[i - BEGIN_IWV])();
	}
      ++it;
    }
}
