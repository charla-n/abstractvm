//
// IOperand.hh for IOperand in /home/charla_n/projects/abstractVM/abstractVM
// 
// Made by nicolas charlas
// Login   <charla_n@epitech.net>
// 
// Started on  Mon Feb  4 19:32:43 2013 nicolas charlas
// Last update Mon Feb 11 17:51:58 2013 nicolas charlas
//

#ifndef IOPERAND_HH_
# define IOPERAND_HH_

enum  eOperandType
  {
    Int8,
    Int16,
    Int32,
    Float,
    Double
  };

class IOperand
{
public:
  virtual std::string const	&toString() const = 0;
  virtual int			getPrecision() const = 0;
  virtual eOperandType		getType() const = 0;

  virtual IOperand*		operator+(const IOperand &rhs) const = 0;
  virtual IOperand*		operator-(const IOperand &rhs) const = 0;
  virtual IOperand*		operator/(const IOperand &rhs) const = 0;
  virtual IOperand*		operator*(const IOperand &rhs) const = 0;
  virtual IOperand*		operator%(const IOperand &rhs) const = 0;
  virtual IOperand*		operator&(const IOperand &rhs) const = 0;
  virtual IOperand*		operator|(const IOperand &rhs) const = 0;
  virtual IOperand*		operator^(const IOperand &rhs) const = 0;
  virtual IOperand*		operator<<(const IOperand &rhs) const = 0;
  virtual IOperand*		operator>>(const IOperand &rhs) const = 0;

  virtual ~IOperand() {}
};

#endif
