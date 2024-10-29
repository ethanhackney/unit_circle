#include <cerrno>
#include <err.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sysexits.h>
#include <unordered_map>
#include <vector>

using std::cout;
using std::ifstream;
using std::pair;
using std::string;
using std::unordered_map;
using std::vector;

int
main(int argc, char **argv)
{
        // coordinates file
        ifstream coordstr {"coord"};
        if (!coordstr.is_open())
                err(EX_SOFTWARE, "could not open coord");

        // angle in radians file
        ifstream radstr {"rad"};
        if (!radstr.is_open())
                err(EX_SOFTWARE, "could not open rad");

        // angle in degrees file
        ifstream degstr {"deg"};
        if (!degstr.is_open())
                err(EX_SOFTWARE, "could not open deg");

        // list of coordinates
        vector<std::pair<string,string>> coords;
        // mapping from angle in radians to coordinates
        unordered_map<string,size_t> radmap;
        // mapping from angle in degrees to coordinates
        unordered_map<string,size_t> degmap;
        for (;;) {
                // read x coordinate
                string x;
                if (!(coordstr >> x))
                        break;
                // read y coordinate
                string y;
                coordstr >> y;
                // add coordinates to list
                coords.push_back({x, y});

                // read angle in radians
                string rad;
                radstr >> rad;
                // set radmap[rad] to index of coordinates
                radmap[rad] = coords.size() - 1;

                // read angle in degrees
                string deg;
                degstr >> deg;
                // set degmap[deg] to index of coordinates
                degmap[deg] = coords.size() - 1;
        }
        // close streams
        coordstr.close();
        radstr.close();
        degstr.close();

        // for each argument
        for (auto p = argv + 1; *p != nullptr; p++) {
                // convert c-style string into std::string
                string arg {*p};
                // coordinates index
                size_t i;
                // if argument has the word 'pi' in it, then use radmap
                if (arg.find("pi") != string::npos) {
                        // lookup angle in radians
                        auto pp = radmap.find(arg);
                        if (pp == radmap.end()) {
                                cout << "invalid argument: " << arg << "\n";
                                continue;
                        }
                        i = pp->second;
                } else {
                        // lookup angle in degrees
                        auto pp = degmap.find(arg);
                        if (pp == degmap.end()) {
                                cout << "invalid argument: " << arg << "\n";
                                continue;
                        }
                        i = pp->second;
                }
                // print coordinates
                cout << "coordinates for " << arg << ": ";
                cout << coords[i].first << ", " << coords[i].second << "\n";
        }
}
