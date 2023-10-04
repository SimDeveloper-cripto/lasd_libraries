
#include "zlasdtest/test.hpp"
#include "zmytest/test.hpp"
#include "user-test/usertest.hpp"

// LASD: Algorithms and data structures (lab)

int main() {
  ushort scelta = 0;

  std::cout << "Welcome to Lasd Libraries 2022!" << std::endl;
  std::cout << "[1] Run Library test (LASD-TEST)." << std::endl << "[2] Run usage example provided by the developer." << std::endl;
  std::cout << "[3] Run your personal test." << std::endl;
  std::cout << "Your choice: ";
  std::cin >> scelta;

  switch(scelta) {
    case 1:
      lasdtest();
      break;
    case 2:
      startTest();
      break;
    case 3:
      usertest::run_test();
      break;
    default:
      std::cout << "Error: your choice is not valid!" << std::endl;
  }

  return 0;
}