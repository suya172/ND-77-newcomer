#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string file_path;
    cin >> file_path;
    ifstream file(file_path);
    if (file.fail()) {
        cout << "File does not exist" << endl;
        exit(EXIT_FAILURE);
    }
    string S;
    string snippet_name;
    cin >> snippet_name;
    string out = "\"" + snippet_name + "\" : { \n \t \"prefix\" : \"" + snippet_name + "\",\n\t\"body\" : [\n";
    while (getline(file, S)) {
        int count = 0;
        bool ok = false;
        string T;
        for (int i = 0; i < S.size(); i++) {
            if (!ok) {
                if (S[i] == ' ') {
                    count++;
                } else {
                    ok = true;
                }
            }
            if (ok) {
                if (S[i] == '\"') {
                    T += "\\\"";
                } else if (S[i] == '\'') {
                    T += "\\\'";
                } else T += S[i];
            }
            if (count == 4) {
                T += "\\t";
                count = 0;
            }
        }
        T = "\t\t\"" + T + "\",\n";
        out += T;
    }
    out += "\t]\n}\n";
    cout << out << endl;
}