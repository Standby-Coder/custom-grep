#include <iostream>
#include <string>
#include <unordered_map>
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
    int strict_start = pattern[pattern_idx] == '^' ? 1 : 0;
    if (strict_start){
        pattern_idx++;
    }

    int strict_end = pattern[pattern.length() - 1] == '$' ? 1 : 0;
    if (strict_end){
        pattern = pattern.substr(0, pattern.length() - 1);
    }

    for(int i = 0; i < input_line.length(); i++){
        if (pattern_idx == pattern.length()){
            if(strict_end && i != input_line.length()){
                cout<<"Strict End Fail"<<endl;
                return 1;
            }
            break;
        }

        cout<<"Input line char: "<<input_line[i]<<endl;
        cout<<"Pattern char: "<<pattern[pattern_idx]<<endl;

        if (pattern[pattern_idx] == '+'){
            char prev = pattern[pattern_idx - 1];
            while(prev == input_line[i]){
                i++;
            }
            pattern_idx++;
        }
        else if (pattern[pattern_idx] == '\\'){
            pattern_idx++;
            if(pattern[pattern_idx] == 'd'){
                cout<<"Search Digit"<<endl;
                if (!isdigit(input_line[i])){
                    pattern_idx = 0;
                    if(strict_start){
                        cout<<"Strict Start Fail"<<endl;
                        break;
                    }
                    cout<<"Fail"<<endl;
                }
                else {
                    pattern_idx++;
                    cout<<"Success"<<endl;
                }
            } else if(pattern[pattern_idx] == 'w'){
                cout<<"Search AlphaNum"<<endl;
                if (!isalnum(input_line[i])){
                    pattern_idx = 0;
                    if(strict_start){
                        cout<<"Strict Start Fail"<<endl;
                        break;
                    }
                    cout<<"Fail"<<endl;
                }
                else {
                    cout<<"Success"<<endl;
                    pattern_idx++;
                }
            }
        } 
        else if (pattern[pattern_idx] == '['){
            cout<<"Search Bracket"<<endl;
            unordered_map<char, int> m;
            
            int sign = pattern[++pattern_idx] == '^' ? 1 : 0;
            int end = int(pattern.find(']', pattern_idx));
            
            for(int j = pattern_idx + sign; j < end; j++){
                m[pattern[j]] = 1;
            }
            
            if(sign){
                if(m.find(input_line[i]) == m.end()){
                    cout<<"Success"<<endl;
                    pattern_idx = end + 1;
                } else{
                    cout<<"Fail"<<endl;
                    if(strict_start){
                        cout<<"Strict Start Fail"<<endl;
                        break;
                    }
                    pattern_idx = 0;
                }
            } else{
                if(m.find(input_line[i]) != m.end()){
                    cout<<"Success"<<endl;
                    pattern_idx = end + 1;
                } else{
                    cout<<"Fail"<<endl;
                    if(strict_start){
                        cout<<"Strict Start Fail"<<endl;
                        break;
                    }
                    pattern_idx = 0;
                }
            } 
        }
        else if (input_line[i] == pattern[pattern_idx]){
            cout<<"Match "<<pattern[pattern_idx]<<endl;
            pattern_idx++;
        } else{
            cout<<"Failure"<<endl;
            pattern_idx = 0;
            if(strict_start){
                cout<<"Strict Start Fail"<<endl;
                break;
            }
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
