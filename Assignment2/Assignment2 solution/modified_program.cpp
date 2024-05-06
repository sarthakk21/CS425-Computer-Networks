#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

string xor_function(string a, string b) {
    string result = "";
    int n = b.length();
    for(int i = 1; i < n; i++) {
        if (a[i] == b[i])
            result += "0";
        else
            result += "1";
    }
    return result;
}

string mod2longdiv(string dividend, string divisor) {
    int idx = divisor.length();
    string tmp = dividend.substr(0, idx);
    int n = dividend.length();
    
    while (idx < n) {
        if (tmp[0] == '1')
            tmp = xor_function(divisor, tmp) + dividend[idx];
        else
            tmp = xor_function(string(idx, '0'), tmp) + dividend[idx];
        idx += 1;
    }
    
    if (tmp[0] == '1')
        tmp = xor_function(divisor, tmp);
    else
        tmp = xor_function(string(idx, '0'), tmp);
    
    return tmp;
}

string encodeData(string data, string pattern) {
    string appended_data = data + string(pattern.length() - 1, '0');
    string remainder = mod2longdiv(appended_data, pattern);
    return data + remainder;
}

string Error_function(string data, int errorCount = 1) {
    srand(time(0));
    for (int i = 0; i < errorCount; i++) {
        int pos = rand() % data.length();
        data[pos] = data[pos] == '0' ? '1' : '0';
    }
    return data;
}

int main() {

    // Generate a message of k=10 bits
    string data = "";
    srand(time(0));
    for(int i = 0; i < 10; i++) {
        data += rand() % 2 == 0 ? '0' : '1';
    }
    cout << endl << "Generated Data (10 bits): " << data << endl;
    
    // Use CRC pattern P=110101 to generate a 15-bit frame
    string P = "110101";
    cout << "Pattern (6 bits): " << P << endl;

    string T = encodeData(data, P);
    cout << "15-bit Frame T for Transmission:  " << T << endl;
    
    // Introduce errors
    string error_string = Error_function(T, 3); // Introduce 3 errors for demonstration
    cout << "Frame T after Introducing Errors: " << error_string << endl;
    
    // Check frame with CRC
    string check = mod2longdiv(error_string, P);
    if (check.find('1'))
        cout << "Error detected in the frame -> Discarded" << endl; // Print error message
    else
        cout << "No error detected in the frame -> Accepted" << endl; // Print no error message
    return 0;
}

