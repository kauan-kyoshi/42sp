#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
    : AForm("ShrubberyCreationForm", 145, 137), target(target) {}
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
    : AForm(other), target(other.target) {}
ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{ if (this != &other) AForm::operator=(other); return *this; }
ShrubberyCreationForm::~ShrubberyCreationForm() {}
const std::string &ShrubberyCreationForm::getTarget() const { return target; }

void ShrubberyCreationForm::executeAction() const
{
    std::ofstream file((target + "_shrubbery").c_str());
    if (!file)
        throw FileCreationException();
    file << "       _-_-_\n"
         << "    /~~     ~~\\\n"
         << " /~~           ~~\\\n"
         << "{                 }\n"
         << " \\  _-     -_  /\n"
         << "   ~  \\ //  ~\n"
         << "_- -   | | _- _\n"
         << "  _ -  | |   -_\n"
         << "      // \\\\\n";
    if (!file)
        throw FileCreationException();
}

const char *ShrubberyCreationForm::FileCreationException::what() const throw()
{ return "não foi possível criar o arquivo de arbustos"; }
