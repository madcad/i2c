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

#include "Exceptions.h"
#include <sstream>

lionheart::Exception::Exception(const std::string& message,
    const std::string& file,
    unsigned int line) throw():
    m_szMessage(message), m_szFile(file), m_iLine(line)
{

}

lionheart::Exception::~Exception() throw()
{
}

const char * lionheart::Exception::what() const throw()
{
    std::ostringstream ss;

    ss << m_szMessage;
    if(!m_szFile.empty())
    {
        ss << " (" << m_szFile << ":" << m_iLine << ")";
    }
    return ss.str().c_str();
}

std::string lionheart::Exception::getMessage() const throw()
{
    return this->m_szMessage;
}
