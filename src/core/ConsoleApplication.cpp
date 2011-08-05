/*
 * ConsoleApplication.cpp
 *
 *  Created on: 18.06.2011
 *      Author: walluhn
 */

#include "ConsoleApplication.h"

namespace lionheart {

    namespace core {

        ConsoleApplication::ConsoleApplication() {
            // TODO Auto-generated constructor stub
            m_szUsage = "usage: %prog [OPTION]... DIR [FILE]...";
            m_szVersion = "%prog 0.0.1\nCopyright (C) 2011 mad-cad.net\n";
            m_OptionParser = optparse::OptionParser()
            .usage(m_szUsage)
            .version(m_szVersion);

            m_OptionParser.add_option("-h").action("help").help("alternative help");
            m_OptionParser.add_option("-v").action("version").help("alternative version");
            m_Logger.addSink(lionheart::LogSinkPtr(new lionheart::ConsoleSink("out")));
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
            return 0;
        }

    }
}