//
//  Log.cpp
//  lionheart
//
//  Created by Torsten Walluhn on 07.04.11.
//  Copyright 2011 mad-cad.net. All rights reserved.
//

#include "Log.h"

lionheart::Log::Log()
{}

lionheart::Log::~Log()
{
    this->removeSinks();
}

void lionheart::Log::addSink(LogSinkPtr sink)
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

void lionheart::Log::removeSink(const std::string& sinkName)
{
    flush();

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

void lionheart::Log::removeSink(LogSinkPtr sink)
{
    flush();

    // search for sink
    std::list<LogSinkPtr>::iterator it =
    std::find(this->m_sinks.begin(),this->m_sinks.end(),sink);

    // remove sink if it exists
    if(it != this->m_sinks.end())
    {
        this->m_sinks.erase(it);
    }
}

void lionheart::Log::removeSinks()
{
    flush();    // make sure last message gets flushed to sinks

    this->m_sinks.clear();     // empty entire sink list
}

void lionheart::Log::flush()
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
std::ostream& lionheart::Log::note()
{
    this->flush();
    this->m_lastLevel = LOG_NOTE;
    return this->m_buffer;
}

std::ostream& lionheart::Log::verbose()
{
    this->flush();
    this->m_lastLevel = LOG_VERBOSE;
    return this->m_buffer;
}

std::ostream& lionheart::Log::warning()
{
    this->flush();
    this->m_lastLevel = LOG_WARNING;
    return this->m_buffer;
}

std::ostream& lionheart::Log::error()
{
    this->flush();
    this->m_lastLevel = LOG_ERROR;
    return this->m_buffer;
}

std::ostream& lionheart::Log::critical()
{
    this->flush();
    this->m_lastLevel = LOG_CRITICAL;
    return this->m_buffer;
}

