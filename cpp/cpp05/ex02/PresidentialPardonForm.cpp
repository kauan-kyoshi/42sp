#include "PresidentialPardonForm.hpp"
#include <iostream>

PresidentialPardonForm::PresidentialPardonForm(const std::string &target)
    : AForm("PresidentialPardonForm", 25, 5), target(target) {}
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other)
    : AForm(other), target(other.target) {}
PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &other)
{ if (this != &other) AForm::operator=(other); return *this; }
PresidentialPardonForm::~PresidentialPardonForm() {}
const std::string &PresidentialPardonForm::getTarget() const { return target; }
void PresidentialPardonForm::executeAction() const
{ std::cout << target << " foi perdoado por Zaphod Beeblebrox." << std::endl; }
