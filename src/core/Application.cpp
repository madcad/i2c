/*
 * Application.cpp
 *
 *  Created on: 24.04.2011
 *      Author: walluhn
 */

#include "Application.h"
#include "OptionParser.h"
#include "LogSink.h"
#include "Log.h"

int lionheart::core::Application::run(int argc, const char** argv) {
    m_Logger.warning() << "App started22: " << __LINE__;
    m_Logger.warning() << "App started22: " << __LINE__;
    m_Logger.warning() << "App started22: " << __LINE__;
    m_Logger.warning() << "App started22: " << __LINE__;
    m_Logger.warning() << "App started22: " << __LINE__;
    m_Logger.warning() << "App started22: " << __LINE__;
    m_OptionParser.parse_args(argc, argv);
    // vector<string> args = parser.args();
    if (argc == 0) {
        m_OptionParser.print_help();
        return 1;
    }
    return 0;
}


lionheart::core::Application::Application() {
    m_szUsage = "usage: %prog [OPTION]... DIR [FILE]...";
    m_szVersion = "%prog 0.0.1\nCopyright (C) 2011 mad-cad.net\n";
    m_OptionParser = optparse::OptionParser()
    .usage(m_szUsage)
    .version(m_szVersion);

    m_OptionParser.add_option("-h").action("help").help("alternative help");
    m_OptionParser.add_option("-v").action("version").help("alternative version");
    m_Logger.addSink(lionheart::LogSinkPtr(new lionheart::ConsoleSink("out")));
    m_Logger.warning() << "App started22";
    m_Logger.warning() << "App started22: " << __LINE__;
}

lionheart::core::Application::~Application() {
    m_Logger.flush();
}
