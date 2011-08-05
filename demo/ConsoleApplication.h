/*
 * ConsoleApplication.h
 *
 *  Created on: 18.06.2011
 *      Author: walluhn
 */

#ifndef _CONSOLEAPPLICATION_H_
#define _CONSOLEAPPLICATION_H_

#include "core/Application.h"
#include "core/Singleton.h"
#include "OptionParser.h"
#include <string>
#include <curses.h>

namespace lion {
    class ConsoleApplication: public lionheart::core::Application,
    public lionheart::core::Singleton<ConsoleApplication>
    {
        friend class lionheart::core::Singleton<ConsoleApplication>;
    protected:
        std::string m_szUsage;
        std::string m_szVersion;
        optparse::OptionParser m_OptionParser;
        void _run();
        static void _finish(int sig) {
            ConsoleApplication::m_bRunning = false;
            endwin();
            // exit(0);
        }
        static bool m_bRunning;
    public:
        ConsoleApplication();
        virtual ~ConsoleApplication();
        int run(int argc,const char * argv[]);
    };
}

#endif /* CONSOLEAPPLICATION_H_ */
