#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"

static void printSeparator(const std::string &title)
{
    std::cout << "\n=== " << title << " ===" << std::endl;
}

static void basicSubjectExample()
{
    printSeparator("Subject example");
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());

    ICharacter* me = new Character("me");
    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);

    ICharacter* bob = new Character("bob");
    me->use(0, *bob);
    me->use(1, *bob);

    delete bob;
    delete me;
    delete src;
}

static void inventoryAndCopyTests()
{
    printSeparator("Inventory and copy tests");
    MateriaSource source;
    source.learnMateria(new Ice());
    source.learnMateria(new Cure());
    source.learnMateria(new Ice());

    Character alice("alice");
    alice.equip(source.createMateria("ice"));
    alice.equip(source.createMateria("cure"));
    alice.equip(source.createMateria("ice"));
    alice.equip(source.createMateria("cure"));
    alice.equip(source.createMateria("ice"));

    Character target("target");
    alice.use(0, target);
    alice.use(1, target);
    alice.use(2, target);
    alice.use(3, target);
    alice.use(4, target);

    alice.unequip(1);
    alice.use(1, target);

    Character bob(alice);
    bob.use(0, target);
    bob.use(2, target);

    Character carol("carol");
    carol = alice;
    carol.use(3, target);
}

static void sourceUnknownTypeTest()
{
    printSeparator("Unknown type test");
    MateriaSource source;
    source.learnMateria(new Cure());
    AMateria* unknown = source.createMateria("fire");
    if (unknown == 0)
        std::cout << "unknown materia type returned 0" << std::endl;
}

int main()
{
    basicSubjectExample();
    inventoryAndCopyTests();
    sourceUnknownTypeTest();
    return 0;
}