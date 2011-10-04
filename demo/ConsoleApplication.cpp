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


#include "ConsoleApplication.h"
#include "io/InputThread.h"
#include "Commands.h"
#include <iostream>


namespace lion {

    ConsoleApplication::ConsoleApplication()
    {
        m_szUsage = "usage: %prog [OPTION]... DIR [FILE]...";
        m_szVersion = "%prog 0.0.1\nCopyright (C) 2011 mad-cad.net\n"
            " ___ ____   ____\n"
            "|_ _|___ \\ / ___|\n"
            "| |  __) | |    \n"
            "| | / __/| |___ \n"
            "|___|_____|\\____|\n";
        m_OptionParser = optparse::OptionParser()
        .usage(m_szUsage)
        .version(m_szVersion);

        m_OptionParser.add_option("-h").action("help").help("alternative help");
        m_OptionParser.add_option("-v").action("version").help("alternative version");
        LOGGER->addSink(lionheart::core::LogSinkPtr(new lionheart::core::ConsoleSink("out")));

        running = true;

    }

    ConsoleApplication::~ConsoleApplication() {
        // TODO Auto-generated destructor stub
        LOGGER->flush();
    }

    void ConsoleApplication::onQuitCommand(lionheart::core::CommandBase* BaseCommand)
    {
        LOGGER->note() << "onQuitCommand triggered";
        LOGGER->flush();
        running = false;
    }

    int ConsoleApplication::run(int argc, const char** argv) {
        m_OptionParser.parse_args(argc, argv);
        if (argc == 0) {
            m_OptionParser.print_help();
            return 1;
        }
        this->_run();
        return 0;
    }

    void ConsoleApplication::_run() {
        LOGGER->warning() << "test";
        LOGGER->flush();

        lion::QuitCommand *cmd = new lion::QuitCommand();
        cmd->getSignal()->connect(boost::bind(&ConsoleApplication::onQuitCommand, this, _1));

        lionheart::io::InputThread tc;
        tc.getCommands()->addCommand("quit", cmd);

        boost::thread *thread = new boost::thread(&lionheart::io::InputThread::run, &tc);

        while (running) {
        }
        delete thread;
    }
}
