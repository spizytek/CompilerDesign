#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <optional>
#include <vector>



enum class TokenType{
    _return, //return
    int_lit, //int literal
    semi //semicolon
};

struct Token  {
    TokenType type;
    std::optional<std::string> value;
};

std::string tokens_to_asm(const std::vector <Token> &tokens){

    std::stringstream output; 
    output << "global start\n_start:\n";


    for (int i = 0; i < tokens.size(); i++){
        const Token &token = tokens.at(i);

        if(token.type == TokenType::_return){
            if (i+1 < tokens.size() && tokens.at(i+1).type == TokenType::int_lit){

                if (i+2 < tokens.size() && tokens.at(i+2).type == TokenType::semi){

                    output << "    mov rax, 60\n";
                    output << "    mov rdi, " << tokens.at(i +1).value.value() << "\n";
                    output << "    syscall";

                }

            }
            
        }
    }
    return output.str();

}

std::vector<Token> tokenize(const std::string &str) {

    std::vector<Token> tokens{};
    std::string buffer;
    for (int i=0; i < str.length(); i++){
        // ensure each syntax does not start with a numeric values 
        // Also, parse the rest of your file content as alphanumeric.
        char c = str.at(i);

        if (std::isalpha(c)){
            // beginning of a syntax detected.
            buffer.push_back(c);
            // increment the index "i", to point to the next character
            i++;
            while(std::isalnum(str.at(i))){
                // parse the remaining alpha numeric characters till the
                // you encounter " " or 
                buffer.push_back(str.at(i));
                // increment the index "i", to point to the next character
                i++;

            }
            // At this point "i" would be pointing to the non-alphanumeric character
            // ///decrement "i"

            i--;

            if(buffer == "return"){
                tokens.push_back({.type = TokenType::_return});
                buffer.clear(); 
                continue;
            }else{
                std::cerr<<"Invalid syntax"<<std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (std::isspace(c)){
                continue;
        }
        else if (c == ';'){
            tokens.push_back({.type = TokenType::semi});
        }
        else if (std::isdigit(c)){
            buffer.push_back(c);
            i++;
            // Continue pushing back if its numeric
            while(std::isdigit(str.at(i))){
                buffer.push_back(str.at(i));
                i++;                        
            }      
            i--;
            tokens.push_back({.type = TokenType::int_lit, .value = buffer});
            buffer.clear(); 
        }

        else{
            std::cerr<<"Incorrect command! "<<std::endl;
            std::cerr<<"<command> <hyro.hy>"<<std::endl;
            exit(EXIT_FAILURE);
        }
    }
    return tokens;
}

int main(int argc, char *argv[]){

    if(argc != 2){
        std::cerr<<"Incorrect command! Correct usage is"<<std::endl;
        std::cerr<<"<command> <hydro.hy>"<<std::endl;
        return EXIT_FAILURE;
    }

    std::string contents;
    {
        std::stringstream  str_stream;
        std::fstream input(argv[1], std::ios::in);
        str_stream << input.rdbuf();
        contents = str_stream.str();
    }

    std::vector<Token> tokens = tokenize(contents);

    {
        std::fstream file("out.asm", std::ios::out);
        file << tokens_to_asm(tokens);
    }

    //run the compiled code via nasm (call the assembler)
    system("nasm -felf64 out.asm");
    system("ld -o out out.o");

    return EXIT_SUCCESS;
    
}