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

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>
#include <string>
namespace lionheart {
    class Exception : public std::exception
    {
    public:
        Exception(const std::string& message = std::string(),
            const std::string& file = std::string(),
            unsigned int line=0) throw();
        virtual ~Exception() throw();
        virtual const char* what() const throw();
        std::string virtual getMessage() const throw();

    private:
        std::string m_szMessage;
        std::string m_szFile;
        unsigned int m_iLine;
    };
    class PreconditionException : public Exception {};
}

#endif /* EXCEPTIONS_H_ */
