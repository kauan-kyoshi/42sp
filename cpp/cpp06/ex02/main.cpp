#include "Base.hpp"
#include <iostream>

int main()
{
    for (int index = 0; index < 10; ++index)
    {
        Base *object = generate();
        std::cout << "Ponteiro: ";
        identify(object);
        std::cout << "Referência: ";
        identify(*object);
        delete object;
    }
    std::cout << "Ponteiro nulo: ";
    identify(static_cast<Base *>(0));
    std::cout << "Todos os testes do ex02 passaram." << std::endl;
    return 0;
}
