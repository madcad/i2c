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

#include "core/Command.h"

namespace lionheart {
namespace core {

    Command::Command()
    { }

    Command::~Command()
    {
        while(m_commands.begin() != m_commands.end())
        {
            delete m_commands.begin()->second;
            m_commands.erase(m_commands.begin());
        }
    }

    void Command::addCommand(std::string command, CommandBase* instance)
    {
        m_commands.insert(CommandPair(command, instance));
    }

    CommandBase* Command::getCommand(std::string command)
    {
        // TODO: Add tokenzier to support arguments.
        CommandMap::iterator it = m_commands.find(command);
        if (it != m_commands.end() )
        {
            return (*it).second;
        }
        return NULL;
    }

    void Command::runCommand(std::string command)
    {
        CommandBase* cmd = getCommand(command);
        if (cmd)
        {
            cmd->run();
            cmd->fireEvent();
        }
    }

    void CommandBase::fireEvent()
    {
        m_signal(this);
    }

    CommandBase::CommandSignal* CommandBase::getSignal()
    {
        return &m_signal;
    }
}
}