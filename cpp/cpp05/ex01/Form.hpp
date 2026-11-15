#ifndef FORM_HPP
#define FORM_HPP
#include <exception>
#include <iostream>
#include <string>
class Bureaucrat;
class Form { const std::string _name; bool _signed; const int _signGrade; const int _execGrade; public: Form(); Form(const std::string&, int, int); Form(const Form&); Form& operator=(const Form&); ~Form(); const std::string& getName() const; bool getSigned() const; int getSignGrade() const; int getExecGrade() const; void beSigned(const Bureaucrat&); class GradeTooHighException: public std::exception { public: virtual const char* what() const throw(); }; class GradeTooLowException: public std::exception { public: virtual const char* what() const throw(); }; };
std::ostream& operator<<(std::ostream&, const Form&);
#endif
