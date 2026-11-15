#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP
#include <exception>
#include <iostream>
#include <string>
class Form;
class Bureaucrat { const std::string _name; int _grade; public: Bureaucrat(); Bureaucrat(const std::string&, int); Bureaucrat(const Bureaucrat&); Bureaucrat& operator=(const Bureaucrat&); ~Bureaucrat(); const std::string& getName() const; int getGrade() const; void incrementGrade(); void decrementGrade(); void signForm(Form&) const; class GradeTooHighException: public std::exception { public: virtual const char* what() const throw(); }; class GradeTooLowException: public std::exception { public: virtual const char* what() const throw(); }; };
std::ostream& operator<<(std::ostream&, const Bureaucrat&);
#endif
