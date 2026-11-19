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

void escribir_maestros(fstream &file, const vector<Maestro> &maestros) {
  size_t n = maestros.size();
  file.write(reinterpret_cast<const char *>(&n), sizeof(n));
  fror(maestro, maestros) escribir_maestro(file, maestro);
}

vector<Maestro> leer_maestros(fstream &file) {
  size_t n = 0;
  file.read(reinterpret_cast<char *>(&n), sizeof(n));
  vector<Maestro> maestros;
  if (!file)
    return maestros;
  maestros.reserve(n);
  fr(i, n) maestros.push_back(leer_maestro(file));
  return maestros;
}
