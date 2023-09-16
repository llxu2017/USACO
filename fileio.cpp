/*
ID: calvin.9
LANG: C
TASK: ride
*/
#include <iostream>
#include <fstream>
#include <string>

int main() {
  std::ofstream fout("ride.out");
  std::ifstream fin("ride.in");
  std::string a, b;
  fin >> a >> b;
  fout << a << std::endl << b << std::endl;
  return 0;
}
