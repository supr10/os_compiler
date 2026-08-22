/*
 *OS Compiler
 *by Nolan Bazin (rguy83667@gmail.com)
 *
 *Credits:
 *asciiart.eu for the ascii art
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>

#define TO_CHAR(x) static_cast<char>(x)

static char logo[] = "the\n"
    "  ___  ____\n"
    " / _ \\/ ___| \n"
    "| | | \\___ \\ \n"
    "| |_| |___) |\n"
    " \\___/|____/ compiler";


static constexpr double version = 0.01;
static constexpr char build_type[] = "alpha";


void invalidate(char* out) {
    //filling the whole out with zeroes
    for (int i = 0;i<511;i++) {
        out[i] = TO_CHAR(0x00);
    }
}

//The compile function transforms the source code (basic-type language) into a hex array
static void compile(char* out, const std::vector<std::string>& opList) {            //assumes the out parameter is 512 bytes long
    if constexpr (sizeof(out)!=512) {
        std::cerr<<"out array too long"<<std::endl;
    }

    invalidate(out);       //making sure the file is 512 bytes

    int caddr = 0;          //current address for writing in output file
    int spf = 0;           //special operation flag, allows to treat operands as arguments instead of operations

    for (const auto& op : opList) {
        switch (spf) {
            case 1:         //printchar
                out[caddr++] = TO_CHAR(0xB4);
                out[caddr++] = TO_CHAR(0x0E);       //mov ah 0x0E
                out[caddr++] = TO_CHAR(0xB0);
                out[caddr++] = TO_CHAR(op[0]);      //mov al op[0]
                out[caddr++] = TO_CHAR(0xCD);
                out[caddr++] = TO_CHAR(0x10);       //int 0x10  (displays ah)
                spf = 0;
                break;
            default: break; //used when spf = 0
        }
        if (op=="printchar"||op=="PRINTCHAR") {
            spf = 1;
        }if (op=="getkey"||op=="GETKEY") {
            out[caddr++] = TO_CHAR(0xB4);
            out[caddr++] = TO_CHAR(0x00);       //mov ah 0x00
            out[caddr++] = TO_CHAR(0xCD);
            out[caddr++] = TO_CHAR(0x16);       //int 0x16   (reads keyboard into al)
        }if (op=="restart"||op=="RESTART") {
            out[caddr++] = TO_CHAR(0xEB);
            out[caddr++] = TO_CHAR(-(caddr+1));


        }
    }


    //operating systems must end with signature 0x55AA
    out[510] = TO_CHAR(0x55);
    out[511] = TO_CHAR(0xAA);
}

static void write_hex_file(std::ofstream* output_file, const char* source) {
    output_file->write(source, 512);
}

static int get_user_action(const int argc, char** argv) {
    if (argc==1) {
        return 0;               // no argument selected
    }if (std::string(argv[1])=="version"||std::string(argv[1])=="-v") {
        return 1;               //shows version and build
    }return 2;                  //just compile the project
}


static std::vector<std::string> get_source_from_file(std::ifstream* input_file) {
    std::vector<std::string> source;
    std::string word;
    while (*input_file>>word) {
        source.push_back(word);
    }
    return source;
}

int main(const int argc, char** argv) {
    switch (get_user_action(argc, argv)) {
        case 0: {
            std::cout<<logo<<"\n"<<std::endl;
            std::cerr<<"No action selected."<<std::endl;
            return 1;
        }
        case 1: {
            std::cout<<logo<<"\n"<<std::endl;
            std::cout<<"The Os Compiler is currently on "<<build_type<<" and on build "<<version<<std::endl;
            return 0;
        }
        case 2: {
            std::ofstream output("out.bin", std::ios::binary);
            std::ifstream input(argv[1]);
            auto source = get_source_from_file(&input);
            char out_hex[512];
            compile(out_hex, source);
            write_hex_file(&output, out_hex);
            input.close();
            output.close();
            return 0;
        }
        default:
            std::cerr<<"no idea of what is supposed to be here..."<<std::endl;
    }
    return 0;
}
