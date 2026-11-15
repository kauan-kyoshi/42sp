#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP
#include "AForm.hpp"
class PresidentialPardonForm:public AForm{std::string _target; protected:void executeAction()const; public:PresidentialPardonForm(const std::string&);PresidentialPardonForm(const PresidentialPardonForm&);PresidentialPardonForm& operator=(const PresidentialPardonForm&);~PresidentialPardonForm();};
#endif
