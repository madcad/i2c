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


#include "io/InputThread.h"
#include "core/Application.h"
#include <iostream>

namespace lionheart {
namespace io {
    InputThread::InputThread()
    {
        LOGGER->note() << "Input thread created.";
        LOGGER->flush();
    }

    InputThread::~InputThread()
    {
        LOGGER->note() << "Input thread destroyed.";
        LOGGER->flush();
    }

    void InputThread::run()
    {
        LOGGER->note() << "Input thread started with ID: " << boost::this_thread::get_id();
        LOGGER->flush();

        std::string input;
        // TODO: Solve the while loop and quit the thread corretly, otherwise it leaks memory.
        while(true) {
            std::cin >> input;
            m_commands.runCommand(input);
        }
    }

    core::Command* InputThread::getCommands()
    {
        return &m_commands;
    }
}
}
