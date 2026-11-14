// El archivo binario deberia ser mas rapido en procesar. Iterar sobre
// strings, en respeto a todos sus factores, DEBE ser mas lento que una lectura
// directa.... verdad? Resultados estan al final del codigo.
//
// Para replicar la prueba, corre la practica 1, practica 4, y ultimamente
// 4-2, en orden respectivo. Recuerde ajustar cantidad de intentos si esta
// tardando mucho.

#include "custom.cpp"
#include <chrono>

long long binary() {
  chrono::steady_clock::time_point begin = chrono::steady_clock::now();

  fstream file("Alumnos.bin", ios::in | ios::binary);
  if (!file.is_open()) {
    cerr << "El archivo no pudo abrirse.\n";
    file.close();
    exit(1);
  }

  vector<Alumno> alumnos;
  while (file.peek() != EOF) {
    Alumno alumno = leer_alumno_bin(file);
    alumnos.push_back(alumno);
    alumnos.pop_back();
  }
  file.close();

  chrono::steady_clock::time_point end = chrono::steady_clock::now();
  return chrono::duration_cast<chrono::microseconds>(end - begin).count();
}

long long text() {
  chrono::steady_clock::time_point begin = chrono::steady_clock::now();

  fstream file("Alumnos.txt", ios::in);
  if (!file.is_open()) {
    cerr << "El archivo no pudo abrirse.\n";
    file.close();
    exit(1);
  }

  vector<Alumno> alumnos;
  string line;
  while (getline(file, line)) {
    if (line.empty())
      continue;
    Alumno alumno = parsear_alumno_txt(line);

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

// Es el unico que reusa componentes desde practicas 1-4. Si no fuera por
// 4-2.cpp, no habria abstraccion.
