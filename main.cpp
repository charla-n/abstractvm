#include <fstream>
#include <iostream>
#include "Operand.hpp"
#include "ListOperands.hh"
#include "Lexer.hh"
#include "AbstractException.hpp"
#include "AbstractVM.hh"

bool	found_colon(std::string const line)
{
  int		fpos = line.find(";;");

  if (fpos == -1 || fpos == line.length())
    return false;

  for (int i = 0; i<fpos; ++i)
    {
      if (line[i] != ' ' && line[i] != '\t')
	return (false);
    }

  for (int i = line.length()-1; i>fpos+1; --i)
    {
      if (line[i] != ' ' && line[i] != '\t')
	return (false);
    }
  return true;
}

int		main(int, char **av)
{
  AbstractVM	vm;
  std::ifstream	input;
  std::string	line;
  int		numLine = 0;

  if (av[1])
    {
      input.open(av[1]);
      vm.run(input);
    }
  else
    {
      try
  	{
	  std::cout << "========= TYPE YOUR COMMANDS ==========" << std::endl;
  	  while (getline(std::cin, line))
  	    {
	      vm.run(line);
  	      if (found_colon(line) == true)
		break;
  	      numLine++;
  	    }
  	}
      catch (AbstractException &e)
  	{
  	  std::cout << "Line " << numLine + 1
		    << " : " << e.what() << std::endl;
  	}
    }
}
