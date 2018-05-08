#include <iostream>
#include <iomanip>
#include <ctime>

void delay(const unsigned long long int &loops);

int main() {

  unsigned long long int loops_per_sec = 1;
  unsigned long long int ticks;
  std::cout << "Calibrating delay loop.." << std::endl;
  while (loops_per_sec <<= 1) {
    ticks = clock();
    delay (loops_per_sec);
    ticks = clock() - ticks;

    std::cout << ticks << " " << loops_per_sec << std::endl ;
    if (ticks >= CLOCKS_PER_SEC) {
      loops_per_sec = (loops_per_sec / ticks) * CLOCKS_PER_SEC;
      double result = static_cast<double> (((loops_per_sec / 5000) / 100) + (loops_per_sec / 5000) % 100);

      std::cout << "ok - " << std::fixed << std::setprecision(2) << result << " BogoMIPS" << std::endl;
      return 0;
    }
  }

  std::cerr << "failed" << std::endl;
  return -1;
}

void delay(const unsigned long long int &loops) {
  for (unsigned long long int i = 0; i < loops; ++i)
    ;
}

