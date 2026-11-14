// Este pequeño codigo hecho por Opencode repara los problemas con imprime de
// los acentos. Es decir, mi conclusion de la exploracion de UTF-8 y C++ ha sido
// correcta - no es culpa de ninguno mencionado, es el maldito Windows.
#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
static void set_utf8() {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8); // cout
  SetConsoleCP(CP_UTF8);       // getline
#endif
}

#include "faker-cxx/number.h"
#include "faker-cxx/person.h"
#include "faker-cxx/string.h"
#include <fstream>

#include <cmath>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

// short version of for -> fr
#define fr(i, b) for (int i = 0; i < b; i++)
// short version of "for object" -> fr o -> fro
#define fro(i, a) for (auto i : a)
#define thick_separator "================================================\n";
#define thin_separator "------------------------------------------------\n";

using namespace std;

struct Alumno {
  string nombre;
  string matricula;
  float calif[3];
  int grupo;
  optional<float> promedio;
};

Alumno crear_alumno() {
  Alumno alumno;
  alumno.nombre = faker::person::fullName(faker::Locale::es_MX);
  alumno.matricula = faker::string::numeric(10);
  fr(i, 3) alumno.calif[i] = round(faker::number::decimal(10.0) * 10.0) / 10.0;
  alumno.grupo = faker::number::integer(1, 5);

  return alumno;
}

void imprimir_alumnos(const vector<Alumno> &alumnos) {
  cout << thick_separator;
  for (Alumno i : alumnos) {
    cout << thin_separator;

    cout << "Nombre: " << i.nombre << "\n";
    cout << "Matricula: " << i.matricula << "\n";
    cout << "Calificaciones: " << i.calif[0] << "   " << i.calif[1] << "   "
         << i.calif[2] << "   " << "\n";
    cout << "ID del grupo: " << i.grupo << "\n";
    if (i.promedio.has_value()) {
      // por si acaso que me vuelve paranoico falta de .unwrap
      cout << "Promedio: " << i.promedio.value() << "\n";
    }
  }
  cout << thick_separator;
}

void almacenar_alumno_texto(fstream &file, const Alumno &i) {
  file << i.nombre << "/" << i.matricula << "/" << i.calif[0] << "/"
       << i.calif[1] << "/" << i.calif[2] << "/" << i.grupo << "\n";
}

Alumno parsear_alumno_txt(const string &line) {
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

  return alumno;
}

void almacenar_alumno_bin(fstream &file, const Alumno &i) {
  // yo presenté esto

  size_t nombre_size = i.nombre.length();
  file.write(reinterpret_cast<const char *>(&nombre_size), sizeof(nombre_size));
  file.write(i.nombre.c_str(), nombre_size);

  size_t matricula_size = i.matricula.length();
  file.write(reinterpret_cast<const char *>(&matricula_size),
             sizeof(matricula_size));
  file.write(i.matricula.c_str(), matricula_size);

  // sabemos que el tamaño de calif[3] y grupo son 12 y 4 bytes
  // respectivamente.
  file.write(reinterpret_cast<const char *>(&i.calif), sizeof(i.calif));
  file.write(reinterpret_cast<const char *>(&i.grupo), sizeof(i.grupo));
}

Alumno leer_alumno_bin(fstream &file) {
  // bendiciones a https://www.geeksforgeeks.org/cpp/file-handling-c-classes/
  Alumno alumno;

  size_t nombre_size;
  file.read(reinterpret_cast<char *>(&nombre_size), sizeof(nombre_size));
  char *name_buffer = new char[nombre_size + 1];
  file.read(name_buffer, nombre_size);
  name_buffer[nombre_size] = '\0';
  alumno.nombre = name_buffer;

  size_t matricula_size;
  file.read(reinterpret_cast<char *>(&matricula_size), sizeof(matricula_size));
  char *matricula_buffer = new char[matricula_size + 1];
  file.read(matricula_buffer, matricula_size);
  matricula_buffer[matricula_size] = '\0';
  alumno.matricula = matricula_buffer;

  file.read(reinterpret_cast<char *>(&alumno.calif), sizeof(alumno.calif));
  file.read(reinterpret_cast<char *>(&alumno.grupo), sizeof(alumno.grupo));

  delete[] name_buffer;
  delete[] matricula_buffer;

  return alumno;
}
