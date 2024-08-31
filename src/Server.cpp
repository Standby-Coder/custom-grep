#include <iostream>
#include <string>
using namespace std;

bool match_pattern(const string& input_line, const string& pattern) {
    if (pattern.length() == 1) {
        return input_line.find(pattern) != string::npos;
    }
    else {
        throw runtime_error("Unhandled pattern " + pattern);
    }
}

bool find_digit(const string& input_line) {
    for (char c : input_line) {
        if (isdigit(c)) {
            return true;
        }
    }
    return false;
}

bool find_alpha(const string& input_line) {
    for (char c : input_line) {
        if (isalpha(c)) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    // Flush after every cout / cerr
    cout << unitbuf;
    cerr << unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    cout << "Logs from your program will appear here" << endl;

    if (argc != 3) {
        cerr << "Expected two arguments" << endl;
        return 1;
    }

    string flag = argv[1];
    string pattern = argv[2];

    if (flag != "-E") {
        cerr << "Expected first argument to be '-E'" << endl;
        return 1;
    }

    // Uncomment this block to pass the first stage
    //
    string input_line;
    getline(cin, input_line);

    int pattern_idx = 0;

    for(int i = 0; i < input_line.length(); i++){
        cout<<"Input line char: "<<input_line[i]<<endl;
        cout<<"Pattern char: "<<pattern[pattern_idx]<<endl;
        if (pattern[pattern_idx] == '\\'){
            pattern_idx++;
            if(pattern[pattern_idx] == 'd'){
                cout<<"Search Digit"<<endl;
                if (!isdigit(input_line[i])){
                    pattern_idx = 0;
                }
                else {
                    pattern_idx++;
                }
            } else if(pattern[pattern_idx] == 'w'){
                cout<<"Search AlphaNum"<<endl;
                if (!isalnum(input_line[i])){
                    pattern_idx = 0;
                }
                else {
                    pattern_idx++;
                }
            }
        } 
        else if (pattern[pattern_idx] == '['){
            cout<<"Search Bracket"<<endl;
            int flag = 1;
            if (pattern[pattern_idx + 1] == '^'){
                cout<<"Search Not"<<endl;
                int x = 0;
                for (int j = pattern_idx + 2; j < pattern.length() - 1; j++){
                    if (input_line[i] == pattern[j]){
                        x = 1;
                        break;
                    }
                }
                flag = x;
            } else{
                cout<<"Search Normal"<<endl;
                for (int j = pattern_idx + 1; j < pattern.length() - 1; j++){
                    if (input_line[i] == pattern[j]){
                        flag = 0;
                        break;
                    }
                }
            }
            if (flag){
                pattern_idx = 0;
            } else{
                pattern_idx++;
            }
        }
        if (input_line[i] == pattern[pattern_idx]){
            cout<<"Matched"<<endl;
            pattern_idx++;
        } else{
            pattern_idx = 0;
        }
    }

    if (pattern_idx == pattern.length()){
        return 0;
    } else{
        return 1;
    }
    
    // try {
    //     if (pattern == "\\w" && (find_alpha(input_line) || find_digit(input_line))) {
    //         return 0;
    //     } else
    //     if (pattern == "\\d" && find_digit(input_line)) {
    //         return 0;
    //     } else if(pattern[0] == '['){
    //         int flag = 1;

    //         if (pattern[1] == '^'){
    //             cout<<1<<endl;
    //             int x = 0;
    //             for (int i = 2; i < pattern.length() - 1; i++) {
    //                 if(match_pattern(input_line, string(1, pattern[i]))){
    //                     x = 1;
    //                     break;
    //                 }
    //             }
    //             flag = x;
    //         } else{
    //             for (int i = 1; i < pattern.length() - 1; i++) {
    //                 if(match_pattern(input_line, string(1, pattern[i]))){
    //                     flag = 0;
    //                     break;
    //                 }
    //             }
    //         }
    //         return flag;
    //     } else if (match_pattern(input_line, pattern)) {
    //         return 0;
    //     } else {
    //         return 1;
    //     }
    // } catch (const runtime_error& e) {
    //     cerr << e.what() << endl;
    //     return 1;
    // }
}
