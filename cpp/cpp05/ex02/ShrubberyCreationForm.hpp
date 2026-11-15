#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP
#include "AForm.hpp"
class ShrubberyCreationForm:public AForm{std::string _target; protected:void executeAction()const; public:ShrubberyCreationForm(const std::string&);ShrubberyCreationForm(const ShrubberyCreationForm&);ShrubberyCreationForm& operator=(const ShrubberyCreationForm&);~ShrubberyCreationForm();};
#endif
