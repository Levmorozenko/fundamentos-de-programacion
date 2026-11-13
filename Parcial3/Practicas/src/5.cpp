// Manejo de errores. Intenta abrir un archivo que no existe y maneja el error
// sin que el programa se cierre inesperadamente (muestra un mensaje claro al
// usuario).

#include "custom.cpp"

void do_something_with_file(fstream &file) {} // funcion cosmetica

int main() {
  fstream file("Archivo_inexistente.txt", ios::in | ios::out);

  if (!file.is_open()) {
    cout << "The input file does not exist. Please create it first\n";
    return 0;
  }

  do_something_with_file(file);

  return 0;
}
