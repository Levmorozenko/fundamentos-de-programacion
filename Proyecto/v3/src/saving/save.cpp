#include "alumno.cpp"
#include "grupo.cpp"
#include "maestro.cpp"

bool guardar(const vector<Grupo> &grupos, const vector<Alumno> &alumnos,
             const vector<Maestro> &maestros,
             const string &path = default_file) {
  // Practica 4: crear/truncar en binario.
  fstream file(path, ios::out | ios::trunc | ios::binary);
  if (!file.is_open()) { // Practica 5: error claro, sin cerrar el programa.
    cerr << "No se pudo crear " << path << ".\n";
    return false;
  }

  escribir_grupos(file, grupos);
  escribir_alumnos(file, alumnos);
  escribir_maestros(file, maestros);
  return true; // el destructor cierra el archivo
}

bool cargar(vector<Grupo> &grupos, vector<Alumno> &alumnos,
            vector<Maestro> &maestros, const string &path = default_file) {
  // Practica 6: solo lectura binaria.
  fstream file(path, ios::in | ios::binary);
  if (!file.is_open())
    return false; // primera ejecucion: se empieza vacio

  vector<Grupo> g = leer_grupos(file);
  vector<Alumno> a = leer_alumnos(file);
  vector<Maestro> m = leer_maestros(file);

  if (!file) {
    cerr << "El archivo " << path << " esta corrupto; se ignorara.\n";
    return false;
  }

  grupos = g;
  alumnos = a;
  maestros = m;
  return true;
}
