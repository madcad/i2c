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

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <memory>
#include <fstream>

using boost::shared_ptr;

#ifndef LOG_SINK_H_
#define LOG_SINK_H_
namespace lionheart {
    enum LogLevel {
        LOG_NOTE, LOG_VERBOSE, LOG_WARNING, LOG_ERROR, LOG_CRITICAL
    };

    class LogSink {

    public:
        LogSink(const std::string& name);

        virtual ~LogSink();
        virtual void writeMessage(LogLevel level, const std::string& msg)=0;
        std::string getName() const;

    private:
        std::string m_Name;
        LogSink(const LogSink&);
        LogSink& operator=(const LogSink&);
    };

    // Type: LogSinkPtr
    //  Pointer to a log sink, used since LogSink is abstract and will always
    //  be accessed via a pointer.
    typedef shared_ptr<LogSink> LogSinkPtr;

    class ConsoleSink: public LogSink {
    public:
        ConsoleSink(const std::string& name);
        virtual ~ConsoleSink();

        virtual void writeMessage(LogLevel level, const std::string& msg);
    };

    class FileSink: public LogSink {
    public:
        FileSink(const std::string& name);
        ~FileSink();

        virtual void writeMessage(LogLevel level, const std::string& msg);
    private:
        std::ofstream m_OutStream;
    };
}
#endif

