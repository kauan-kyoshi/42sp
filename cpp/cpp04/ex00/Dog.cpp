#include "Dog.hpp"

Dog::Dog() : Animal()
{
    type = "Dog";
    std::cout << "Dog default constructor" << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other)
{
    type = other.type;
    std::cout << "Dog copy constructor" << std::endl;
}

Dog &Dog::operator=(const Dog &other)
{
    std::cout << "Dog copy assignment operator" << std::endl;
    if (this != &other)
        type = other.type;
    return *this;
}

Dog::~Dog()
{
    std::cout << "Dog destructor" << std::endl;
}

void Dog::makeSound() const
{
    std::cout << "[Dog] Woof woof!" << std::endl;
}