/*
 * Exceptions.cpp
 *
 *  Created on: 24.04.2011
 *      Author: walluhn
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
