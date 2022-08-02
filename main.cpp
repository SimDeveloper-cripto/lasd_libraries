
#include "zlasdtest/test.hpp"
#include "zmytest/test.hpp"

int main() {
  ushort scelta = 0;

  std::cout << "Lasd Libraries 2022" << std::endl;
  std::cout << "[1] Per effettuare LASDTEST." << std::endl << "[2] Per effettuare lo svolgimento dell'esercizio." << std::endl;
  std::cout << "Scelta: ";
  std::cin >> scelta;

  switch(scelta) {
    case 1:
      lasdtest();
      break;
    case 2:
      startTest();
      break;
    default: 
      std::cout << "Errore: scelta non disponibile!" << std::endl;
  }

  // little :))

  return 0;
}