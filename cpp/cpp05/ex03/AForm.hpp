#ifndef AFORM_HPP
#define AFORM_HPP
#include <exception>
#include <iostream>
#include <string>
class Bureaucrat;
class AForm { const std::string _name; bool _signed; const int _signGrade; const int _execGrade; protected: virtual void executeAction()const=0; public: AForm(const std::string&,int,int); AForm(const AForm&); AForm& operator=(const AForm&); virtual ~AForm(); const std::string& getName()const; bool getSigned()const; int getSignGrade()const; int getExecGrade()const; void beSigned(const Bureaucrat&); void execute(const Bureaucrat&)const; class GradeTooHighException:public std::exception{public:virtual const char* what()const throw();};class GradeTooLowException:public std::exception{public:virtual const char* what()const throw();};class FormNotSignedException:public std::exception{public:virtual const char* what()const throw();};};
std::ostream& operator<<(std::ostream&,const AForm&);
#endif
