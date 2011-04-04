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

#include "LogSink.h"

LogSink::LogSink(const std::string& name) :
    m_Name(name)
{
}

LogSink::~LogSink()
{
}

std::string LogSink::getName() const
{
    return this->m_Name;
}

ConsoleSink::ConsoleSink(const std::string& name) :
    LogSink(name)
{
}

ConsoleSink::~ConsoleSink()
{
}

void ConsoleSink::writeMessage(LogLevel level, const std::string& msg)
{
    static const char* pre[] = { "    NOTE: ",
                           " VERBOSE: ",
                           " WARNING: ",
                           "   ERROR: ",
                           "CRITICAL: " };

    std::cerr << pre[static_cast<int>(level)] << msg << std::endl;
}
