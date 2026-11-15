#include "Bureaucrat.hpp"
#include "Form.hpp"
int main(){Bureaucrat junior("Junior",150);Bureaucrat chief("Chief",1);Form permit("Permit",50,20);junior.signForm(permit);chief.signForm(permit);std::cout<<permit<<std::endl;}
