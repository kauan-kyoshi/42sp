#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

static void printSeparator(const std::string &title)
{
    std::cout << "\n=== " << title << " ===" << std::endl;
}

int main()
{
    printSeparator("Dynamic dispatch");
    const Animal *meta = new Animal();
    const Animal *j = new Dog();
    const Animal *i = new Cat();

    std::cout << j->getType() << std::endl;
    std::cout << i->getType() << std::endl;
    i->makeSound();
    j->makeSound();
    meta->makeSound();

    delete meta;
    delete j;
    delete i;

    printSeparator("Stack objects and copies");
    Animal base;
    Dog dog;
    Cat cat;
    Dog dogCopy(dog);
    Cat catCopy;
    catCopy = cat;
    Animal baseCopy(base);
    baseCopy.makeSound();
    dogCopy.makeSound();
    catCopy.makeSound();

    printSeparator("Wrong polymorphism");
    const WrongAnimal *wrongMeta = new WrongAnimal();
    const WrongAnimal *wrongCat = new WrongCat();

    std::cout << wrongCat->getType() << std::endl;
    wrongCat->makeSound();
    wrongMeta->makeSound();

    delete wrongMeta;
    delete wrongCat;

    printSeparator("Direct wrong object");
    WrongCat directWrongCat;
    directWrongCat.makeSound();

    return 0;
}