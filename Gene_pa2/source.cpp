#include <iostream>
#include <fstream>
#include <string>
#include <boost/polygon/polygon.hpp>

using namespace std;
using namespace boost::polygon;
using namespace boost::polygon::operators;

typedef polygon_data<int> Polygon;
typedef polygon_traits<Polygon>::point_type Point;
typedef vector<Polygon> PolygonSet;

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
    int inputNum;
    vector<string> operation;

    while (fin >> input) {
        /* ----- Store Operation Information ----- */
        if (input.compare("OPERATION") == 0) {
            fin >> input;
            for (; input.compare(";") != 0;fin >> input) {                
                operation.push_back(input);
            }
        }
        // else if (input.compare("END") == 0) {
        //     fin >> input;
        //     continue;
        // }
        /* ----- Store Opertion Information ----- */        
        else if (input.compare("DATA") == 0) {
            /* ----- input phrase "Merge" or "Clipper"*/
            fin >> input;
            /* ----- input operation name ----- */
            fin >> input;
            cout << input << endl; 
            // /* ----- Store Merge Polygon ----- */
            // if (input.compare("MERGE")) {
            //     fin >> input;
            //     cout << input << endl; 
                                          
            // } 
            // /* ----- Store Clipper Polygon ----- */
            // else if (input.compare("CLIPPER")) {
            //     fin >> input;
            //     cout << input << endl;
            // }
            /* ----- Read Polygon ----- */
            for (; input.compare("END") != 0;fin >> input) {            
                if (input.compare("POLYGON") == 0) {
                    fin >> input;
                        for (; input.compare(";") != 0;fin >> input) {                
                            cout << input << endl;;
                        }
                    }
            }
            /* ----- End ----- */
            fin >> input;     
        }
    }

    cout << endl;

    for (int i = 0; i < operation.size(); i++) {
        cout << operation[i] << endl;
    }
    
    
    /* ----- Write Output File ----- */

    return 0;
}