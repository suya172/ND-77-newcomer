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
        S = "\t\t\"" + S + "\",\n";
        out += S;
    }
    out += "\t]\n}\n";
    cout << out << endl;
}