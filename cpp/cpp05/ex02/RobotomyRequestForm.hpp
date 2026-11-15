#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP
#include "AForm.hpp"
class RobotomyRequestForm:public AForm{std::string _target; protected:void executeAction()const; public:RobotomyRequestForm(const std::string&);RobotomyRequestForm(const RobotomyRequestForm&);RobotomyRequestForm& operator=(const RobotomyRequestForm&);~RobotomyRequestForm();};
#endif
