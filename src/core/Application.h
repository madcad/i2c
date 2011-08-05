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


#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "core/Singleton.h"
#include "core/Log.h"

namespace lionheart {
    namespace core {
        class Application {
        protected:
            lionheart::core::Log m_Logger;
            Application();
            ~Application();
        public:
            virtual int run(int argc,const char * argv[]) = 0;
        };
    }
}

#endif /* APPLICATION_H_ */
