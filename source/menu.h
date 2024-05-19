//
// Created by rodri on 14/05/2024.
//

#ifndef PROJETO_DA_2_MENU_H
#define PROJETO_DA_2_MENU_H

#include "request.h"
#include <string>
#include <iostream>
#include <vector>

class menu {
private:
    bool first_time_running;
    bool go_back_to_main_menu;
    request Request;
    // functions common to all menus
    int print_menu_and_get_choice_input(std::string current_selection, std::vector<std::string> options,
                                        bool is_main_menu = false);
    int print_menu_and_get_number_input(std::string current_selection);
    std::string print_menu_and_get_string_input(std::string current_selection);
    void print_separator();
    int print_result_and_get_choice_input(std::string current_selection, std::vector<std::string> results);


    int print_menu_and_get_number_input_for_0(std::string current_selection);

    void csv_file_type_selection_menu();
    void csv_file_name_selection_menu();

    void main_menu();
    void real_world_graph_select_starting_node();
    void t2_4_real_world_graph(int input);
    void t2_3_other_heuristic();
    void t2_2_triangular_approximation_heuristic();
    void t2_1_backtracking();
public:
    menu();
};


#endif //PROJETO_DA_2_MENU_H
