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

// #include <ctime>
#include <iostream>
// #include <iterator>
// #include <string>
#include "ConsoleApplication.h"
#include "Exceptions.h"
// #include "OptionParser.h"
// #include "Log.h"
// #include "LogSink.h"
#include <boost/thread.hpp>
#include <boost/date_time.hpp>


// using namespace std;


// void workerFunc()
// {
//     boost::posix_time::seconds workTime(3);
//
//     std::cout << "Worker: running" << std::endl;
//     std::cout << "Thread ID: " << boost::this_thread::get_id() << std::endl;
//
//     // Pretend to do something useful...
//     boost::this_thread::sleep(workTime);
//
//     std::cout << "Worker: finished" << std::endl;
// }



/**
 * @brief Main function to start lionhearth.
 *
 * @param argc   Argument Counter.
 * @param argv[] Argument Values.
 *
 * @return int
 */
int main (int argc, const char * argv[]) {
    // insert code here...
    try {
        int return_code = lion::ConsoleApplication::getInstance()->run(argc, argv);

        // boost::thread workerThread(workerFunc);
        // return_code = lionheart::core::ConsoleApplication::getInstance()->run(argc, argv);
        // workerThread.join();
        return return_code;
    } catch (lionheart::Exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "Exception of unknown type!\n";
        return 255;
    }
    lion::ConsoleApplication::destroy();
    return 0;
}
