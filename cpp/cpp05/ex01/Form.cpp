#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form()
    : name("Default"), signedStatus(false), gradeToSign(150),
      gradeToExecute(150) {}

Form::Form(const std::string &name, int gradeToSign, int gradeToExecute)
    : name(name), signedStatus(false), gradeToSign(gradeToSign),
      gradeToExecute(gradeToExecute)
{
    if (gradeToSign < 1 || gradeToExecute < 1)
        throw GradeTooHighException();
    if (gradeToSign > 150 || gradeToExecute > 150)
        throw GradeTooLowException();
}

Form::Form(const Form &other)
    : name(other.name), signedStatus(other.signedStatus),
      gradeToSign(other.gradeToSign), gradeToExecute(other.gradeToExecute) {}

Form &Form::operator=(const Form &other)
{
    if (this != &other)
        signedStatus = other.signedStatus;
    return *this;
}

Form::~Form() {}

const std::string &Form::getName() const { return name; }
bool Form::getSignedStatus() const { return signedStatus; }
int Form::getGradeToSign() const { return gradeToSign; }
int Form::getGradeToExecute() const { return gradeToExecute; }

void Form::beSigned(const Bureaucrat &bureaucrat)
{
    if (bureaucrat.getGrade() > gradeToSign)
        throw GradeTooLowException();
    signedStatus = true;
}

const char *Form::GradeTooHighException::what() const throw()
{
    return "classificação do formulário alta demais";
}

const char *Form::GradeTooLowException::what() const throw()
{
    return "classificação do burocrata baixa demais";
}

std::ostream &operator<<(std::ostream &out, const Form &form)
{
    return out << form.getName() << ", assinado: "
               << (form.getSignedStatus() ? "sim" : "não")
               << ", grau para assinar: " << form.getGradeToSign()
               << ", grau para executar: " << form.getGradeToExecute() << ".";
}
