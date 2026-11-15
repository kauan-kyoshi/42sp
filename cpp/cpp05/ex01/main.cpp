#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <cassert>
#include <iostream>
#include <sstream>

static void testInvalidForms()
{
    bool caught = false;
    try { Form invalid("High", 0, 1); }
    catch (const Form::GradeTooHighException &) { caught = true; }
    assert(caught);
    caught = false;
    try { Form invalid("Low", 1, 151); }
    catch (const Form::GradeTooLowException &) { caught = true; }
    assert(caught);
}

static void testSigning()
{
    Bureaucrat chief("Chefe", 1);
    Bureaucrat junior("Júnior", 51);
    Bureaucrat exact("Exato", 50);
    Form permit("Licença", 50, 20);
    junior.signForm(permit);
    assert(!permit.getSignedStatus());
    exact.signForm(permit);
    assert(permit.getSignedStatus());
    chief.signForm(permit);
    assert(permit.getSignedStatus());
    std::cout << permit << std::endl;
}

static void testCanonicalForm()
{
    Bureaucrat signer("Assinante", 1);
    Form original("Original", 20, 10);
    original.beSigned(signer);
    Form copy(original);
    assert(copy.getName() == "Original" && copy.getSignedStatus());
    Form destination("Destino", 100, 90);
    destination = original;
    assert(destination.getName() == "Destino");
    assert(destination.getGradeToSign() == 100);
    assert(destination.getGradeToExecute() == 90);
    assert(destination.getSignedStatus());
    std::ostringstream output;
    output << destination;
    assert(output.str() == "Destino, assinado: sim, grau para assinar: 100, grau para executar: 90.");
}

int main()
{
    testInvalidForms();
    testSigning();
    testCanonicalForm();
    std::cout << "Todos os testes do ex01 passaram." << std::endl;
    return 0;
}
