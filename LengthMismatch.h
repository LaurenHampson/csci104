#ifndef LENGTHMISMATCH_H
#define LENGTHMISMATCH_H

#include<exception>
#include <string>


// at the top, add the following include
#include <stdexcept>

// after all includes, add this
class LengthMismatch : public std::exception 
{
public:
  LengthMismatch(int x, int y); //throw();
 
  virtual const char* what() const throw()
  {
    return msg.c_str(); 
  }
 ~LengthMismatch() throw() {}
private:
  std::string msg;
};

#endif