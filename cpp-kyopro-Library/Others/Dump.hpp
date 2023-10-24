#include <iostream>
#include <string>
#include <source_location>

using namespace std;

namespace debug {
    void dump_init(const source_location location = std::source_location::current()) {
        cout << "\033[32m[dump] \033[m\033[36m" << location.file_name() << ":" << location.line() << ":" << location.function_name() << "\033[m ";
    }
    template <typename T>
    void dump(const T a, const string label = "", const source_location location = source_location::current()) {
        dump_init(location);
        if (label == "") {
            cout << a << endl;
            return;
        }
        cout << label << " : " << a << endl;
    }
};

using namespace debug;