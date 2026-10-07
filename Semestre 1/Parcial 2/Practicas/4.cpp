// Ingresos de supermercado. Almacena en un arreglo las ventas de 100 clientes y
// calcula la suma total de ingresos.
#include "custom.cpp"
#include <cstdlib>
#include <vector>
using namespace custom;

int main() {
  vector<int> chocolates_vendidos(100);
  int ventas_totales = 0;

  for (int i = 0; i < chocolates_vendidos.size(); i++) {
    int x = abs(random::digit());
    chocolates_vendidos[i] = x;
    ventas_totales += x;
  }

  int precio = 20; // pesos por chocolate

  std::cout << "Se vendieron " << ventas_totales
            << " chocolates, con ingreso total de " << ventas_totales * precio
            << " pesos.";

  return 0;
}
