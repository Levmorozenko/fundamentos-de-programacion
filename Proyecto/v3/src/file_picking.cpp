// no queria poner codigo crudo en main, pero tampoco pertenece en saving.
// Iba a ser menus.cpp pero tampoco mover el menu principal y switch aqui.

#include "custom.cpp"
#include <filesystem>
#include <vector>

using namespace std::filesystem;

vector<path> find_files() {
  vector<path> list;
  for (const auto &item : directory_iterator(current_path())) {
    if (!item.is_regular_file())
      continue; // evitamos carpetas, symlinks y otros elementos magicos.
    if (item.path().extension().string() == ".bin")
      list.push_back(item.path());
  }
  return list;
}

string pick_file(const string &fallback = "datos.bin") {
  auto files = find_files();
  if (!files.empty()) {
    cout << "Archivos binarios disponibles:\n";
    fr(i, files.size()) cout << i + 1 << ") " << files[i].filename().string()
                             << "\n";
  }

  cout << "0) Crear un archivo nuevo\n" << thin_separator;

  int choice = stoi(get_regexed_input("Selecciona un archivo: ", digit_regex,
                                      "Entra un numero por favor."));

  if (choice == 0) {
    bool created_succesfully;
    string new_name;
    do {
      new_name = get_regexed_input(
          "Escribe el nuevo nombre del archivo: ", ascii_regex,
          "Entra un nombre valido por favor (solo simbolos ASCII).");
      new_name.append(".bin");
      fstream file(new_name, ios::out | ios::trunc | ios::binary);
      created_succesfully = file.is_open();
      if (!created_succesfully) {
        cerr << "No se pudo crear el archivo " << new_name
             << ". Intente otra vez\n"
             << thin_separator;
      }
    } while (!created_succesfully);
    return new_name;
  }
  if (choice < 1 || choice > files.size()) // otra vez off by one....
    return fallback;
  return files[choice - 1].filename().string();
}
