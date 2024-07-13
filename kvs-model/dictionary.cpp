// C++ Program to Create a Dictionary  using Unordered Map
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main()
{
    // // Create an empty dictionary using ordered map
    unordered_map<string, string> dictionary;

    // Insert key-value pairs using subscript operator
    dictionary["one"] = "C++";
    dictionary["two"] = "Java";

    // Insert key-value pairs using insert method
    dictionary.insert(make_pair("three", "Python"));
    dictionary.insert(make_pair("four", "JavaScript"));

    // Check if a key exists using count method
    if (dictionary.count("two") > 0) {
        cout << "Value for Key - 2: " << dictionary["two"]
             << endl;
    }
    else {
        cout << " 2 is not present in the dictionary"
             << endl;
    }

    // Check if a key exists using find method
    if (dictionary.find("three") != dictionary.end()) {
        cout << "Value for key - 3: " << dictionary["three"]
             << endl;
    }
    else {
        cout << "3 is not present  in the dictionary"
             << endl;
    }

    // Iterate over the dictionary using range-based for
    // loop
    cout << "Elements of Dictionary:" << endl;
    for (const auto& pair : dictionary) {
        cout << pair.first << ": " << pair.second << endl;
    }
    return 0;
}
