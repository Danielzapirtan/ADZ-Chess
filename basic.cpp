#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <memory>
#include <cctype>
#include <algorithm>
#include <fstream>

class BasicInterpreter {
private:
    std::map<int, std::string> program;
    std::map<std::string, int> variables;
    std::map<int, int> lineNumbers;
    std::vector<int> executionOrder;
    int currentLineIndex;
    bool running;

    enum class TokenType {
        NUMBER, STRING, IDENTIFIER, OPERATOR, KEYWORD, EOL, UNKNOWN
    };

    struct Token {
        TokenType type;
        std::string value;
        int lineNumber;
    };

public:
    BasicInterpreter() : currentLineIndex(0), running(false) {}

    void loadProgram(const std::vector<std::string>& lines) {
        program.clear();
        lineNumbers.clear();
        executionOrder.clear();
        
        for (const auto& line : lines) {
            auto tokens = tokenize(line);
            if (!tokens.empty() && tokens[0].type == TokenType::NUMBER) {
                int lineNum = std::stoi(tokens[0].value);
                program[lineNum] = line;
                lineNumbers[lineNum] = executionOrder.size();
                executionOrder.push_back(lineNum);
            }
        }
        
        std::sort(executionOrder.begin(), executionOrder.end());
    }

    void loadProgramFromFile(const std::string& filename) {
        program.clear();
        lineNumbers.clear();
        executionOrder.clear();
        
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return;
        }
        
        std::string line;
        while (std::getline(file, line)) {
            // Remove carriage returns for cross-platform compatibility
            line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
            
            if (!line.empty()) {
                auto tokens = tokenize(line);
                if (!tokens.empty() && tokens[0].type == TokenType::NUMBER) {
                    int lineNum = std::stoi(tokens[0].value);
                    program[lineNum] = line;
                    lineNumbers[lineNum] = executionOrder.size();
                    executionOrder.push_back(lineNum);
                }
            }
        }
        
        file.close();
        std::sort(executionOrder.begin(), executionOrder.end());
        std::cout << "Loaded " << executionOrder.size() << " lines from " << filename << std::endl;
    }

    void listProgram() {
        std::cout << "\nProgram Listing:\n";
        for (int lineNum : executionOrder) {
            std::cout << program[lineNum] << std::endl;
        }
        std::cout << std::endl;
    }

    void run() {
        if (executionOrder.empty()) {
            std::cout << "No program loaded." << std::endl;
            return;
        }

        currentLineIndex = 0;
        running = true;
        
        while (running && currentLineIndex < executionOrder.size()) {
            int lineNum = executionOrder[currentLineIndex];
            executeLine(program[lineNum]);
            currentLineIndex++;
        }
    }

    void runInteractive() {
        std::cout << "BASIC Interpreter - Interactive Mode\n";
        std::cout << "Type 'LOAD filename' to load a program, 'LIST' to show program, 'RUN' to execute, 'QUIT' to exit\n";
        
        std::string command;
        while (true) {
            std::cout << "> ";
            std::getline(std::cin, command);
            
            if (command == "QUIT" || command == "quit") {
                break;
            } else if (command.substr(0, 4) == "LOAD" || command.substr(0, 4) == "load") {
                if (command.length() > 5) {
                    std::string filename = command.substr(5);
                    loadProgramFromFile(filename);
                } else {
                    std::cout << "Usage: LOAD filename\n";
                }
            } else if (command == "LIST" || command == "list") {
                listProgram();
            } else if (command == "RUN" || command == "run") {
                run();
            } else if (command == "CLEAR" || command == "clear") {
                program.clear();
                variables.clear();
                lineNumbers.clear();
                executionOrder.clear();
                std::cout << "Program cleared.\n";
            } else {
                std::cout << "Unknown command. Available: LOAD, LIST, RUN, CLEAR, QUIT\n";
            }
        }
    }

