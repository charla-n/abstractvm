//
// AbstractException.hh for AbstractException in /home/charla_n/projects/abstractVM/abstractVM
// 
// Made by nicolas charlas
// Login   <charla_n@epitech.net>
// 
// Started on  Wed Feb  6 15:24:08 2013 nicolas charlas

//

#ifndef ABSTRACTEXCPETION_HH_
# define ABSTRACTEXCPETION_HH_

class AbstractException : public std::exception
{
  std::string	_msg;

public:
  AbstractException(const std::string &msg)
  {
    _msg = msg;
  }
  virtual ~AbstractException() throw() {};

  virtual const char*	what() const throw()
  {
    return (_msg.c_str());
  }
};

#endif
