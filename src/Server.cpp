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

int grep(string pattern, string input_line){
    
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
        
        if(pattern[pattern_idx] == '('){
            cout<<"Search Alternation"<<endl;
            int end = int(pattern.find(')', pattern_idx));
            string p = "";
            int result = 0;
            while(pattern_idx <= end){
                p += pattern[++pattern_idx];
                cout<<"test"<<endl;
                if(pattern[pattern_idx] == '|'){
                    p = '^' + p + '$';
                    cout<<"Checking Pattern: "<<p<<endl;
                    result = result || grep(p, input_line.substr(i, p.length() - 2));
                    if (result){
                        cout<<"Success Pattern"<<endl;
                        break;
                    }
                    p = "";
                }
                if(result)
                    break;
                else
                    return 0;
            }   
        }
        else if(pattern[pattern_idx] == '.'){ // Any character
            pattern_idx++;
        }
        else if (pattern[pattern_idx] == '?'){
            pattern_idx++;
            i--;
        }
        else if (pattern[pattern_idx] == '+'){ // One or more
            char prev = pattern[pattern_idx - 1];
            while(prev == input_line[i]){
                i++;
            }
            i--;
            pattern_idx++;
        }
        else if (pattern[pattern_idx] == '\\'){ // Check for digit and alphanumerics
            pattern_idx++;
            if(pattern[pattern_idx] == 'd'){
                cout<<"Search Digit"<<endl;
                if (!isdigit(input_line[i])){
                    if(pattern_idx < pattern.length() - 1 && pattern[pattern_idx + 1] == '?'){
                        pattern_idx += 2;
                        cout<<"Chance"<<endl;
                        continue;
                    }
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
                    if(pattern_idx < pattern.length() - 1 && pattern[pattern_idx + 1] == '?'){
                        pattern_idx += 2;
                        cout<<"Chance"<<endl;
                        continue;
                    }
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
        else if (pattern[pattern_idx] == '['){ //check for regex
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
                    if(pattern_idx < pattern.length() - 1 && pattern[pattern_idx + 1] == '?'){
                        pattern_idx += 2;
                        cout<<"Chance"<<endl;
                        continue;
                    }
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
                    if(pattern_idx < pattern.length() - 1 && pattern[pattern_idx + 1] == '?'){
                        pattern_idx += 2;
                        cout<<"Chance"<<endl;
                        continue;
                    }
                    cout<<"Fail"<<endl;
                    if(strict_start){
                        cout<<"Strict Start Fail"<<endl;
                        break;
                    }
                    pattern_idx = 0;
                }
            } 
        }
        else if (input_line[i] == pattern[pattern_idx]){ // Check for exact match
            cout<<"Match "<<pattern[pattern_idx]<<endl;
            pattern_idx++;
        } 
        else{ //Chance logic or else fail
            if(pattern_idx < pattern.length() - 1 && pattern[pattern_idx + 1] == '?'){
                pattern_idx++;
                i--;
                cout<<"Chance"<<endl;
                continue;
            }
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
    
    return grep(pattern, input_line);
}
