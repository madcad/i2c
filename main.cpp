/* Copyright (C) 2011 Torsten Walluhn <mail@mad-cad.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <ctime>
#include <iostream>
#include <iterator>
#include <string>
#include "OptionParser.h"


using namespace std;

/**
* @brief Main function to start lionhearth.
*
* @param argc   Argument Counter.
* @param argv[] Argument Values.
*
* @return int
*/
int main (int argc, char * const argv[]) {
    // insert code here...
    const string usage = "usage: %prog [OPTION]... DIR [FILE]...";
    const string version = "%prog 0.0.1\nCopyright (C) 2011 mad-cad.net\n"
    "License GPLv3+: GNU GPL version 3 or later "
    "<http://gnu.org/licenses/gpl.html>.\n"
    "This is free software: you are free to change and redistribute it.\n"
    "There is NO WARRANTY, to the extent permitted by law.";
    const string desc = "Missing description.";
    try {
        optparse::OptionParser parser = optparse::OptionParser()
        .usage(usage)
        .version(version)
        .description(desc);

        parser.add_option("-h").action("help").help("alternative help");
        parser.add_option("-v").action("version").help("alternative version");

        optparse::Values& options = parser.parse_args(argc, argv);
        vector<string> args = parser.args();

        if (argc == 0) {
            parser.print_help();
            return 1;
        }

    } catch (exception& e) {
        cerr << "error: " << e.what() << "\n";
        return 1;
    } catch (...) {
        cerr << "Exception of unknown type!\n";
        return 255;
    }
    return 0;
}
