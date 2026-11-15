#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP
#include "AForm.hpp"
class RobotomyRequestForm : public AForm
{
private:
    const std::string target;
    virtual void executeAction() const;
public:
    RobotomyRequestForm(const std::string &target);
    RobotomyRequestForm(const RobotomyRequestForm &other);
    RobotomyRequestForm &operator=(const RobotomyRequestForm &other);
    virtual ~RobotomyRequestForm();
    const std::string &getTarget() const;
};
#endif
