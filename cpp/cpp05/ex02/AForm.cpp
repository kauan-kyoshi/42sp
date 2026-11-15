#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(const std::string &name, int gradeToSign, int gradeToExecute)
    : name(name), signedStatus(false), gradeToSign(gradeToSign),
      gradeToExecute(gradeToExecute)
{
    if (gradeToSign < 1 || gradeToExecute < 1)
        throw GradeTooHighException();
    if (gradeToSign > 150 || gradeToExecute > 150)
        throw GradeTooLowException();
}

AForm::AForm(const AForm &other)
    : name(other.name), signedStatus(other.signedStatus),
      gradeToSign(other.gradeToSign), gradeToExecute(other.gradeToExecute) {}

AForm &AForm::operator=(const AForm &other)
{
    if (this != &other)
        signedStatus = other.signedStatus;
    return *this;
}

AForm::~AForm() {}
const std::string &AForm::getName() const { return name; }
bool AForm::getSignedStatus() const { return signedStatus; }
int AForm::getGradeToSign() const { return gradeToSign; }
int AForm::getGradeToExecute() const { return gradeToExecute; }

void AForm::beSigned(const Bureaucrat &bureaucrat)
{
    if (bureaucrat.getGrade() > gradeToSign)
        throw GradeTooLowException();
    signedStatus = true;
}

void AForm::execute(const Bureaucrat &executor) const
{
    if (!signedStatus)
        throw FormNotSignedException();
    if (executor.getGrade() > gradeToExecute)
        throw GradeTooLowException();
    executeAction();
}

const char *AForm::GradeTooHighException::what() const throw()
{ return "classificação do formulário alta demais"; }
const char *AForm::GradeTooLowException::what() const throw()
{ return "classificação do burocrata baixa demais"; }
const char *AForm::FormNotSignedException::what() const throw()
{ return "formulário não assinado"; }

std::ostream &operator<<(std::ostream &out, const AForm &form)
{
    return out << form.getName() << ", assinado: "
               << (form.getSignedStatus() ? "sim" : "não")
               << ", grau para assinar: " << form.getGradeToSign()
               << ", grau para executar: " << form.getGradeToExecute() << ".";
}
