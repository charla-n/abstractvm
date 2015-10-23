//
// Lexer.cpp for lexer. in /home/jansen_a//svn/abstractvm
// 
// Made by arthur jansen
// Login   <jansen_a@epitech.net>
// 
// Started on  Mon Feb 11 17:22:55 2013 arthur jansen
// Last update Fri Feb 15 20:02:59 2013 nicolas charlas
//

#include "Lexer.hh"

void	Lexer::initGrammar()
{
  _grammar.push_back("push");
  _grammar.push_back("pop");
  _grammar.push_back("assert");
  _grammar.push_back("dump");
  _grammar.push_back("add");
  _grammar.push_back("sub");
  _grammar.push_back("mul");
  _grammar.push_back("div");
  _grammar.push_back("mod");
  _grammar.push_back("and");
  _grammar.push_back("or");
  _grammar.push_back("xor");
  _grammar.push_back("decalG");
  _grammar.push_back("decalD");
  _grammar.push_back("print");
  _grammar.push_back("exit");
  _grammar.push_back("int8");
  _grammar.push_back("int16");
  _grammar.push_back("int32");
  _grammar.push_back("float");
  _grammar.push_back("double");
  _grammar.push_back("(");
  _grammar.push_back(")");
}

Lexer::Lexer()
{
  initGrammar();
}

Lexer::~Lexer(){}

void		Lexer::getNumber(int position, std::string &line)
{
  int		begin = -1;
  int		end = -1;
  bool		hasPoint = false;

  if ((line[position + 1] >= '0' && line[position + 1] <= '9') ||
      line[position + 1] == '-')
    {
      begin = position + 1;
      end = position + 1;
      position += 2;
      for (; (line[position] && line[position] >= '0' &&
	      line[position] <= '9') || line[position] == '.';
	   position++ && end++);
      {
	if (line[position] == '.' && hasPoint == false)
	  hasPoint = true;
	else if (line[position] == '.' && hasPoint)
	  throw AbstractException("Number bad written");
	_check.push_back(line.substr(begin, end - begin + 1));
      }
      line.erase(begin, end - begin + 1);
    }
}

bool		Lexer::isComment(const std::string &str) const
{
  int		i;

  for (i = 0; str[i] && (str[i] == ' ' || str[i] == '\t'); i++);
  if (str[i] == ';')
    return (true);
  return (false);
}

int		Lexer::isCommentEnd(const std::string &str) const
{
  int		i;

  i = str.find(";");
  if (i == -1 || i == str.length())
    return (-1);
  return (i);
}

void		Lexer::getToken(std::string &line)
{  
  int		previousPos = -1;
  int		grammarPos = -1;
  int		posFind;
  int		positionComment;

  _check.clear();
  if (isComment(line))
    return ;
  if ((positionComment = isCommentEnd(line)) == -1)
    positionComment = line.length();
  line = line.substr(0, positionComment);
  do
    {
      grammarPos = -1;
      for (unsigned int i = 0; i < _grammar.size(); i++)
	{
	  posFind = line.find(_grammar[i].c_str());
	  if (posFind != -1 && (posFind < previousPos || previousPos == -1))
	    {
	      previousPos = posFind;
	      grammarPos = i;
	    }
	}
      if (grammarPos != -1)
	{
	  _check.push_back(_grammar[grammarPos]);
	  if (_grammar[grammarPos] == "(")
	    getNumber(previousPos, line);
	  line = line.erase(previousPos,
			    _grammar[grammarPos].length());
	  positionComment -= _grammar[grammarPos].length();
	  if ((_grammar[grammarPos] == "assert"
	       || _grammar[grammarPos] == "push") && (line[0] != ' ' &&
						      line[0] != '\t'))
	    throw AbstractException("missing space after " +
				    _grammar[grammarPos]);
	  previousPos = -1;
	}
    } while (grammarPos != -1 && line.length());
  checkRemaining(line);
}

void		Lexer::checkRemaining(const std::string &remain)
{
  for (int i = 0; remain[i]; i++)
    {
      if (remain[i] == ';')
	break;
      if (remain[i] != ' ' && remain[i] != '\t')
	throw AbstractException("Instruction was not written properly");
    }
}

std::list<std::string> const &	Lexer::getResult() const
{
  return (_result);
}

std::vector<std::string> const	Lexer::getGrammar() const
{
  return (_grammar);
}

std::list<std::string> const &	Lexer::getCheck() const
{
  return (_check);
}
