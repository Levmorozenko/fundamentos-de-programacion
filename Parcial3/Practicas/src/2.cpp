// Leer y reconstruir. Lee ese archivo y reconstruye el arreglo de Alumno en
// memoria. Muestra los datos leídos para confirmar que coinciden.

#include "custom.cpp"

// dado que solo escribimos structs enteros, no tenemos que preocuparnos por
// posibles offsets. En un caso de 0-trust agregaria verificacion propia.
// Por misma razon no habrá verificacion en las siguientes practicas.

int main() {
  set_utf8();

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

    // se cancela el almacenamiento de posiciones por almacenamiento de palabras
    // directamente.
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

    alumnos.push_back(alumno);
  }

  // No he encontrado documentacion hecha para humanos y principiantes -
  // manuscritos tecnicos del cppreference.com y cplusplus.com son muy dificiles
  // de entender.

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
