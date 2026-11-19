#include "alumno.cpp"
#include "grupo.cpp"
#include "maestro.cpp"

// The Farmer Was Replaced me enseñó esta abstraccion en niveles.

bool save(const vector<Grupo> &grupos, const vector<Alumno> &alumnos,
          const vector<Maestro> &maestros, const string &path = default_file) {
  fstream file(path, ios::out | ios::trunc | ios::binary);
  if (!file.is_open()) {
    cerr << "No se pudo crear " << path << ".\n";
    return false;
  }

  escribir_grupos(file, grupos);
  escribir_alumnos(file, alumnos);
  escribir_maestros(file, maestros);
  return true; // que bueno que fstream cierra el archivo por si mismo,
               // totalmente no me jode la percepcion de como se debe manejar la
               // memoria en etapa fundamental del aprendizaje.
}

bool load(vector<Grupo> &grupos, vector<Alumno> &alumnos,
          vector<Maestro> &maestros, const string &path = default_file) {
  fstream file(path, ios::in | ios::binary);
  if (!file.is_open())
    return false;

  // Dejo este mini crimen porque finalmente se que estoy haciendo.
  vector<Grupo> g = leer_grupos(file);
  vector<Alumno> a = leer_alumnos(file);
  vector<Maestro> m = leer_maestros(file);

  // la razon por cual esta separado es para checar si el archivo esta corrupto.
  // Si se cierra entre la ejecucion, algun dato esta mal. Si algun dato esta
  // mal, todos los datos despues estan mal. Es aqui donde no dejamos que
  // cargue basura.
  if (!file) {
    cerr << "El archivo " << path
         << " reprobo prepa y tomo ejemplo "
            "de la situacion geopolitica (esta corrupto).\n";
    return false;
  }

  grupos = g;
  alumnos = a;
  maestros = m;
  return true;
}
