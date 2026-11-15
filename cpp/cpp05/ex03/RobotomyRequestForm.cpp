#include "RobotomyRequestForm.hpp"
#include <cstdlib>
#include <iostream>

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
    : AForm("RobotomyRequestForm", 72, 45), target(target) {}
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other)
    : AForm(other), target(other.target) {}
RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{ if (this != &other) AForm::operator=(other); return *this; }
RobotomyRequestForm::~RobotomyRequestForm() {}
const std::string &RobotomyRequestForm::getTarget() const { return target; }
void RobotomyRequestForm::executeAction() const
{
    std::cout << "BZZZZZZ... VRRRRRR..." << std::endl;
    if (std::rand() % 2)
        std::cout << target << " foi robotomizado com sucesso." << std::endl;
    else
        std::cout << "A robotomia de " << target << " falhou." << std::endl;
}
