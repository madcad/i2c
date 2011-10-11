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


#ifndef COMMAND_H
#define COMMAND_H

#include <boost/signals2.hpp>
#include <map>
#include <iostream>

namespace lionheart {
namespace core {
    class CommandBase
    {
    public:
        typedef boost::signals2::signal<void(CommandBase *)> CommandSignal;
        virtual void run()=0;
        void fireEvent();
        CommandSignal* getSignal();
    protected:
        CommandSignal m_signal;
    };

    class Command
    {
    public:
        typedef std::map<std::string, CommandBase*> CommandMap;
        typedef std::pair<std::string, CommandBase*> CommandPair;
    private:
        CommandMap m_commands;
    public:
        Command();
        ~Command();
        void addCommand(std::string command, CommandBase *instance);
        CommandBase* getCommand(std::string command);
        void runCommand(std::string command);
    };
}
}

#endif // COMMAND_H
