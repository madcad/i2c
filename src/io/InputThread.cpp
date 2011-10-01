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


#include "InputThread.h"
#include "core/Application.h"
#include <iostream>

namespace lion {
    InputThread::InputThread()
    {
        LOGGER->note() <<
            "Input thread started with ID: "
            << boost::this_thread::get_id();
        LOGGER->flush();
    }

    InputThread::~InputThread()
    {
        LOGGER->note() <<
            "Input thread destroyed.";
    }

    void InputThread::run()
    {
        std::string input;
        while(true) {
            std::cin >> input;
            if (input == "exit")
                break;
        }
    }
}
