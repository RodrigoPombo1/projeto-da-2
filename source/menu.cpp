//
// Created by rodri on 14/05/2024.
//

#include "menu.h"

using namespace std;

/// @brief Prints current menu and gets the input corresponding to the choice from the options
/// @param current_selection current menu selected
/// @param options vector with the diferent options in the menu
/// @param is_main_menu boolean value corresponding to being the main menu or not
/// @return choice made
int menu::print_menu_and_get_choice_input(string current_selection, vector<string> options, bool is_main_menu) {
    int input;
    bool valid_input = false;
    while (!valid_input) {
        cout << current_selection << endl;

        this->print_separator();

        for (int i = 0; i < options.size(); i++) {
            cout << i + 1 << ". " << options[i] << endl;
        }
        if (!is_main_menu) {
            cout << "0. Go back to previous menu\n";
            cout << "-1. Go back to main menu\n";
        } else {
            cout << "0. Exit\n";
        }
        this->print_separator();

        cout << "Chose one of the options above by entering the corresponding number and press enter\n";
        cin >> input;
        if (input >= -1 && input <= (int) options.size() && !is_main_menu) {
            valid_input = true;
        } else if (input >= 0 && input <= (int) options.size() && is_main_menu) {
            valid_input = true;
        } else {
            cout << "Invalid input, please try again\n";
        }
    }
    return input;
}

/// @brief Prints a separator
void menu::print_separator() {
    cout << "---------------------------------------------------------------------------\n";
}

/// @brief Prints current menu and gets number input
/// @param current_selection current menu selected
/// @return number input chosen
int menu::print_menu_and_get_number_input(string current_selection) {
    int input;
    bool valid_input = false;
    while (!valid_input) {
        cout << current_selection << endl;

        this->print_separator();

        cout << "Enter a number above 1" << " and press enter\n";

        this->print_separator();

        cout << "0. Go back to previous menu\n";
        cout << "-1. Go back to main menu\n";

        this->print_separator();

        cout << "Chose one of the options above by entering the corresponding number and press enter\n";
        cin >> input;
        if (input >= -1) {
            valid_input = true;
        } else {
            cout << "Invalid input, please try again\n";
        }
    }
    return input;
}

/// @brief Prints current menu and gets string input
/// @param current_selection current menu selected
/// @return string input chosen
string menu::print_menu_and_get_string_input(string current_selection) {
    string input;
    bool valid_input = false;
    while (!valid_input) {
        cout << current_selection << endl;

        this->print_separator();

        cout << "Enter a string and press enter\n";

        this->print_separator();

        cout << "0. Go back to previous menu\n";
        cout << "-1. Go back to main menu\n";

        this->print_separator();

        cout << "Chose one of the options above by entering a string or the corresponding number and press enter\n";
        cin >> input;
        if (input != "") {
            valid_input = true;
        } else {
            cout << "Invalid input, please try again\n";
        }
    }
    return input;
}

/// @brief Prints results from the request and gets choice input
/// @param current_selection current menu selected
/// @param results vector with the results from the request made
/// @return input chosen
int menu::print_result_and_get_choice_input(std::string current_selection, std::vector<std::string> results) {
    int input;
    bool valid_input = false;
    while (!valid_input) {
        cout << current_selection << endl;

        this->print_separator();

        for (int i = 0; i < results.size(); i++) {
            cout << i + 1 << ". " << results[i] << endl;
        }

        this->print_separator();

        cout << "0. Go back to previous menu\n";
        cout << "-1. Go back to main menu\n";

        this->print_separator();

        cout << "Chose one of the options above by entering the corresponding number and press enter\n";
        cin >> input;
        if (input >= -1 && input <= 0) {
            valid_input = true;
        } else {
            cout << "Invalid input, please try again\n";
        }
    }
    return input;
}

