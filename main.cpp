/*
* Name: main.cpp
* Purpose: Matrix and solving equations
* @author mmodzel2
* @version 1.0 20-04-2017
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <assert.h>

#include "console.hpp"
#include "equation.hpp"
#include "matrix.hpp"
#include "test.hpp"

using namespace std;

unsigned int help(Console* console, void** args);

int main(){
    Console* console;
    console = new Console(cout);
    string str;

    Test<double>::test_assert(console,nullptr);

    if (console == nullptr){
        cout << "Error. No free memory." << endl;
        return 1;
    }

    //register commands to console interface
    console->register_instruction(Matrix<double>::Create_Matrix,"create",4,8,7,7,22);
    console->register_instruction(Matrix<double>::Add_Matrix,"add",2,11,11);
    console->register_instruction(Matrix<double>::Mul_Matrix,"mul",2,11,11);
    console->register_instruction(Matrix<double>::Det_Matrix,"det",1,11);
    console->register_instruction(Matrix<double>::Rank_Matrix,"rank",1,11);
    console->register_instruction(Matrix<double>::Look_Matrix,"look",1,11);
    console->register_instruction(Matrix<double>::Characteristic_Matrix,"c",1,11);
    console->register_instruction(Matrix<double>::Characteristic_Matrix,"characteristic",1,11);
    console->register_instruction(Matrix<double>::Get_Matrix,"get",3,11,7,7);
    console->register_instruction(Matrix<double>::Set_Matrix,"set",4,11,7,7,10);
    console->register_instruction(Matrix<double>::Delete_Matrix,"delete",1,11);

    console->register_instruction(matrix_equation,"solve",2,11,11);

    console->register_instruction(help,"help",0);
    console->register_instruction(help,"h",0);

    console->register_instruction(Test<double>::test,"test",0);
    console->register_instruction(Test<double>::test,"t",0);

    cout << "Write an instruction:" << endl;
    while(1){
        getline(cin,str);
        if (str == "exit" || str == "quit") break;
        console->parse(str.c_str());
    }

    return 0;
}

unsigned int help(Console* console, void** args){ //help function for console interface
    (console->get_stream()) << "create [matrix_name] [rows] [columns] [coefficients]" << std::endl;
    (console->get_stream()) << "add [matrix_name1] [matrix_name2]" << std::endl;
    (console->get_stream()) << "mul [matrix_name1] [matrix_name2]" << std::endl;
    (console->get_stream()) << "det [matrix_name]" << std::endl;
    (console->get_stream()) << "rank [matrix_name]" << std::endl;
    (console->get_stream()) << "look [matrix_name] - write coefficients" << std::endl;
    (console->get_stream()) << "c [matrix_name] - show characteristic" << std::endl;
    (console->get_stream()) << "solve [matrix_name_A] [matrix_name_B]" << std::endl;
    (console->get_stream()) << "get [matrix_name] [row] [column]" << std::endl;
    (console->get_stream()) << "set [matrix_name] [row] [column] [coefficient]" << std::endl;
    (console->get_stream()) << "delete [matrix_name]" << std::endl;

    return 0;
}


