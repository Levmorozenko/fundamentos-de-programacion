#include <vector>
using namespace std;

int main() {
  vector<int> numeros = {1, 2, 3};

  int indice = 2;
  if (indice >= 0 && indice < numeros.size()) {
    numeros[indice] += 2;
  }
}
