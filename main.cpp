#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <assert.h>

#include "console.hpp"
#include "equation.hpp"
#include "matrix.hpp"

using namespace std;

unsigned int help(Console* console, void** args);
unsigned int test(Console* console, void** args);
unsigned int test_assert(Console* console, void** args);

int main(){
    Console* console;
    console = new Console(cout);
    string str;

    if (console == nullptr){
        cout << "Error. No free memory." << endl;
        return 1;
    }

    //register commands to graphic interface
    console->register_instruction(Matrix<double>::Create_Matrix,"create",4,8,7,7,22);
    console->register_instruction(Matrix<double>::Add_Matrix,"add",2,11,11);
    console->register_instruction(Matrix<double>::Mul_Matrix,"mul",2,11,11);
    console->register_instruction(Matrix<double>::Det_Matrix,"det",1,11);
    console->register_instruction(Matrix<double>::Rank_Matrix,"rank",1,11);
    console->register_instruction(Matrix<double>::Look_Matrix,"look",1,11);
    console->register_instruction(Matrix<double>::Characteristic_Matrix,"c",1,11);
    console->register_instruction(Matrix<double>::Get_Matrix,"get",3,11,7,7);
    console->register_instruction(Matrix<double>::Set_Matrix,"set",4,11,7,7,10);
    console->register_instruction(Matrix<double>::Delete_Matrix,"delete",1,11);

    console->register_instruction(matrix_equation,"solve",2,11,11);

    console->register_instruction(help,"help",0);
    console->register_instruction(help,"h",0);

    console->register_instruction(test,"test",0);
    console->register_instruction(test,"t",0);

    cout << "Write an instruction:" << endl;
    while(1){
        getline(cin,str);
        if (str == "exit" || str == "quit") break;
        console->parse(str.c_str());
    }

    return 0;
}

unsigned int help(Console* console, void** args){
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

unsigned int test(Console* console, void** args){
    test_assert(console,args);

    (console->get_stream()) << "create testA 4 4 1 2 3 4 3 5 6 9 4 5 3 2 0 0 0 0" << std::endl;
    console->parse("create testA 4 4 1 2 3 4 3 5 6 9 4 5 3 2 0 0 0 0");
    (console->get_stream()) << "create testB 4 1 1 2 3 0" << std::endl;
    console->parse("create testB 4 1 1 2 3 0");
    (console->get_stream()) << "look testA" << std::endl;
    console->parse("look testA");
    (console->get_stream()) << "look testB" << std::endl;
    console->parse("look testB");
    (console->get_stream()) << "det testA" << std::endl;
    console->parse("det testA");
    (console->get_stream()) << "rank testA" << std::endl;
    console->parse("rank testA");
    (console->get_stream()) << "solve testA testB" << std::endl;
    console->parse("solve testA testB");

    (console->get_stream()) << "mul testA testB" << std::endl;
    console->parse("mul testA testB");
    (console->get_stream()) << "look testA" << std::endl;
    console->parse("look testA");

    (console->get_stream()) << "add testA testB" << std::endl;
    console->parse("add testA testB");
    (console->get_stream()) << "look testA" << std::endl;
    console->parse("look testA");

    (console->get_stream()) << "delete testA" << std::endl;
    console->parse("delete testA");
    (console->get_stream()) << "delete testB" << std::endl;
    console->parse("delete testB");

    return 0;
}

unsigned int test_assert(Console* console, void** args){
    Matrix <double> *m = new Matrix <double> (2,2);
    Matrix <double> *m1 = new Matrix <double> (2,2);

    m->set(0,0,1);
    assert(m->get(0,0) == 1);
    assert(m->get(0,1) == 0);
    assert(m->get(1,0) == 0);
    assert(m->get(1,1) == 0);

    m->set(1,1,1);

    m1->set(0,0,3);
    m1->set(0,1,3);
    m1->set(1,0,3);
    m1->set(1,1,3);

    (*m1)+=(*m);

    assert(m1->get(0,0) == 4);
    assert(m1->get(0,1) == 3);
    assert(m1->get(1,0) == 3);
    assert(m1->get(1,1) == 4);

    assert(m1->get(3,3) == 0); //out of bound

    (*m1)*=(*m);

    assert(m1->get(0,0) == 4);
    assert(m1->get(0,1) == 3);
    assert(m1->get(1,0) == 3);
    assert(m1->get(1,1) == 4);

    assert(m1->get(2,1) == 0); //out of bound
    assert(m1->get(2,2) == 0); //out of bound

    assert(m->det() == 1);

    Matrix <double> *m2 = m->inverse();
    assert(m2 != nullptr); //det = 1

    assert(m2->get(0,0) == 1);
    assert(m2->get(0,1) == 0);
    assert(m2->get(1,0) == 0);
    assert(m2->get(1,1) == 1);

    Matrix <double> *m3 = m2->transpose();
    assert(m3 != nullptr);

    assert(m3->get(0,0) == 1);
    assert(m3->get(0,1) == 0);
    assert(m3->get(1,0) == 0);
    assert(m3->get(1,1) == 1);

    delete m;
    delete m1;
    delete m2;
    delete m3;

    return 0;
}


