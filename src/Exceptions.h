/*
 * exceptions.h
 *
 *  Created on: 24.04.2011
 *      Author: walluhn
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
}

#endif /* EXCEPTIONS_H_ */
