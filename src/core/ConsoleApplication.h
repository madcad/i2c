/*
 * ConsoleApplication.h
 *
 *  Created on: 18.06.2011
 *      Author: walluhn
 */

#ifndef CONSOLEAPPLICATION_H_
#define CONSOLEAPPLICATION_H_

#include "core/Application.h"
#include "OptionParser.h"
#include <string>

namespace lionheart {

    namespace core {

        class ConsoleApplication: public lionheart::core::Application, public Singleton<ConsoleApplication> {
        friend class Singleton<ConsoleApplication>;
        protected:
            std::string m_szUsage;
            std::string m_szVersion;
            optparse::OptionParser m_OptionParser;
        public:
            ConsoleApplication();
            virtual ~ConsoleApplication();
            int run(int argc,const char * argv[]);
        };

    }

}

#endif /* CONSOLEAPPLICATION_H_ */
