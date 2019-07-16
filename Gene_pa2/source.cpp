#include <iostream>
#include <fstream>
#include <string>
#include <boost/polygon/polygon.hpp>

using namespace std;
namespace gtl = boost::polygon;
using namespace boost::polygon::operators;

class Merge
{

};

class Clipper
{

};

int main(int argc, char *argv[])
{
    /* ----- Read Cmd Line ----- */
    ifstream fin(argv[1]);

    if (!fin) {
        cout << "# file reading error" << endl;
		return 0;
    }
    // if (argc < 2) {
    //     cout << "Please input : .//myPolygon [input_file*.txt] [output_file*.txt]" << endl;
    // }

    /* ----- Read Input File ----- */
    string input;    
    vector<string> operation;

    while (fin >> input) {
        /* ----- Store Operation Information ----- */
        if (input.compare("OPERATION") == 0) {
            fin >> input;
            for (; input.compare(";") != 0;fin >> input) {                
                operation.push_back(input);
            }
        }
        else if (input.compare("END") == 0) {
            fin >> input;
            continue;
        }
        /* ----- Store Opertion Information ----- */        
        else if (input.compare("DATA") == 0) {
            fin >> input; 
            /* ----- Store Merge Polygon ----- */
            if (input.compare("MERGE")) {
                fin >> input;
                cout << input << endl;
            } 
            /* ----- Store Clipper Polygon ----- */
            else if (input.compare("CLIPPER")) {
                fin >> input;
                cout << input << endl;
            }    
        }
    }

    cout << endl;

    for (int i = 0; i < operation.size(); i++) {
        cout << operation[i] << endl;
    }
    
    
    /* ----- Write Output File ----- */

    return 0;
}