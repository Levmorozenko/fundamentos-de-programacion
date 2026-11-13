// Agregar sin perder datos. Agrega un alumno nuevo al archivo existente, sin
// borrar los que ya estaban.

#include "custom.cpp"

int main() {
  fstream file("Alumnos.txt", ios::out | ios::app);
  if (!file.is_open()) {
    cerr << "El archivo no pudo abrirse.\n";
    return 1;
  }

  Alumno alumno = crear_alumno();
  almacenar_alumno_texto(file, alumno);

  return 0;
}