menu::menu() {
    this->go_back_to_main_menu = false;
    this->first_time_running = true;
    this->csv_file_type_selection_menu();
}
void menu::csv_file_type_selection_menu() {
    while (this->first_time_running) {
        vector<string> options = {"Toy-Graphs", "Extra Fully Connected Graphs", "Real-world Graphs"};
        int input = this->print_menu_and_get_choice_input("Select the type of file you want to read from", options,
                                                          true);
        switch (input) {
            case 0:
                return;
            case 1:
                this->Request.setGraphTypeToRead(1);
                this->csv_file_name_selection_menu();
                return;
            case 2:
                this->Request.setGraphTypeToRead(2);
                this->csv_file_name_selection_menu();
                return;
            case 3:
                this->Request.setGraphTypeToRead(3);
                this->csv_file_name_selection_menu();
                return;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
    while (!go_back_to_main_menu) {
        vector<string> options = {"Toy-Graphs", "Extra Fully Connected Graphs", "Real-world Graphs"};
        int input = this->print_menu_and_get_choice_input("Select the type of file you want to read from", options);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            case 1:
                this->Request.setGraphTypeToRead(1);
                this->csv_file_name_selection_menu();
                return;
            case 2:
                this->Request.setGraphTypeToRead(2);
                this->csv_file_name_selection_menu();
                return;
            case 3:
                this->Request.setGraphTypeToRead(3);
                this->csv_file_name_selection_menu();
                return;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

void menu::csv_file_name_selection_menu() {
    vector<string> toy_graphs_names = {"shipping.csv", "stadiums.csv", "tourism.csv"};
    vector<string> extra_fully_connected_graphs_names = {"edges_25.csv", "edges_50.csv", "edges_75.csv", "edges_100.csv", "edges_200.csv", "edges_300.csv", "edges_400.csv", "edges_500.csv", "edges_600.csv", "edges_700.csv", "edges_800.csv", "edges_900.csv"};
    vector<string> real_world_graphs_names = {"graph 1", "graph 2", "graph 3"};
    while (this->first_time_running) {
        switch (this->Request.getGraphTypeToRead()) {
            case 1: {
                int input = this->print_menu_and_get_choice_input("Select the toy graph you want to read from",
                                                                  toy_graphs_names, true);
                switch (input) {
                    case 0:
                        return;
                    case 1:
                        this->Request.setGraphFile(1);
                        this->first_time_running = false;
                        this->main_menu();
                        return;
                    case 2:
                        this->Request.setGraphFile(2);
                        this->first_time_running = false;
                        this->main_menu();
                        return;
                    case 3:
                        this->Request.setGraphFile(3);
                        this->first_time_running = false;
                        this->main_menu();
                        return;
                    default:
                        cout << "Invalid input, please try again\n";
                        break;
                }
            }
            break;
            case 2: {
                int input = this->print_menu_and_get_choice_input(
                        "Select the extra fully connected graph you want to read from",
                        extra_fully_connected_graphs_names, true);
                switch (input) {
                    case 0:
                        return;
                    case 1:
                        this->Request.setGraphFile(1);
                        this->first_time_running = false;
                        this->main_menu();
                        return;
                    case 2:
                        this->Request.setGraphFile(2);
                        this->first_time_running = false;
                        this->main_menu();
                        return;
                    case 3:
                        this->Request.setGraphFile(3);
                        this->first_time_running = false;
                        this->main_menu();
                        return;
                    case 4:
                        this->Request.setGraphFile(4);
                        this->first_time_running = false;
                        this->main_menu();
                        return;
                    case 5:
                        this->Request.setGraphFile(5);
                        this->first_time_running = false;
                        this->main_menu();
                        return;
                    case 6:
                        this->Request.setGraphFile(6);
                        this->first_time_running = false;
                        this->main_menu();
                        return;
                    case 7:
                        this->Request.setGraphFile(7);
                        this->first_time_running = false;
                        this->main_menu();
                        return;
                    case 8:
                        this->Request.setGraphFile(8);
                        this->first_time_running = false;
                        this->main_menu();
                        return;
                    case 9:
                        this->Request.setGraphFile(9);
                        this->first_time_running = false;
                        this->main_menu();
                        return;
                    case 10:
                        this->Request.setGraphFile(10);
                        this->first_time_running = false;
                        this->main_menu();
                        return;
                    case 11:
                        this->Request.setGraphFile(11);
                        this->first_time_running = false;
                        this->main_menu();
                        return;
                    case 12:
                        this->Request.setGraphFile(12);
                        this->first_time_running = false;
                        this->main_menu();
                        return;
                    default:
                        cout << "Invalid input, please try again\n";
                        break;
                }
            }
            break;
            case 3: {
                int input = this->print_menu_and_get_choice_input("Select the real world graph you want to read from",
                                                                  real_world_graphs_names, true);
                switch (input) {
                    case 0:
                        return;
                    case 1:
                        this->Request.setGraphFile(1);
                        this->first_time_running = false;
                        this->main_menu();
                        return;
                    case 2:
                        this->Request.setGraphFile(2);
                        this->first_time_running = false;
                        this->main_menu();
                        return;
                    case 3:
                        this->Request.setGraphFile(3);
                        this->first_time_running = false;
                        this->main_menu();
                        return;
                    default:
                        cout << "Invalid input, please try again\n";
                        break;
                }
            }
            break;
        }
    }
    while (!go_back_to_main_menu) {
        switch (this->Request.getGraphTypeToRead()) {
            case 1: {
                int input = this->print_menu_and_get_choice_input("Select the toy graph you want to read from",
                                                                  toy_graphs_names);
                switch (input) {
                    case -1:
                        this->go_back_to_main_menu = true;
                        return;
                    case 0:
                        return;
                    case 1:
                        this->Request.setGraphFile(1);
                        this->go_back_to_main_menu = true;
                        return;
                    case 2:
                        this->Request.setGraphFile(2);
                        this->go_back_to_main_menu = true;
                        return;
                    case 3:
                        this->Request.setGraphFile(3);
                        this->go_back_to_main_menu = true;
                        return;
                    default:
                        cout << "Invalid input, please try again\n";
                        break;
                }
                break;
            }
            case 2: {
                int input = this->print_menu_and_get_choice_input(
                        "Select the extra fully connected graph you want to read from",
                        extra_fully_connected_graphs_names);
                switch (input) {
                    case -1:
                        this->go_back_to_main_menu = true;
                        return;
                    case 0:
                        return;
                    case 1:
                        this->Request.setGraphFile(1);
                        this->go_back_to_main_menu = true;
                        return;
                    case 2:
                        this->Request.setGraphFile(2);
                        this->go_back_to_main_menu = true;
                        return;
                    case 3:
                        this->Request.setGraphFile(3);
                        this->go_back_to_main_menu = true;
                        return;
                    case 4:
                        this->Request.setGraphFile(4);
                        this->go_back_to_main_menu = true;
                        return;
                    case 5:
                        this->Request.setGraphFile(5);
                        this->go_back_to_main_menu = true;
                        return;
                    case 6:
                        this->Request.setGraphFile(6);
                        this->go_back_to_main_menu = true;
                        return;
                    case 7:
                        this->Request.setGraphFile(7);
                        this->go_back_to_main_menu = true;
                        return;
                    case 8:
                        this->Request.setGraphFile(8);
                        this->go_back_to_main_menu = true;
                        return;
                    case 9:
                        this->Request.setGraphFile(9);
                        this->go_back_to_main_menu = true;
                        return;
                    case 10:
                        this->Request.setGraphFile(10);
                        this->go_back_to_main_menu = true;
                        return;
                    case 11:
                        this->Request.setGraphFile(11);
                        this->go_back_to_main_menu = true;
                        return;
                    case 12:
                        this->Request.setGraphFile(12);
                        this->go_back_to_main_menu = true;
                        return;
                    default:
                        cout << "Invalid input, please try again\n";
                        break;
                }
                break;
            }
            case 3: {
                int input = this->print_menu_and_get_choice_input("Select the real world graph you want to read from",
                                                                  real_world_graphs_names);
                switch (input) {
                    case -1:
                        this->go_back_to_main_menu = true;
                        return;
                    case 0:
                        return;
                    case 1:
                        this->Request.setGraphFile(1);
                        this->go_back_to_main_menu = true;
                        return;
                    case 2:
                        this->Request.setGraphFile(2);
                        this->go_back_to_main_menu = true;
                        return;
                    case 3:
                        this->Request.setGraphFile(3);
                        this->go_back_to_main_menu = true;
                        return;
                    default:
                        cout << "Invalid input, please try again\n";
                        break;
                }
                break;
            }
        }
    }
}

void menu::main_menu() {
    while (true) {
        this->go_back_to_main_menu = false;
        string current_menu = "Main menu";
        vector<string> options = {"T2.1 Backtracking (can be incomplete and not fully connected)", "T2.2 Triangular Approximation Heuristic (must have chosen fully connected and complete graph)", "T2.3 Other Heuristic (must have chosen fully connected and complete graph)", "T2.4 Real World Graph (must have chosen fully connected and complete graph)", "Choose different csv file"};
        int input = this->print_menu_and_get_choice_input(current_menu, options, true);
        switch (input) {
            case 0:
                return;
            case 1:
                this->t2_1_backtracking();
                break;
            case 2:
                this->t2_2_triangular_approximation_heuristic();
                break;
            case 3:
                this->t2_3_other_heuristic();
                break;
            case 4:
                this->real_world_graph_select_starting_node();
                break;
            case 5:
                this->csv_file_type_selection_menu();
                break;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

void menu::real_world_graph_select_starting_node() {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Real World Graph - Select starting node";
        int input = this->print_menu_and_get_number_input_for_0(current_menu);
        switch (input) {
            case -2:
                this->go_back_to_main_menu = true;
                return;
            case -1:
                return;
            default:
                this->t2_4_real_world_graph(input);
                break;
        }
    }
}

int menu::print_menu_and_get_number_input_for_0(string current_selection) {
    int input;
    bool valid_input = false;
    while (!valid_input) {
        cout << current_selection << endl;

        this->print_separator();

        cout << "Enter a number above 0 (included)" << " and press enter\n";

        this->print_separator();

        cout << "-1. Go back to previous menu\n";
        cout << "-2. Go back to main menu\n";

        this->print_separator();

        cout << "Chose one of the options above by entering the corresponding number and press enter\n";
        cin >> input;
        if (input >= -2) {
            valid_input = true;
        } else {
            cout << "Invalid input, please try again\n";
        }
    }
    return input;
}

void menu::t2_4_real_world_graph(int input) {
    while (!this->go_back_to_main_menu) {
        string current_menu = "T2.4 Real World Graph";
        vector<string> result; // TODO get results from request // with starting node in the input
        int input = this->print_result_and_get_choice_input(current_menu, result);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

void menu::t2_3_other_heuristic() {
    while (!this->go_back_to_main_menu) {
        string current_menu = "T2.3 Other Heuristic";
        vector<string> result = this->Request.print_result_christofides_heuristic();
        int input = this->print_result_and_get_choice_input(current_menu, result);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

void menu::t2_2_triangular_approximation_heuristic() {
    while (!this->go_back_to_main_menu) {
        string current_menu = "T2.2 Triangular Approximation Heuristic";
        vector<string> result = this->Request.print_result_greedy_heuristic();
        int input = this->print_result_and_get_choice_input(current_menu, result);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

void menu::t2_1_backtracking() {
    while (!this->go_back_to_main_menu) {
        string current_menu = "T2.1 Backtracking";
        vector<string> result = this->Request.print_result_backtracking();
        int input = this->print_result_and_get_choice_input(current_menu, result);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}