#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

static void printSeparator(const std::string &title)
{
    std::cout << "\n=== " << title << " ===" << std::endl;
}

static void fillAnimals(Animal **animals, int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (i < size / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }
}

static void destroyAnimals(Animal **animals, int size)
{
    for (int i = 0; i < size; ++i)
        delete animals[i];
}

static void testDeepCopy()
{
    printSeparator("Deep copy");
    Dog originalDog;
    originalDog.setIdea(0, "chase the mailman");
    originalDog.setIdea(1, "bury a bone");
    Dog copiedDog(originalDog);
    originalDog.setIdea(0, "chew the sofa");

    std::cout << "original dog idea 0: " << originalDog.getIdea(0) << std::endl;
    std::cout << "copied dog idea 0:   " << copiedDog.getIdea(0) << std::endl;

    Cat originalCat;
    originalCat.setIdea(0, "nap on the keyboard");
    Cat copiedCat;
    copiedCat = originalCat;
    originalCat.setIdea(0, "ignore the humans");

    std::cout << "original cat idea 0: " << originalCat.getIdea(0) << std::endl;
    std::cout << "copied cat idea 0:   " << copiedCat.getIdea(0) << std::endl;
}

int main()
{
    printSeparator("Polymorphic array");
    const int size = 8;
    Animal *animals[size];

    fillAnimals(animals, size);
    for (int i = 0; i < size; ++i)
    {
        std::cout << animals[i]->getType() << " -> ";
        animals[i]->makeSound();
    }
    destroyAnimals(animals, size);

    testDeepCopy();

    printSeparator("Pointer polymorphism");
    const Animal *j = new Dog();
    const Animal *i = new Cat();
    std::cout << j->getType() << std::endl;
    std::cout << i->getType() << std::endl;
    j->makeSound();
    i->makeSound();
    delete j;
    delete i;

    printSeparator("Wrong polymorphism");
    const WrongAnimal *wrongAnimal = new WrongAnimal();
    const WrongAnimal *wrongCat = new WrongCat();
    wrongAnimal->makeSound();
    wrongCat->makeSound();
    delete wrongAnimal;
    delete wrongCat;

    return 0;
}