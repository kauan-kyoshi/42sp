#include "Bureaucrat.hpp"
#include <cassert>
#include <climits>
#include <iostream>
#include <sstream>

static void testInvalidGrade(int grade)
{
    bool caught = false;
    try
    {
        Bureaucrat invalid("Invalid", grade);
    }
    catch (const Bureaucrat::GradeTooHighException &e)
    {
        assert(grade < 1);
        caught = true;
        std::cout << grade << ": " << e.what() << std::endl;
    }
    catch (const Bureaucrat::GradeTooLowException &e)
    {
        assert(grade > 150);
        caught = true;
        std::cout << grade << ": " << e.what() << std::endl;
    }
    assert(caught);
}

static void testLimits()
{
    Bureaucrat highest("Highest", 2);
    Bureaucrat lowest("Lowest", 149);
    highest.incrementGrade();
    lowest.decrementGrade();
    assert(highest.getGrade() == 1);
    assert(lowest.getGrade() == 150);
    bool caught = false;
    try
    {
        highest.incrementGrade();
    }
    catch (const std::exception &e)
    {
        caught = true;
        std::cout << e.what() << std::endl;
    }
    assert(caught && highest.getGrade() == 1);
    caught = false;
    try
    {
        lowest.decrementGrade();
    }
    catch (const std::exception &e)
    {
        caught = true;
        std::cout << e.what() << std::endl;
    }
    assert(caught && lowest.getGrade() == 150);
    highest.decrementGrade();
    lowest.incrementGrade();
    assert(highest.getGrade() == 2);
    assert(lowest.getGrade() == 149);
}

static void testCanonicalForm()
{
    Bureaucrat defaultBureaucrat;
    assert(defaultBureaucrat.getGrade() == 150);
    Bureaucrat original("Ana", 42);
    Bureaucrat copy(original);
    assert(copy.getName() == "Ana" && copy.getGrade() == 42);
    copy.incrementGrade();
    assert(original.getGrade() == 42);
    Bureaucrat assigned("Bruno", 100);
    assigned = original;
    assert(assigned.getName() == "Bruno" && assigned.getGrade() == 42);
    Bureaucrat &alias = assigned;
    assigned = alias;
    assert(assigned.getName() == "Bruno" && assigned.getGrade() == 42);
    const Bureaucrat constant(original);
    std::ostringstream output;
    output << constant;
    assert(output.str() == "Ana, burocrata com classificação 42.");
    std::cout << constant << std::endl;
}

int main()
{
    testInvalidGrade(0);
    testInvalidGrade(151);
    testInvalidGrade(INT_MIN);
    testInvalidGrade(INT_MAX);
    testLimits();
    testCanonicalForm();
    std::cout << "Todos os testes passaram." << std::endl;
    return 0;
}
