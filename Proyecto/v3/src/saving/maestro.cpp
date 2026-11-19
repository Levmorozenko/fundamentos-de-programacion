#include "base.cpp"

void escribir_maestro(fstream &file, const Maestro &maestro) {
  write_string(file, maestro.nombre);
  write_string(file, maestro.materia);
}

Maestro leer_maestro(fstream &file) {
  Maestro maestro;
  maestro.nombre = read_string(file);
  maestro.materia = read_string(file);
  return maestro;
}

void escribir_maestros(fstream &file, const vector<Maestro> &v) {
  size_t n = v.size();
  file.write(reinterpret_cast<const char *>(&n), sizeof(n));
  for (const Maestro &m : v)
    escribir_maestro(file, m);
}

vector<Maestro> leer_maestros(fstream &file) {
  size_t n = 0;
  file.read(reinterpret_cast<char *>(&n), sizeof(n));
  vector<Maestro> v;
  if (!file)
    return v;
  v.reserve(n);
  for (size_t i = 0; i < n; i++)
    v.push_back(leer_maestro(file));
  return v;
}
