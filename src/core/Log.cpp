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


#include "core/Log.h"

lionheart::core::Log::Log()
{}

lionheart::core::Log::~Log()
{
    this->removeSinks();
}

/**
 * Add a log Sink to the logger.
 */
void lionheart::core::Log::addSink(LogSinkPtr sink)
{
    this->flush();

    for (std::list<LogSinkPtr>::iterator it = this->m_sinks.begin();
         it != this->m_sinks.end();
         ++it)
    {
        if(sink == *it || sink->getName() == (*it)->getName())
        {
            throw Exception(std::string("Sink '" + sink->getName() + " already exists"), __FILE__, __LINE__);
        }
    }

    this->m_sinks.push_back(sink);
}

/**
 * Remove a log Sink to the logger by it's name.
 */
void lionheart::core::Log::removeSink(const std::string& sinkName)
{
    this->flush();

    // find sink and erase it
    for (std::list<LogSinkPtr>::iterator it = this->m_sinks.begin();
         it != this->m_sinks.end();
         ++it)
    {
        if((*it)->getName() == sinkName)
        {
            this->m_sinks.erase(it);
        }
    }
}

/**
 * Remove a log Sink to the logger by it's instance.
 */
void lionheart::core::Log::removeSink(LogSinkPtr sink)
{
    this->flush();

    // search for sink
    std::list<LogSinkPtr>::iterator it =
    std::find(this->m_sinks.begin(),this->m_sinks.end(),sink);

    // remove sink if it exists
    if(it != this->m_sinks.end())
    {
        this->m_sinks.erase(it);
    }
}

/**
 * Remove all sinks.
 */
void lionheart::core::Log::removeSinks()
{
    this->flush();    // make sure last message gets flushed to sinks

    this->m_sinks.clear();     // empty entire sink list
}

/**
 * Flaush all log sinks.
 */
void lionheart::core::Log::flush()
{
    std::string str = this->m_buffer.str();    // get string from buffer
    if(str.length())    // if a message exists, write it to all sinks
    {
        for(std::list<LogSinkPtr>::iterator it = this->m_sinks.begin();
            it != this->m_sinks.end();
            ++it)
        {
            (*it)->writeMessage(this->m_lastLevel, str);
        }
        this->m_buffer.str("");    // clear message
    }
}

// note, verbose, warning, error, critical all flush the existing buffer
// set the level and return the stringstream for writing
std::ostream& lionheart::core::Log::note()
{
    this->flush();
    this->m_lastLevel = LOG_NOTE;
    return this->m_buffer;
}

std::ostream& lionheart::core::Log::verbose()
{
    this->flush();
    this->m_lastLevel = LOG_VERBOSE;
    return this->m_buffer;
}

std::ostream& lionheart::core::Log::warning()
{
    this->flush();
    this->m_lastLevel = LOG_WARNING;
    return this->m_buffer;
}

std::ostream& lionheart::core::Log::error()
{
    this->flush();
    this->m_lastLevel = LOG_ERROR;
    return this->m_buffer;
}

std::ostream& lionheart::core::Log::critical()
{
    this->flush();
    this->m_lastLevel = LOG_CRITICAL;
    return this->m_buffer;
}

