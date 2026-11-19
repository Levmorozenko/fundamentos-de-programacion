#include "base.cpp"

void escribir_grupo(fstream &file, const Grupo &grupo) {
  write_string(file, grupo.nombre);
  write_string(file, grupo.carrera);
}

Grupo leer_grupo(fstream &file) {
  Grupo grupo;
  grupo.nombre = read_string(file);
  grupo.carrera = read_string(file);
  return grupo;
}

void escribir_grupos(fstream &file, const vector<Grupo> &grupos) {
  size_t n = grupos.size();
  file.write(reinterpret_cast<const char *>(&n), sizeof(n));
  for (const Grupo &grupo : grupos)
    escribir_grupo(file, grupo);
}

vector<Grupo> leer_grupos(fstream &file) {
  size_t n = 0;
  file.read(reinterpret_cast<char *>(&n), sizeof(n));
  vector<Grupo> v;
  if (!file)
    return v;
  v.reserve(n);
  for (size_t i = 0; i < n; i++)
    v.push_back(leer_grupo(file));
  return v;
}