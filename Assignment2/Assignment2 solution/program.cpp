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

int main() {
    cout << "First sample data: 11100011" << endl;
    cout << "First sample CRC pattern: 110011" <<endl;
    string sample1 = encodeData("11100011","110011");
    cout << "Remainder 5" << " bit code: " << sample1.substr(8)<<endl;
    cout <<"13 bit Frame with CRC: " << sample1 << endl;

    cout << "Second sample data: 10010011011" << endl;
    cout << "Seccond sample CRC pattern: 10011" <<endl;
    string sample2 = encodeData("10010011011","10011");
    cout << "Remainder 4" << " bit code: " << sample2.substr(11)<<endl;
    cout <<"15 bit Frame with CRC: " << sample2 << endl;
    while(1){
        cout << "Want to provide more input? : Y or N only"<<endl;
        string allowed;
        cin>> allowed;
        if(allowed == "N"){
            cout<< "Turning off the program" <<endl;
            return 0;
        }
        else if(allowed != "Y"){
            cout << "Wrong input! Turning off the program" <<endl; 
            return 0;
        }
        string data;
        int k,p,n;
        cout<< "Enter Data: "<<endl;
        cin>>data;
        k = data.length();
        string pattern;
        cout << "Enter Pattern P: " << endl;
        cin>>pattern;
        p = pattern.length();
        n = k + p;
        string frame = encodeData(data, pattern);
        cout << "Remainder " << p-1 << " bit code: " << frame.substr(k)<<endl;
        cout << k+p-1 <<" bit Frame with CRC: " << frame << endl;
    }
    return 0;
}

