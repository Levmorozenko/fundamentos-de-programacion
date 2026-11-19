#include "input.cpp"
#include "menus.cpp"
#include "saving.cpp"
#include "uni.cpp"


int main() {
  setup_console();

  Uni uni;
  load(uni);

  while (true) {
    clear_screen();
    cout << "===== Uni =====\n";
    cout << "1) Register\n";
    cout << "2) List\n";
    cout << "3) Queries\n";
    cout << "4) Save\n";
    cout << "5) Reload\n";
    cout << "0) Exit\n";

    int option = read_int("Option: ", 0, 5);
    switch (option) {
    case 1:
      register_menu(uni);
      break;
    case 2:
      list_menu(uni);
      break;
    case 3:
      query_menu(uni);
      break;
    case 4:
      save(uni);
      cout << "Saved.\n";
      break;
    case 5:
      load(uni);
      break;
    case 0:
      save(uni);
      return 0;
    }
  }
}
