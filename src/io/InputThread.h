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

#ifndef _INPUTTHREAD_H_
#define _INPUTTHREAD_H_

#include <boost/thread.hpp>
#include <boost/signals2.hpp>
#include "core/Command.h"

namespace lionheart {
namespace io {
    class InputThread
    {
    protected:
    public:
        InputThread();
        ~InputThread();
        void run();
        lionheart::core::Command* getCommands();
    private:
        lionheart::core::Command m_commands;
    };
}
}

#endif /* CONSOLEAPPLICATION_H_ */
