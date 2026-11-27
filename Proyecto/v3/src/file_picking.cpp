// no queria poner codigo crudo en main, pero tampoco pertenece en saving.
// Iba a ser menus.cpp pero tampoco mover el menu principal y switch aqui.

#include "custom.cpp"

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

string pick_file() {
  // encontramos y escribimos los archivos disponibles
  auto files = find_files();
  if (!files.empty()) {
    cout << "Archivos binarios disponibles:\n";
    fr(i, files.size()) cout << i + 1 << ") " << files[i].filename().string()
                             << "\n";
  }
  cout << "0) Crear un archivo nuevo\n" << thin_separator;

  // seleccionamos un archivo
  int choice;
  while (true) {
    choice = stoi(get_regexed_input("Selecciona un archivo: ", digit_regex,
                                    "Entra un numero por favor."));

    if (choice >= 0 && choice <= files.size())
      break;
    cout << "Opcion fuera del rango, intente otra vez\n" << thin_separator;
  }

  // creamos nuevo archivo y lo retornamos
  if (choice == 0) {
    bool created_succesfully = false;
    string new_name;
    do {
      new_name = get_regexed_input(
          "Escribe el nuevo nombre del archivo: ", filename_regex,
          "Entra un nombre valido por favor (solo simbolos ASCII).");
      new_name.append(".bin");

      // existe?
      if (exists(new_name)) {
        // no good prospect in overriding non-file items
        if (!is_regular_file(new_name)) {
          cerr << new_name
               << " ya existe y no es un archivo regular. Elige otro nombre\n"
               << thin_separator;
          continue;
        }

        // asks if we want to overwrite
        string overwrite_input = "El archivo " + new_name +
                                 " ya existe. Desea sobrescribirlo? (s/n)";
        string answer = get_regexed_input(
            overwrite_input.c_str(), confirm_regex, "Entra S o N por favor.");
        if (answer != "s" && answer != "S" && answer != "y" && answer != "Y") {
          cout << "Entonces, elige otro nombre.\n" << thin_separator;
          continue; // pedimos otro nombre sin tocar el archivo
        } else {
          cout << "Sobreescribiendo " << new_name << "...\n";
        }
      }

      fstream file(new_name, ios::out | ios::trunc | ios::binary);
      created_succesfully = file.is_open();
      if (!created_succesfully) {
        cerr << "No se pudo crear el archivo " << new_name
             << ". Intente otra vez\n"
             << thin_separator;
      } else {
        cout << "El archivo fue sobreescribido exitosamente.\n\n";
      }
    } while (!created_succesfully);
    return new_name;
  }

  // retornamos nombre del archivo
  return files[choice - 1].filename().string();
}
