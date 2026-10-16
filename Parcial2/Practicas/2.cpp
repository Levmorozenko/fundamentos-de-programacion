// Promedio de grupo. Usa 3 arreglos: en dos guarda los promedios de dos grupos
// de 5 alumnos, y en el tercero el promedio más alto de cada posición.
#include "custom.cpp"
#include <vector>
using namespace custom;

// =============================================================================
// Aqui habia una parte grande del codigo. Dado que fueron funciones, tambien
// usadas en otras practicas, los moví al modulo custom.cpp.
// =============================================================================

// funcion super desactualizada ya que aprendi closuras. Guardada para
// compatibilidad.
vector<float> fill_array_rand(vector<float> array) {
  for (int i = 0; i < array.size(); i++) {
    array[i] = random::calificacion();
  }
  return array;
}

int main() {
  custom_cls();

  vector<float> grupo1 = fill_array_rand(vector<float>(5));
  vector<float> grupo2 = fill_array_rand(vector<float>(5));

  vector<float> promedios(5);

  for (int i = 0; i < promedios.size(); i++) {
    promedios[i] = ((grupo1[i] > grupo2[i]) ? grupo1[i] : grupo2[i]);
  } // amo usar mini-ifs

  print_array(grupo1, "Calificaciones del grupo 1: ");
  print_array(grupo2, "Calificaciones del grupo 2: ");
  print_array(promedios, "Promedio mayor para cada posicion: ");

  return 0;
}
