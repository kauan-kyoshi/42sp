#include "Character.hpp"

Character::Character() : _name(""), _trashCount(0)
{
    for (int i = 0; i < 4; ++i)
        _inventory[i] = 0;
    for (int i = 0; i < 100; ++i)
        _trash[i] = 0;
    std::cout << "Character default constructor" << std::endl;
}

Character::Character(std::string const & name) : _name(name), _trashCount(0)
{
    for (int i = 0; i < 4; ++i)
        _inventory[i] = 0;
    for (int i = 0; i < 100; ++i)
        _trash[i] = 0;
    std::cout << "Character name constructor" << std::endl;
}

Character::Character(const Character &other) : _name(other._name), _trashCount(0)
{
    for (int i = 0; i < 4; ++i)
        _inventory[i] = 0;
    for (int i = 0; i < 100; ++i)
        _trash[i] = 0;
    std::cout << "Character copy constructor" << std::endl;
    *this = other;
}

Character &Character::operator=(const Character &other)
{
    std::cout << "Character copy assignment operator" << std::endl;
    if (this != &other)
    {
        clearInventory();
        clearTrash();
        _name = other._name;
        for (int i = 0; i < 4; ++i)
        {
            if (other._inventory[i])
                _inventory[i] = other._inventory[i]->clone();
            else
                _inventory[i] = 0;
        }
    }
    return *this;
}

Character::~Character()
{
    std::cout << "Character destructor" << std::endl;
    clearInventory();
    clearTrash();
}

std::string const & Character::getName() const
{
    return _name;
}

void Character::clearInventory()
{
    for (int i = 0; i < 4; ++i)
    {
        delete _inventory[i];
        _inventory[i] = 0;
    }
}

void Character::clearTrash()
{
    for (int i = 0; i < _trashCount; ++i)
    {
        delete _trash[i];
        _trash[i] = 0;
    }
    _trashCount = 0;
}

void Character::equip(AMateria* m)
{
    if (!m)
        return;
    for (int i = 0; i < 4; ++i)
    {
        if (_inventory[i] == 0)
        {
            _inventory[i] = m;
            return;
        }
    }
    delete m;
}

void Character::unequip(int idx)
{
    if (idx < 0 || idx >= 4 || _inventory[idx] == 0)
        return;
    if (_trashCount < 100)
        _trash[_trashCount++] = _inventory[idx];
    _inventory[idx] = 0;
}

void Character::use(int idx, ICharacter& target)
{
    if (idx < 0 || idx >= 4 || _inventory[idx] == 0)
        return;
    _inventory[idx]->use(target);
}