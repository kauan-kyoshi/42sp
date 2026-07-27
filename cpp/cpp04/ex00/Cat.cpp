#include "Cat.hpp"

Cat::Cat() : Animal()
{
    type = "Cat";
    std::cout << "Cat default constructor" << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other)
{
    type = other.type;
    std::cout << "Cat copy constructor" << std::endl;
}

Cat &Cat::operator=(const Cat &other)
{
    std::cout << "Cat copy assignment operator" << std::endl;
    if (this != &other)
        type = other.type;
    return *this;
}

Cat::~Cat()
{
    std::cout << "Cat destructor" << std::endl;
}

void Cat::makeSound() const
{
    std::cout << "[Cat] Meow!" << std::endl;
}