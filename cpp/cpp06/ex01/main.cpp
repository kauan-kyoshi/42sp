#include "Serializer.hpp"
#include <cassert>
#include <iostream>

int main()
{
    Data original;
    original.id = 42;
    original.name = "Objeto original";
    original.value = 6.25;

    uintptr_t raw = Serializer::serialize(&original);
    Data *restored = Serializer::deserialize(raw);

    assert(restored == &original);
    assert(restored->id == 42);
    assert(restored->name == "Objeto original");
    assert(restored->value == 6.25);

    std::cout << "Endereço original: " << &original << std::endl;
    std::cout << "Valor serializado: " << raw << std::endl;
    std::cout << "Endereço restaurado: " << restored << std::endl;
    std::cout << "Dados: " << restored->id << ", " << restored->name
              << ", " << restored->value << std::endl;
    std::cout << "Todos os testes do ex01 passaram." << std::endl;
    return 0;
}
