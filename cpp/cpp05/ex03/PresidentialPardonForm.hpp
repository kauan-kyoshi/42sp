#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP
#include "AForm.hpp"
class PresidentialPardonForm : public AForm
{
private:
    const std::string target;
    virtual void executeAction() const;
public:
    PresidentialPardonForm(const std::string &target);
    PresidentialPardonForm(const PresidentialPardonForm &other);
    PresidentialPardonForm &operator=(const PresidentialPardonForm &other);
    virtual ~PresidentialPardonForm();
    const std::string &getTarget() const;
};
#endif
