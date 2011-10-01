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
#include <list>
#include <sstream>

#ifndef LOG_H_
#define LOG_H_

#include "core/LogSink.h"
#include "core/Singleton.h"
#include "Exceptions.h"

namespace lionheart {
    namespace core {
        class Log : public lionheart::core::Singleton<Log> {
            friend class lionheart::core::Singleton<Log>;
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
}
#endif
