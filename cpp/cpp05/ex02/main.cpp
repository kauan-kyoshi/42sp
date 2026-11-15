#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include <cassert>
#include <iostream>

int main()
{
    Bureaucrat boss("Chefe", 1);
    Bureaucrat junior("Júnior", 150);
    ShrubberyCreationForm shrubbery("casa");
    RobotomyRequestForm robotomy("Bender");
    PresidentialPardonForm pardon("Arthur Dent");

    boss.executeForm(shrubbery);
    junior.signForm(shrubbery);
    assert(!shrubbery.getSignedStatus());
    boss.signForm(shrubbery);
    boss.executeForm(shrubbery);

    boss.signForm(robotomy);
    junior.executeForm(robotomy);
    boss.executeForm(robotomy);

    boss.signForm(pardon);
    boss.executeForm(pardon);

    assert(shrubbery.getGradeToSign() == 145 && shrubbery.getGradeToExecute() == 137);
    assert(robotomy.getGradeToSign() == 72 && robotomy.getGradeToExecute() == 45);
    assert(pardon.getGradeToSign() == 25 && pardon.getGradeToExecute() == 5);
    std::cout << "Todos os testes do ex02 passaram." << std::endl;
    return 0;
}
