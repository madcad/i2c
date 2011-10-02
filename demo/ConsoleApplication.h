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

#ifndef _CONSOLEAPPLICATION_H_
#define _CONSOLEAPPLICATION_H_

#include "core/Application.h"
#include "core/Singleton.h"
#include "OptionParser.h"
#include "io/InputThread.h"
#include <string>

namespace lion {
    class InputThread;

    class ConsoleApplication: public lionheart::core::Application,
    public lionheart::core::Singleton<ConsoleApplication>
    {
        friend class lionheart::core::Singleton<ConsoleApplication>;
        friend class InputThread;
    protected:
        bool running;
        std::string m_szUsage;
        std::string m_szVersion;
        optparse::OptionParser m_OptionParser;
        void _run();
    public:
        ConsoleApplication();
        ~ConsoleApplication();
        void onCommandExit(lionheart::io::InputThread * InputInstance);
        int run(int argc,const char * argv[]);
    };
}

#endif /* CONSOLEAPPLICATION_H_ */

