/*
 * ConsoleApplication.cpp
 *
 *  Created on: 18.06.2011
 *      Author: walluhn
 */

#include "ConsoleApplication.h"
#include <signal.h>
#include <curses.h>

namespace lion {

    ConsoleApplication::ConsoleApplication()
    {
        m_szUsage = "usage: %prog [OPTION]... DIR [FILE]...";
        m_szVersion = "%prog 0.0.1\nCopyright (C) 2011 mad-cad.net\n";
        m_OptionParser = optparse::OptionParser()
        .usage(m_szUsage)
        .version(m_szVersion);

        m_OptionParser.add_option("-h").action("help").help("alternative help");
        m_OptionParser.add_option("-v").action("version").help("alternative version");
        m_Logger.addSink(lionheart::core::LogSinkPtr(new lionheart::core::ConsoleSink("out")));
        m_Logger.warning() << "App started22";
        m_Logger.flush();

    }

    ConsoleApplication::~ConsoleApplication() {
        // TODO Auto-generated destructor stub
    }

    int ConsoleApplication::run(int argc, const char** argv) {
        m_OptionParser.parse_args(argc, argv);
        if (argc == 0) {
            m_OptionParser.print_help();
            return 1;
        }
        m_bRunning = true;
        this->_run();
        return 0;
    }

    void ConsoleApplication::_run() {
        int num = 0;

        /* initialize your non-curses data structures here */

        // (void) signal(SIGINT, finish);      /* arrange interrupts to terminate */
        signal(SIGINT, _finish);

        (void) initscr();      /* initialize the curses library */
        keypad(stdscr, TRUE);  /* enable keyboard mapping */
        (void) nonl();         /* tell curses not to do NL->CR/NL on output */
        (void) cbreak();       /* take input chars one at a time, no wait for \n */
        (void) echo();         /* echo input - in color */

        if (has_colors())
        {
            start_color();

            /*
             * Simple color assignment, often all we need.  Color pair 0 cannot
             * be redefined.  This example uses the same value for the color
             * pair as for the foreground color, though of course that is not
             * necessary:
             */
            init_pair(1, COLOR_RED,     COLOR_BLACK);
            init_pair(2, COLOR_GREEN,   COLOR_BLACK);
            init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
            init_pair(4, COLOR_BLUE,    COLOR_BLACK);
            init_pair(5, COLOR_CYAN,    COLOR_BLACK);
            init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
            init_pair(7, COLOR_WHITE,   COLOR_BLACK);
        }

        while (ConsoleApplication::m_bRunning) {
            int c = getch();     /* refresh, accept single keystroke of input */
            attrset(COLOR_PAIR(num % 8));
            num++;
            if (c == 'q') {
                ConsoleApplication::_finish(1);
                break;
            }
            /* process the command keystroke */
        }
    }
    bool ConsoleApplication::m_bRunning = false;
}
