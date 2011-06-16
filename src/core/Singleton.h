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


#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <boost/utility.hpp>
#include <boost/thread/once.hpp>
#include <boost/scoped_ptr.hpp>
#include "Exceptions.h"

namespace lionheart {
    namespace core {
        template<typename T>
        class Singleton: public boost::noncopyable {
        public:
            static void destroy() {
                if (m_instance == 0) {
                    throw PreconditionException();
                }

                if (m_instance) {
                    delete m_instance;
                    m_instance = 0;
                }
            };
            static T* getInstance(){
                if (!m_instance) {
                    m_instance = new T();
                }
                assert(m_instance != NULL);
                return m_instance; //return dereferenced instance
            };
        protected:
            Singleton() {};
            virtual ~Singleton() {};
        private:
            static T* m_instance;
        };

        template <typename T> T* Singleton<T>::m_instance = 0;
    }
}

#endif /* SINGLETON_H_ */
