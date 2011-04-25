/*
 * Application.h
 *
 *  Created on: 24.04.2011
 *      Author: walluhn
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "core/Singleton.h"
#include "Log.h"
#include "OptionParser.h"
#include <string>

namespace lionheart {
    namespace core {
        class Application : public Singleton<Application> {
        friend class Singleton<Application>;
        protected:
            std::string m_szUsage;
            std::string m_szVersion;
            optparse::OptionParser m_OptionParser;
            lionheart::Log m_Logger;
            Application();
            ~Application();
        public:
            void app();
            int run(int argc,const char * argv[]);
        };
    }
}

#endif /* APPLICATION_H_ */
