//
//  Log.h
//  lionheart
//
//  Created by Torsten Walluhn on 07.04.11.
//  Copyright 2011 mad-cad.net. All rights reserved.
//

#include <string>
#include <list>
#include <sstream>

#include "LogSink.h"
namespace lionheart {
    class Log {
    public:
        Log();
        ~Log();
        void addSink(LogSinkPtr sink);
        void removeSink(const std::string& sinkName);
        void removeSink(LogSinkPtr sink);
        void removeSinks();
    public:
        std::ostream& note();
        std::ostream& verbose();
        std::ostream& warning();
        std::ostream& error();
        std::ostream& critical();
        void flush();
    private:
        std::stringstream m_buffer;
        LogLevel m_lastLevel;
        std::list<LogSinkPtr> m_sinks;
    };
}
