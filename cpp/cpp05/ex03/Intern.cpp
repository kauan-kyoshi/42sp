#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
typedef AForm* (*FormMaker)(const std::string&);
static AForm* makeShrubbery(const std::string&t){return new ShrubberyCreationForm(t);} static AForm* makeRobotomy(const std::string&t){return new RobotomyRequestForm(t);} static AForm* makePardon(const std::string&t){return new PresidentialPardonForm(t);}
Intern::Intern(){}Intern::Intern(const Intern&){}Intern&Intern::operator=(const Intern&){return *this;}Intern::~Intern(){}AForm*Intern::makeForm(const std::string&name,const std::string&target)const{const std::string names[3]={"shrubbery creation","robotomy request","presidential pardon"};FormMaker makers[3]={makeShrubbery,makeRobotomy,makePardon};for(int i=0;i<3;++i)if(name==names[i]){std::cout<<"Intern creates "<<name<<std::endl;return makers[i](target);}std::cerr<<"Intern cannot create unknown form: "<<name<<std::endl;return 0;}
