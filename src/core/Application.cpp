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


#include "Application.h"
#include "OptionParser.h"
#include "LogSink.h"
#include "Log.h"

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}


int lionheart::core::Application::run(int argc, const char** argv) {
    m_OptionParser.parse_args(argc, argv);
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
    m_Logger.flush();
    lua_State* L = lua_open();
    lua_close(L);
}

lionheart::core::Application::~Application() {
    m_Logger.flush();
}
