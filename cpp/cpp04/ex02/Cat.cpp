#include "Cat.hpp"

Cat::Cat() : Animal(), brain(new Brain())
{
    type = "Cat";
    std::cout << "Cat default constructor" << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other), brain(new Brain(*other.brain))
{
    type = other.type;
    std::cout << "Cat copy constructor" << std::endl;
}

Cat &Cat::operator=(const Cat &other)
{
    std::cout << "Cat copy assignment operator" << std::endl;
    if (this != &other)
    {
        Animal::operator=(other);
        *brain = *other.brain;
    }
    return *this;
}

Cat::~Cat()
{
    std::cout << "Cat destructor" << std::endl;
    delete brain;
}

void Cat::makeSound() const
{
    std::cout << "[Cat] Meow!" << std::endl;
}

void Cat::setIdea(int index, const std::string &idea)
{
    brain->setIdea(index, idea);
}

std::string Cat::getIdea(int index) const
{
    return brain->getIdea(index);
}