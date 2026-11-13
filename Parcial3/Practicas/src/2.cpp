// Leer y reconstruir. Lee ese archivo y reconstruye el arreglo de Alumno en
// memoria. Muestra los datos leídos para confirmar que coinciden.

#include "custom.cpp"
#include <iterator>
#include <vector>

// dado que solo escribimos structs enteros, no tenemos que preocuparnos por
// posibles offsets. En un caso de 0-trust agregaria verificacion propia.
// Por misma razon no habrá verificacion en las siguientes practicas.

int main() {
  ifstream file("Alumnos.txt");
  if (!file.is_open()) {
    cerr << "El archivo no pudo abrirse.\n";
    return 1;
  }

  // Esta implementacion funciona, por razones que no entiendo. Por alguna razon
  // lo siguiente separa todo el archivo entre whitespaces, incluyendo espacios,
  // \t y \n. Debido a esto, todos espacios son reemplazados con '_' y se usa
  // '/' como el separador entre palabras. Tras leer el archivo se ensamblan
  // cadenas del siguiente formato: "Daniel_Castro/1631966878/2/4.6/8.8/5.1/1"
  // Lo cual es facilmente parseado despues del codigo importado.

  // Codigo importado desde:
  // https://www.geeksforgeeks.org/cpp/stdistream_iterator-stdostream_iterator-c-stl/
  vector<string> strings_vector;
  vector<Alumno> alumnos;

  istream_iterator<string> file_iterator(file);
  istream_iterator<string> eos;
  ostream_iterator<string> cout_iterator(cout, " ");
  copy(file_iterator, eos, back_inserter(strings_vector));

  copy(strings_vector.begin(), strings_vector.end(), cout_iterator);
  // fin del codigo importado

  for (string i : strings_vector) {
    // primero encontramos las posiciones de todos los separadores
    vector<size_t> separadores = {0};
    fr(j, 6) separadores.push_back(i.find('/', separadores[j]));

    // luego ensamblamos el struct con .substr()
    Alumno alumno;
    alumno.nombre = i.substr(separadores[0], separadores[1]);
    alumno.matricula =
        i.substr(separadores[1], (separadores[2] - separadores[1]));
    alumno.calif[0] =
        stof(i.substr(separadores[2], (separadores[3]) - separadores[2]));
    alumno.calif[1] =
        stof(i.substr(separadores[3], (separadores[4]) - separadores[3]));
    alumno.calif[2] =
        stof(i.substr(separadores[4], (separadores[5]) - separadores[4]));
    alumno.grupo =
        stoi(i.substr(separadores[5], (separadores[6]) - separadores[5]));

    alumnos.push_back(alumno);
  }

  // si existe una solucion mas facil que puede procesar caracteres en UTF-8 me
  // encantaria saberla. Lamentablemente no he encontrado documentacion hecha
  // para humanos y principiantes - manuscritos tecnicos del cppreference.com y
  // cplusplus.com son muy dificiles de entender.

  cout << thick_separator;
  for (Alumno i : alumnos) {
    cout << thin_separator;
    cout << "Nombre: " << i.nombre << endl;
    cout << "Matricula: " << i.matricula << endl;
    cout << "Calificaciones: " << i.calif[0] << "   " << i.calif[1] << "   "
         << i.calif[2] << "   " << endl;
    cout << "ID del grupo: " << i.grupo << endl;
  }
  cout << thick_separator;

  file.close();
  return 0;
}
