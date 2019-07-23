#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <boost/polygon/polygon.hpp>

using namespace std;
using namespace boost::polygon;
using namespace boost::polygon::operators;

typedef polygon_90_data<int> Polygon;
typedef polygon_traits<Polygon>::point_type Point;
typedef polygon_90_set_data<int> PolygonSet;
typedef rectangle_data<int> Rectangle;

int main(int argc, char *argv[])
{
    /* ----- Read Cmd Line ----- */
    ifstream fin(argv[1]);

    if (!fin) {
        cout << "# file reading error" << endl;
		return 0;
    }    

    /* ----- Declare Variabes */
    vector<string> operation;
    unordered_map<string, PolygonSet> opMap;
    PolygonSet result;
    vector <Rectangle> splitResult;

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
        
        /* ----- Store Polygon Information ----- */        
        else if (input.compare("DATA") == 0) {
            PolygonSet polys;
            string opNames;
            /* ----- input phrase "Merge" or "Clipper"*/
            fin >> input;

            /* ----- input operation name ----- */
            fin >> input;
            opNames = input;            
            
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
                        }                          
                    }
                    set_points(poly, pts.begin(), pts.end());
                    polys.insert(poly);
                }                              
            }
            opMap[opNames] = polys;

            /* ----- Read End ----- */
            fin >> input;     
        }
    }
    

    for (int i = 0; i < operation.size(); i++) {         
        string key = operation[i];
        if (key[0] == 'M') {
            result += opMap[key];
        }  
        else if (key[0] == 'C') {
            result -= opMap[key];
        } 
        else if (key[1] == 'H') {
            result.get_rectangles(splitResult, HORIZONTAL);            
        } 
        else if (key[1] == 'V') {
            result.get_rectangles(splitResult, VERTICAL);            
        }         
    }

    /* ----- Write Output File ----- */
    ofstream fout(argv[2]);
    for (int i = 0; i < splitResult.size(); i++) {
        fout << "RECT " << xl(splitResult[i]) << " " << yl(splitResult[i])
        << " " << xh(splitResult[i]) << " " << yh(splitResult[i]) << " ;" << endl;
    }

    return 0;
}