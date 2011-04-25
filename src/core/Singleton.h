/*
 * Singleton.h
 *
 *  Created on: 24.04.2011
 *      Author: walluhn
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
