#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include <cassert>
#include <iostream>

static void useForm(Intern &intern, Bureaucrat &boss,
                    const std::string &name, const std::string &target)
{
    AForm *form = intern.makeForm(name, target);
    assert(form != 0);
    boss.signForm(*form);
    boss.executeForm(*form);
    delete form;
}

int main()
{
    Intern intern;
    Intern copy(intern);
    copy = intern;
    Bureaucrat boss("Chefe", 1);

    useForm(intern, boss, "shrubbery creation", "jardim");
    useForm(intern, boss, "robotomy request", "Bender");
    useForm(intern, boss, "presidential pardon", "Arthur Dent");

    AForm *unknown = intern.makeForm("coffee request", "escritório");
    assert(unknown == 0);
    delete unknown;
    std::cout << "Todos os testes do ex03 passaram." << std::endl;
    return 0;
}
