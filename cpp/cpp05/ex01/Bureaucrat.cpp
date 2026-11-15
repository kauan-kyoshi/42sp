#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

Bureaucrat::Bureaucrat() : name("Default"), grade(150) {}

Bureaucrat::Bureaucrat(const std::string &name, int grade)
    : name(name), grade(grade)
{
    if (grade < 1)
        throw GradeTooHighException();
    if (grade > 150)
        throw GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat &other)
    : name(other.name), grade(other.grade) {}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other)
{
    if (this != &other)
        grade = other.grade;
    return *this;
}

Bureaucrat::~Bureaucrat() {}

const std::string &Bureaucrat::getName() const { return name; }
int Bureaucrat::getGrade() const { return grade; }

void Bureaucrat::incrementGrade()
{
    if (grade == 1)
        throw GradeTooHighException();
    --grade;
}

void Bureaucrat::decrementGrade()
{
    if (grade == 150)
        throw GradeTooLowException();
    ++grade;
}

void Bureaucrat::signForm(Form &form) const
{
    try
    {
        form.beSigned(*this);
        std::cout << name << " assinou " << form.getName() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << name << " não conseguiu assinar " << form.getName()
                  << " porque " << e.what() << "." << std::endl;
    }
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
    return "Classificacao alta demais";
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
    return "Classificacao baixa demais";
}

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureaucrat)
{
    return out << bureaucrat.getName() << ", burocrata com classificação "
               << bureaucrat.getGrade() << ".";
}
