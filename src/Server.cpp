#include <iostream>
#include <string>

bool match_pattern(const std::string& input_line, const std::string& pattern) {
    if (pattern.length() == 1) {
        return input_line.find(pattern) != std::string::npos;
    }
    else {
        throw std::runtime_error("Unhandled pattern " + pattern);
    }
}

bool find_digit(const std::string& input_line) {
    for (char c : input_line) {
        if (std::isdigit(c)) {
            return true;
        }
    }
    return false;
}

bool find_alpha(const std::string& input_line) {
    for (char c : input_line) {
        if (std::isalpha(c)) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    std::cout << "Logs from your program will appear here" << std::endl;

    if (argc != 3) {
        std::cerr << "Expected two arguments" << std::endl;
        return 1;
    }

    std::string flag = argv[1];
    std::string pattern = argv[2];

    if (flag != "-E") {
        std::cerr << "Expected first argument to be '-E'" << std::endl;
        return 1;
    }

    // Uncomment this block to pass the first stage
    //
    std::string input_line;
    std::getline(std::cin, input_line);
    
    try {
        if (pattern == "\\w" && (find_alpha(input_line) || find_digit(input_line))) {
            return 0;
        } else
        if (pattern == "\\d" && find_digit(input_line)) {
            return 0;
        } else if(pattern[0] == '['){
            int flag = 1;

            if (pattern[1] == '^'){
                for (int i = 2; i < pattern.length() - 1; i++) {
                    if(match_pattern(input_line, std::string(1, pattern[i]))){
                        return flag;
                    }
                }
            }
            
            for (int i = 1; i < pattern.length() - 1; i++) {
                if(match_pattern(input_line, std::string(1, pattern[i]))){
                    flag = 0;
                    break;
                }
            }
            return flag;
        } else if (match_pattern(input_line, pattern)) {
            return 0;
        } else {
            return 1;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
