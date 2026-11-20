#include "alumno.cpp"
#include "grupo.cpp"
#include "maestro.cpp"

// The Farmer Was Replaced me enseñó esta abstraccion en niveles.

bool save_file(const vector<Grupo> &grupos, const vector<Alumno> &alumnos,
               const vector<Maestro> &maestros, const string &path) {
  fstream file(path, ios::out | ios::trunc | ios::binary);
  if (!file.is_open()) {
    cerr << "No se pudo crear el archivo " << path << ".\n";
    return false;
  }

  escribir_grupos(file, grupos);
  escribir_alumnos(file, alumnos);
  escribir_maestros(file, maestros);
  return true; // que bueno que fstream cierra el archivo por si mismo,
               // totalmente no me jode la percepcion de como se debe manejar la
               // memoria en etapa fundamental del aprendizaje.
}

bool load_file(vector<Grupo> &grupos, vector<Alumno> &alumnos,
               vector<Maestro> &maestros, const string &path = "datos.bin") {
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
    cerr << "El archivo " << path << " esta corrupto.\n";
    return false;
  }

  grupos = g;
  alumnos = a;
  maestros = m;
  return true;
}

bool handle_user_save(const vector<Grupo> &grupos,
                      const vector<Alumno> &alumnos,
                      const vector<Maestro> &maestros, const string &path) {
  // no me dejó inicializar las variables dentro del switch, pero es el caso
  // ideal para usar un puntero a memoria dinamica. Y luego lo meti a una
  // funcion, por lo que se queda la memoria dinamica
  bool *success;
  cout << "Guardando...\n";
  success = new bool(save_file(grupos, alumnos, maestros, path));
  if (*success == true) {
    cout << "Save successful!\n";
    delete success;
    await_enter();
    return true;
  } else {
    cout << "Error al guardar el archivo\n";
    delete success;
    await_enter();
    return false;
  }
}
