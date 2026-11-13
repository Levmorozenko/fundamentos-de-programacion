// Extiende 4.cpp. Usa la funcion del 2.cpp para convertir todas lineas de
// Alumnos.txt a Alumnos.bin. Los resultados fueron los siguientes:
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
// Una teoria que tengo puede ser explorada en 4-3.cpp

#include "custom.cpp"

void almacenar_alumno_bin(ofstream &file, Alumno &i) {
  // yo presenté esto

  size_t nombre_size = i.nombre.length();
  file.write(reinterpret_cast<const char *>(&nombre_size), sizeof(nombre_size));
  file.write(i.nombre.c_str(), nombre_size);

  size_t matricula_size = i.matricula.length();
  file.write(reinterpret_cast<const char *>(&matricula_size),
             sizeof(matricula_size));
  file.write(i.matricula.c_str(), matricula_size);

  // sabemos que el tamaño de int calif[3] y grupo son 12 y 4 bytes
  // respectivamente.
  file.write(reinterpret_cast<const char *>(&i.calif), sizeof(i.calif));
  file.write(reinterpret_cast<const char *>(&i.grupo), sizeof(i.grupo));
}

int main() {
  set_utf8();

  ofstream bin_file("Alumnos.bin", ios::trunc | ios::binary);
  ifstream file("Alumnos.txt");
  if (!file.is_open()) {
    cerr << "El archivo no pudo abrirse.\n";
    return 1;
  }

  vector<Alumno> alumnos;

  string line;
  while (getline(file, line)) {
    if (line.empty())
      continue; // como el eof()
    vector<string> parts;
    size_t start = 0;
    while (true) {
      size_t end = line.find('/', start);
      parts.push_back(line.substr(start, end - start));
      if (end == string::npos)
        break;
      start = end + 1;
    }
    Alumno alumno;
    alumno.nombre = parts[0];
    alumno.matricula = parts[1];
    alumno.calif[0] = stof(parts[2]);
    alumno.calif[1] = stof(parts[3]);
    alumno.calif[2] = stof(parts[4]);
    alumno.grupo = stoi(parts[5]);
    almacenar_alumno_bin(bin_file, alumno);
  }

  file.close();
  return 0;
}
