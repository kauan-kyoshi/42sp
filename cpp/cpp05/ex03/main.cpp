#include "Intern.hpp"
#include "Bureaucrat.hpp"
#include "AForm.hpp"
int main(){Intern intern;Bureaucrat boss("Boss",1);AForm* form=intern.makeForm("robotomy request","Bender");if(form){boss.signForm(*form);boss.executeForm(*form);delete form;}form=intern.makeForm("coffee request","Office");delete form;}