private:
    std::vector<Token> tokenize(const std::string& line) {
        std::vector<Token> tokens;
        std::stringstream ss(line);
        std::string token;
        int lineNumber = 0;
        bool firstToken = true;

        for (size_t i = 0; i < line.length(); ++i) {
            char c = line[i];
            
            if (std::isspace(c)) {
                continue;
            }
            
            if (std::isdigit(c) && firstToken) {
                std::string num;
                while (i < line.length() && std::isdigit(line[i])) {
                    num += line[i++];
                }
                i--;
                tokens.push_back({TokenType::NUMBER, num, 0});
                firstToken = false;
            }
            else if (std::isalpha(c)) {
                std::string ident;
                while (i < line.length() && (std::isalnum(line[i]) || line[i] == '$')) {
                    ident += line[i++];
                }
                i--;
                
                if (isKeyword(ident)) {
                    tokens.push_back({TokenType::KEYWORD, ident, 0});
                } else {
                    tokens.push_back({TokenType::IDENTIFIER, ident, 0});
                }
            }
            else if (c == '"') {
                std::string str;
                i++;
                while (i < line.length() && line[i] != '"') {
                    str += line[i++];
                }
                tokens.push_back({TokenType::STRING, str, 0});
            }
            else if (std::isdigit(c) || c == '.' || c == '-') {
                std::string num;
                if (c == '-') {
                    num += c;
                    i++;
                }
                while (i < line.length() && (std::isdigit(line[i]) || line[i] == '.')) {
                    num += line[i++];
                }
                i--;
                tokens.push_back({TokenType::NUMBER, num, 0});
            }
            else {
                tokens.push_back({TokenType::OPERATOR, std::string(1, c), 0});
            }
        }
        
        return tokens;
    }

    bool isKeyword(const std::string& word) {
        static const std::vector<std::string> keywords = {
            "PRINT", "LET", "IF", "THEN", "GOTO", "INPUT", "END", "REM"
        };
        
        std::string upperWord = word;
        std::transform(upperWord.begin(), upperWord.end(), upperWord.begin(), ::toupper);
        
        return std::find(keywords.begin(), keywords.end(), upperWord) != keywords.end();
    }

    void executeLine(const std::string& line) {
        auto tokens = tokenize(line);
        if (tokens.empty()) return;

        size_t tokenIndex = 1;
        if (tokenIndex >= tokens.size()) return;

        std::string keyword = tokens[tokenIndex].value;
        std::transform(keyword.begin(), keyword.end(), keyword.begin(), ::toupper);

        if (keyword == "PRINT") {
            executePrint(tokens, tokenIndex + 1);
        }
        else if (keyword == "LET") {
            executeLet(tokens, tokenIndex + 1);
        }
        else if (keyword == "IF") {
            executeIf(tokens, tokenIndex + 1);
        }
        else if (keyword == "GOTO") {
            executeGoto(tokens, tokenIndex + 1);
        }
        else if (keyword == "INPUT") {
            executeInput(tokens, tokenIndex + 1);
        }
        else if (keyword == "END") {
            running = false;
        }
        else if (keyword == "REM") {
            return;
        }
    }

    void executePrint(const std::vector<Token>& tokens, size_t startIndex) {
        std::string output;
        
        for (size_t i = startIndex; i < tokens.size(); ++i) {
            if (tokens[i].type == TokenType::STRING) {
                output += tokens[i].value;
            }
            else if (tokens[i].type == TokenType::IDENTIFIER) {
                if (variables.find(tokens[i].value) != variables.end()) {
                    output += std::to_string(variables[tokens[i].value]);
                } else {
                    output += "0";
                }
            }
            else if (tokens[i].type == TokenType::NUMBER) {
                output += tokens[i].value;
            }
            else if (tokens[i].value == ";") {
                continue;
            }
        }
        
        std::cout << output << std::endl;
    }

    void executeLet(const std::vector<Token>& tokens, size_t startIndex) {
        if (startIndex + 3 >= tokens.size()) return;
        
        std::string varName = tokens[startIndex].value;
        
        if (tokens[startIndex + 1].value != "=") return;
        
        if (tokens[startIndex + 2].type == TokenType::NUMBER) {
            variables[varName] = std::stoi(tokens[startIndex + 2].value);
        }
        else if (tokens[startIndex + 2].type == TokenType::IDENTIFIER) {
            std::string sourceVar = tokens[startIndex + 2].value;
            if (variables.find(sourceVar) != variables.end()) {
                variables[varName] = variables[sourceVar];
            } else {
                variables[varName] = 0;
            }
        }
    }

    void executeIf(const std::vector<Token>& tokens, size_t startIndex) {
        if (startIndex + 4 >= tokens.size()) return;
        
        int left = getValue(tokens[startIndex]);
        std::string op = tokens[startIndex + 1].value;
        int right = getValue(tokens[startIndex + 2]);
        
        bool condition = false;
        
        if (op == "=") condition = (left == right);
        else if (op == "<") condition = (left < right);
        else if (op == ">") condition = (left > right);
        else if (op == "<=") condition = (left <= right);
        else if (op == ">=") condition = (left >= right);
        else if (op == "<>") condition = (left != right);
        
        if (condition && tokens[startIndex + 3].value == "THEN") {
            if (tokens[startIndex + 4].type == TokenType::NUMBER) {
                int gotoLine = std::stoi(tokens[startIndex + 4].value);
                jumpToLine(gotoLine);
            }
        }
    }

    void executeGoto(const std::vector<Token>& tokens, size_t startIndex) {
        if (startIndex < tokens.size() && tokens[startIndex].type == TokenType::NUMBER) {
            int gotoLine = std::stoi(tokens[startIndex].value);
            jumpToLine(gotoLine);
        }
    }

    void executeInput(const std::vector<Token>& tokens, size_t startIndex) {
        if (startIndex < tokens.size() && tokens[startIndex].type == TokenType::IDENTIFIER) {
            std::string varName = tokens[startIndex].value;
            std::cout << "? ";
            
            std::string input;
            std::getline(std::cin, input);
            
            try {
                variables[varName] = std::stoi(input);
            } catch (...) {
                variables[varName] = 0;
            }
        }
    }

    int getValue(const Token& token) {
        if (token.type == TokenType::NUMBER) {
            return std::stoi(token.value);
        }
        else if (token.type == TokenType::IDENTIFIER) {
            if (variables.find(token.value) != variables.end()) {
                return variables[token.value];
            }
        }
        return 0;
    }

    void jumpToLine(int lineNumber) {
        auto it = lineNumbers.find(lineNumber);
        if (it != lineNumbers.end()) {
            currentLineIndex = it->second;
        }
    }
};

// Example usage with file support
int main() {
    BasicInterpreter interpreter;
    
    // Option 1: Direct file loading
    // interpreter.loadProgramFromFile("program.bas");
    // interpreter.listProgram();
    // interpreter.run();
    
    // Option 2: Interactive mode
    interpreter.runInteractive();
    
    return 0;
}