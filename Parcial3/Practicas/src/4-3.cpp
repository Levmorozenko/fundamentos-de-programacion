// El archivo binario deberia ser mas rapido en procesar. Iterar sobre
// strings, en respeto a todos sus factores, DEBE ser mas lento que una lectura
// directa.... verdad? Resultados estan al final del codigo.
//
// Este codigo es una amalgamacion de los codigos entre 1.cpp - 4-2.cpp, mas la
// lectura binaria.
//
// Para replicar la prueba, corre la practica 1, practica 4-2, y ultimamente
// 4-3, en orden respectivo. Recuerde ajustar cantidad de intentos si esta
// tardando mucho.

#include "custom.cpp"
#include <chrono>

long long binary() {
  chrono::steady_clock::time_point begin = chrono::steady_clock::now();

  ifstream file("Alumnos.bin", ios::binary);
  if (!file.is_open()) {
    cerr << "El archivo no pudo abrirse.\n";
    return 1;
  }

  // bendiciones a https://www.geeksforgeeks.org/cpp/file-handling-c-classes/
  vector<Alumno> alumnos;
  while (file.peek() != EOF) {
    Alumno alumno;

    size_t nombre_size;
    file.read(reinterpret_cast<char *>(&nombre_size), sizeof(nombre_size));
    char *name_buffer = new char[nombre_size + 1];
    file.read(name_buffer, nombre_size);
    name_buffer[nombre_size] = '\0';
    alumno.nombre = name_buffer;

    size_t matricula_size;
    file.read(reinterpret_cast<char *>(&matricula_size),
              sizeof(matricula_size));
    char *matricula_buffer = new char[matricula_size + 1];
    file.read(matricula_buffer, matricula_size);
    matricula_buffer[matricula_size] = '\0';
    alumno.matricula = matricula_buffer;

    file.read(reinterpret_cast<char *>(&alumno.calif), sizeof(alumno.calif));
    file.read(reinterpret_cast<char *>(&alumno.grupo), sizeof(alumno.grupo));

    alumnos.push_back(alumno);
    alumnos.pop_back();

    delete[] name_buffer;
    delete[] matricula_buffer;
  }
  file.close();

  chrono::steady_clock::time_point end = chrono::steady_clock::now();
  return chrono::duration_cast<chrono::microseconds>(end - begin).count();
}

long long text() {
  chrono::steady_clock::time_point begin = chrono::steady_clock::now();

  ifstream file("Alumnos.txt");
  if (!file.is_open()) {
    cerr << "El archivo no pudo abrirse.\n";
    return 1;
  }

  vector<Alumno> alumnos;
  string line;
  while (getline(file, line)) {
    if (line.empty())
      continue;
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
    alumnos.pop_back();
  }
  file.close();

  chrono::steady_clock::time_point end = chrono::steady_clock::now();
  return chrono::duration_cast<chrono::microseconds>(end - begin).count();
}

int main() {
  set_utf8();

  // Se tienen que correr multiples veces para evitar el sesgo de algun spike
  // del uso del CPU.
  int tries = 24;

  vector<long long> binary_times;
  vector<long long> text_times;

  fr(i, tries) binary_times.push_back(binary());
  fr(i, tries) text_times.push_back(text());

  long long sum_binary_time = 0, sum_text_time = 0;
  fro(i, binary_times) sum_binary_time += i;
  fro(i, text_times) sum_text_time += i;

  cout << "Average time elapsed to iterate through a million structs in: \n";
  cout << "Binary: " << sum_binary_time / static_cast<float>(tries)
       << " microseconds on average of " << tries << " times\n";
  cout << "Text:   " << sum_text_time / static_cast<float>(tries)
       << " microseconds on average of " << tries << " times\n";

  return 0;
}

// Resultado:
//      Average time elapsed to iterate through a million structs in:
//      Binary: 305232 microseconds on average of 24 times
//      Text:   803975 microseconds on average of 24 times
//
// Mi teoria fue correcta - es mucho mas rapido procesar estructuras binarias
// que textuales. En este caso la diferencia es ~2.5 veces mas rapido, lo cual
// es significativo. En un millon de structs la diferencia esta entre 0.3 y 0.8
// segundos. En bases de datos mas grandes - esa diferencia es mucho mas
// significativa.
