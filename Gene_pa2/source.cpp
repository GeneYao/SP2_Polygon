#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <boost/polygon/polygon.hpp>

using namespace std;
using namespace boost::polygon;
using namespace boost::polygon::operators;

typedef polygon_data<int> Polygon;
typedef polygon_traits<Polygon>::point_type Point;
typedef vector<Polygon> PolygonSet;

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

    /* ----- Declare Variabes */
    vector<string> operation;
    unordered_map<string, PolygonSet> opMap;
    PolygonSet result;

    /* ----- Read Input File ----- */
    string input;  
    



    while (fin >> input) {
        /* ----- Store Operation Information ----- */
        if (input.compare("OPERATION") == 0) {
            fin >> input;
            for (; input.compare(";") != 0;fin >> input) {                
                operation.push_back(input);
            }
        }
        
        /* ----- Store Opertion Information ----- */        
        else if (input.compare("DATA") == 0) {
            PolygonSet polys;
            string opNames;
            /* ----- input phrase "Merge" or "Clipper"*/
            fin >> input;

            /* ----- input operation name ----- */
            fin >> input;
            opNames = input;
            cout << opNames << endl; 
            
            /* ----- Read Polygon ----- */
            
            for (; input.compare("END") != 0;fin >> input) {
                if (input.compare("POLYGON") == 0) {
                    fin >> input; 
                    int x, y;
                    vector<Point> pts;
                    Polygon poly;                                       
                    for (int i = 0; input.compare(";") != 0; fin >> input, i++) {
                        if (i % 2 == 0) {
                            x = stoi(input);
                        }
                        if (i % 2 == 1) {
                            y = stoi(input);
                            pts.push_back({x, y});
                            cout << x << " " << y << endl;
                        }                          
                    }
                    set_points(poly, pts.begin(), pts.end());
                    polys.push_back(poly);
                }

                //cout << polys.size() << endl;                
            }
            opMap[opNames] = polys;
            /* ----- End ----- */
            fin >> input;     
        }
    }

    cout << endl;

    for (int i = 0; i < operation.size(); i++) {         
        string key = operation[i];
        if (key[0] == 'M') {
            result += opMap[key];
        }  
        else if (key[0] == 'C') {
            result -= opMap[key];
        }    
        cout << operation[i] << endl;
        cout << opMap[operation[i]].size() << endl;
        cout << area(result) << endl;
    }
    
    
    /* ----- Write Output File ----- */

    return 0;
}