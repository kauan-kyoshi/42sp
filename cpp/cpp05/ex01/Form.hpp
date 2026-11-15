#ifndef FORM_HPP
#define FORM_HPP

#include <exception>
#include <ostream>
#include <string>

class Bureaucrat;

class Form
{
private:
    const std::string name;
    bool signedStatus;
    const int gradeToSign;
    const int gradeToExecute;

public:
    Form();
    Form(const std::string &name, int gradeToSign, int gradeToExecute);
    Form(const Form &other);
    Form &operator=(const Form &other);
    ~Form();

    const std::string &getName() const;
    bool getSignedStatus() const;
    int getGradeToSign() const;
    int getGradeToExecute() const;
    void beSigned(const Bureaucrat &bureaucrat);

    class GradeTooHighException : public std::exception
    {
    public:
        virtual const char *what() const throw();
    };

    class GradeTooLowException : public std::exception
    {
    public:
        virtual const char *what() const throw();
    };
};

std::ostream &operator<<(std::ostream &out, const Form &form);

#endif
