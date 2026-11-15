#include "Bureaucrat.hpp"
int main() { try { Bureaucrat alice("Alice", 2); std::cout << alice << std::endl; alice.incrementGrade(); std::cout << alice << std::endl; alice.incrementGrade(); } catch (const std::exception& e) { std::cerr << "Exception: " << e.what() << std::endl; } }
