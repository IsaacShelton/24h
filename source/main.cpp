
/*
    The 24 Hour Programming Language Interpreter - Interprets .24h Files
    By Isaac Shelton 5.3.2016

    Instruction List:
        '`' Allocate               Allocates number of cells               `(value).
        '~' Deallocate             Deallocates number of cells             ~(value).
        '^' Set Cell               Sets the cell number                    ^(value).
        '>' Increament Cell        Increaments the cell number             >(value).
        '<' Decreament Cell        Decreaments the cell number             <(value).
        '+' Add To                 Adds to the Current Cell                +(value).
        '-' Subtract From          Subtracts from the Current Cell         -(value).
        '=' Set                    Sets the value of the Current Cell      =(value).
        '!' Print                  Prints the value of the Current Cell    !
        '"' Input                  Inputs an Amount of Characters          "(value).
        '%' Not                    Logical Not of Current Cell value       %
        '&' Goto                   Jumps to that location in the file      &(value).
        '@' Conditional Goto       Jumps to that location if cell is 1     @(value).
        ':' Get Current Cell       Sets the Cell value to the Cell index   :
        '?' Conditional            Evaluates depending on condition        ?(condition)(value).(result cell).
            '=' Checks for equality     ?=100.0.
            '<' Less Than               ?<100.0.
            '>' Greater Than            ?>100.0.
            '{' Less Than or Equal      ?{100.0.
            '}' Greater Than or Equal   ?}100.0.

            If result cell isn't a blank string, the result of the conditional will set the result cell to either 1 or 0
                For example: ?=100.8.
                If the current cell is 100, the cell 8 will be set to 1 otherwise it will be set to 0
            If result cell is a blank string, the result value will be placed into the current cell
                For example: ?=100..
                If the current cell is 100, the current cell will be set to 1 otherwise it will be set to 0
        '.' Terminator             Terminates a value

    hello.24h - example program:
        `1.^0.=72.!=101.!=108.!=108.!=111.!=32.!=87.!=111.!=114.!=108.!=100.!

    echo.24h  - example program:
        `255.^0."255.!>1.!?=0..%@14.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int to_int(string what){
    stringstream ss(what);
    int value;

    ss >> value;
    return value;
}

int main(int argc, char** argv)
{
    if(argc != 2){
        cout << "No file specified" << endl;
        return 1;
    }

    ifstream executable(argv[1], ios::binary | ios::in);
    vector<char> data;
    unsigned int ptr;

    if(executable.is_open()){
        executable.seekg(0, ios::beg);
        char buffer;

        while(!executable.eof()){
            executable.read(&buffer, 1);

            if(executable.eof()) continue;

            if(buffer == '`'){
                string times_str;

                executable.read(&buffer, 1);

                while(buffer != '.'){
                    times_str += buffer;
                    executable.read(&buffer, 1);
                }

                int times = to_int(times_str);

                while(times >= 0){
                    data.push_back('\0');
                    times--;
                }
            }
            else if(buffer == '~'){
                string times_str;

                executable.read(&buffer, 1);

                while(buffer != '.'){
                    times_str += buffer;
                    executable.read(&buffer, 1);
                }

                int times = to_int(times_str);

                while(times >= 0){
                    data.pop_back();
                    times--;
                }
            }
            else if(buffer == '^'){
                string id_str;

                executable.read(&buffer, 1);

                while(buffer != '.'){
                    id_str += buffer;
                    executable.read(&buffer, 1);
                }

                int id = to_int(id_str);

                if(id >= 0){
                    ptr = id;
                }
            }
            else if(buffer == '>'){
                string id_str;

                executable.read(&buffer, 1);

                while(buffer != '.'){
                    id_str += buffer;
                    executable.read(&buffer, 1);
                }

                int id = to_int(id_str);

                if(id >= 0){
                    ptr += id;
                }
            }
            else if(buffer == '<'){
                string id_str;

                executable.read(&buffer, 1);

                while(buffer != '.'){
                    id_str += buffer;
                    executable.read(&buffer, 1);
                }

                int id = to_int(id_str);

                if(id >= 0){
                    ptr -= id;
                }
            }
            else if(buffer == '+'){
                string amount_str;

                executable.read(&buffer, 1);

                while(buffer != '.'){
                    amount_str += buffer;
                    executable.read(&buffer, 1);
                }

                int amount = to_int(amount_str);

                if(ptr >= 0 and ptr < data.size()){
                    data[ptr] += amount;
                }
            }
            else if(buffer == '-'){
                string amount_str;

                executable.read(&buffer, 1);

                while(buffer != '.'){
                    amount_str += buffer;
                    executable.read(&buffer, 1);
                }

                int amount = to_int(amount_str);

                if(ptr >= 0 and ptr < data.size()){
                    data[ptr] -= amount;
                }
            }
            else if(buffer == '='){
                string amount_str;

                executable.read(&buffer, 1);

                while(buffer != '.'){
                    amount_str += buffer;
                    executable.read(&buffer, 1);
                }

                int amount = to_int(amount_str);

                if(ptr >= 0 and ptr < data.size()){
                    data[ptr] = amount;
                }
            }
            else if(buffer == '!'){
                if(ptr >= 0 and ptr < data.size()){
                    cout << data[ptr];
                }
            }
            else if(buffer == '"'){
                string amount_str;

                executable.read(&buffer, 1);

                while(buffer != '.'){
                    amount_str += buffer;
                    executable.read(&buffer, 1);
                }

                int amount = to_int(amount_str);

                if(ptr >= 0 and ptr < data.size() and amount > 0){
                    cin.get(&data[ptr], amount+1);
                }
            }
            else if(buffer == '?'){
                string amount_str;
                string output_str;
                char comparison;

                executable.read(&comparison, 1);
                executable.read(&buffer, 1);

                while(buffer != '.'){
                    amount_str += buffer;
                    executable.read(&buffer, 1);
                }

                executable.read(&buffer, 1);

                while(buffer != '.'){
                    output_str += buffer;
                    executable.read(&buffer, 1);
                }

                int amount = to_int(amount_str);
                int result_ptr = to_int(output_str);

                if(output_str == ""){
                    result_ptr = ptr;
                }

                if(ptr >= 0 and ptr < data.size()){
                    if(comparison == '='){
                        if(int(data[ptr]) == amount){
                            data[result_ptr] = 1;
                        } else {
                            data[result_ptr] = 0;
                        }
                    }
                    else if(comparison == '>'){
                        if(int(data[ptr]) > amount){
                            data[result_ptr] = 1;
                        } else {
                            data[result_ptr] = 0;
                        }
                    }
                    else if(comparison == '<'){
                        if(int(data[ptr]) < amount){
                            data[result_ptr] = 1;
                        } else {
                            data[result_ptr] = 0;
                        }
                    }
                    else if(comparison == '{'){
                        if(int(data[ptr]) <= amount){
                            data[result_ptr] = 1;
                        } else {
                            data[result_ptr] = 0;
                        }
                    }
                    else if(comparison == '}'){
                        if(int(data[ptr]) >= amount){
                            data[result_ptr] = 1;
                        } else {
                            data[result_ptr] = 0;
                        }
                    }
                }
            }
            else if(buffer == '&'){
                string id_str;

                executable.read(&buffer, 1);

                while(buffer != '.'){
                    id_str += buffer;
                    executable.read(&buffer, 1);
                }

                int id = to_int(id_str);

                if(id >= 0){
                    executable.seekg(id);
                }
            }
            else if(buffer == '@'){
                string id_str;

                executable.read(&buffer, 1);

                while(buffer != '.'){
                    id_str += buffer;
                    executable.read(&buffer, 1);
                }

                int id = to_int(id_str);

                if(id >= 0){
                    if(data[ptr] == 1){
                        executable.seekg(id);
                    }
                }
            }
            else if(buffer == '%'){
                if(ptr >= 0 and ptr < data.size()){
                    if(data[ptr] == 0){
                        data[ptr] = 1;
                    }
                    else if(data[ptr] == 1){
                        data[ptr] = 0;
                    }
                }
            }
            else if(buffer == ':'){
                if(ptr >= 0 and ptr < data.size()){
                    data[ptr] = ptr;
                }
            }
        }

        executable.close();
    }

    return 0;
}
