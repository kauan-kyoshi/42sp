#include "Intern.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include <iostream>

typedef AForm *(*FormCreator)(const std::string &target);

static AForm *createShrubbery(const std::string &target)
{ return new ShrubberyCreationForm(target); }

static AForm *createRobotomy(const std::string &target)
{ return new RobotomyRequestForm(target); }

static AForm *createPardon(const std::string &target)
{ return new PresidentialPardonForm(target); }

Intern::Intern() {}
Intern::Intern(const Intern &other) { (void)other; }
Intern &Intern::operator=(const Intern &other)
{ (void)other; return *this; }
Intern::~Intern() {}

AForm *Intern::makeForm(const std::string &name, const std::string &target) const
{
    const std::string names[3] = {
        "shrubbery creation", "robotomy request", "presidential pardon"
    };
    FormCreator creators[3] = {
        createShrubbery, createRobotomy, createPardon
    };

    for (int index = 0; index < 3; ++index)
    {
        if (name == names[index])
        {
            AForm *form = creators[index](target);
            std::cout << "Intern cria " << name << std::endl;
            return form;
        }
    }
    std::cerr << "Intern não pode criar " << name << ": "
              << UnknownFormException().what() << "." << std::endl;
    return 0;
}

const char *Intern::UnknownFormException::what() const throw()
{ return "formulário desconhecido"; }
