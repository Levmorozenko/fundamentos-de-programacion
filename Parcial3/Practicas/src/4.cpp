// Versión binaria. Guarda el mismo arreglo en un archivo binario. Compara
// el tamaño del archivo binario contra el de texto y explica por qué son
// distintos.

#include "custom.cpp"

int main() {
  set_utf8();

  fstream bin_file("Alumnos.bin", ios::out | ios::trunc | ios::binary);
  fstream file("Alumnos.txt", ios::in);
  if (!file.is_open()) {
    cerr << "El archivo no pudo abrirse.\n";
    return 1;
  }

  vector<Alumno> alumnos;

  string line;
  while (getline(file, line)) {
    if (line.empty())
      continue;
    Alumno alumno = parsear_alumno_txt(line);
    almacenar_alumno_bin(bin_file, alumno);
  }

  return 0;
}

// Los resultados del tamaño fueron los siguientes:
// Alumnos.txt: 42,963,542 bytes
// Alumnos.bin: 58,548,701 bytes
//
// sizeof(txt) < sizeof(bin); Deberia ser al reves, no?
// Pues segun mis calculos, la diferencia es entre los tamaños de strings y char
// '/' o '\n'.
// Mi IDE muestra que size_t es unsigned long long, cual es 8 bytes. 2 x 8 = 16
// bytes de memoria adicional para strings.
// En caso del texto, un char es exactamente 1 byte. 1 x 6 = 6 bytes
// adicionales. Entonces, en version binaria guardamos 16 - 6 = 10 mas bytes de
// memoria para cada struct. Los tamaños no cuadran, porque entre 1 millon de
// structs, para cada uno hay una diferencia de 58 - 42 = 16 bytes. Sin embargo,
// no adentraré al tema compilacion, es demasiado amplio y no me interesa.
//
// Una teoria que tengo es explorada en 4-2.cpp
