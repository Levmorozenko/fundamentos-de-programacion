#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ifstream archivo("poema.txt");
  if (!archivo) {
    cout << "No se pudo abrir el archivo\n";
    return 1;
  }
  string linea;
  int count = 0;
  while (getline(archivo, linea)) {
    count++;
    cout << count << "| " << linea << endl;
  }
  cout << endl << "El poema tiene el total de " << count << " lineas\n";
  archivo.close();
  return 0;
}
