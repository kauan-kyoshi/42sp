#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "AMateria.hpp"
#include "ICharacter.hpp"
#include <string>

class Character : public ICharacter
{
private:
    std::string _name;
    AMateria* _inventory[4];
    AMateria* _trash[100];
    int _trashCount;

    void clearInventory();
    void clearTrash();

public:
    Character();
    Character(std::string const & name);
    Character(const Character &other);
    Character &operator=(const Character &other);
    virtual ~Character();

    std::string const & getName() const;
    void equip(AMateria* m);
    void unequip(int idx);
    void use(int idx, ICharacter& target);
};

#endif