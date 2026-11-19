#include "base.cpp"

// Podria usar un archivo separado para cada vector, pero eso seria impractico.
// Debido a tal, en lugar de usar EOF como separador, escribimos el tamaño de
// cada objeto. Resulta que

void escribir_alumno(fstream &file, const Alumno &alumno) {
  write_string(file, alumno.nombre);
  write_string(file, alumno.matricula);
  file.write(reinterpret_cast<const char *>(alumno.calif),
             sizeof(alumno.calif));
  file.write(reinterpret_cast<const char *>(&alumno.grupo),
             sizeof(alumno.grupo));
  file.write(reinterpret_cast<const char *>(&alumno.promedio),
             sizeof(alumno.promedio));
}

Alumno leer_alumno(fstream &file) {
  Alumno alumno;
  alumno.nombre = read_string(file);
  alumno.matricula = read_string(file);
  file.read(reinterpret_cast<char *>(alumno.calif), sizeof(alumno.calif));
  file.read(reinterpret_cast<char *>(&alumno.grupo), sizeof(alumno.grupo));
  file.read(reinterpret_cast<char *>(&alumno.promedio),
            sizeof(alumno.promedio));
  return alumno;
}

void escribir_alumnos(fstream &file, const vector<Alumno> &v) {
  size_t n = v.size();
  file.write(reinterpret_cast<const char *>(&n), sizeof(n));
  for (const Alumno &a : v)
    escribir_alumno(file, a);
}

vector<Alumno> leer_alumnos(fstream &file) {
  size_t n = 0;
  file.read(reinterpret_cast<char *>(&n), sizeof(n));
  vector<Alumno> v;
  if (!file)
    return v;
  v.reserve(n);
  for (size_t i = 0; i < n; i++)
    v.push_back(leer_alumno(file));
  return v;
}