#pragma once
#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// porque?
// Cada Uni tiene una lista de carreras, maestros y alumnos.
// Cada carrera tiene semestres.
// Cada alumno es parte del semestre especifico, de una carrera
// especifica.
// Cada maestro enseña una lista de semestres especificos.
//
// Debido a eso, la estructura es la siguiente:

struct Group {
  int semester;
  int id;
};

// Porque el Grupo esta separado de la Carrera?
// Una carrera tiene semestres, existe una jerarquia clara entre los dos.
// - Los alumnos no pertenecen a una carrera nada mas, tambien pertenecen a un
//   semestre especifico dentro de la carrera.
// - Un maestro puede enseñar a primeros 6 semestres pero no a ultimos 2.
// Asi mismo, el Grupo "contiene" al Maestro y Alumno en practica, sin ser su
// propietario dentro del codigo.

struct Career {
  string name;
  int id;

  vector<Group> groups; // es propetario de grupos

  Career get();
  Career get_random();
  void print();
};

struct Student {
  string name;
  string id;
  array<float, 3> grades; // mejor que float grades[3]

  int groupId;  // referencia el grupo
  int careerId; // y la carrera

  float average() { return (grades[0] + grades[1] + grades[2]) / 3.0f; }
  Student get();
  Student get_random();
  void print();
};

struct Teacher {
  string name;

  int groupId;  // referencia el grupo
  int careerId; // y la carrera

  Teacher get();
  Teacher get_random();
  void print();
};

struct Uni {
  vector<Career> careers;
  vector<Student> students;
  vector<Teacher> teachers;

  bool add_career();
  bool add_group();
  bool add_student(const Student &student);
  bool add_teacher(const Teacher &teacher);
};
