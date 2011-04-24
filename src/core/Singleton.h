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

namespace lionheart {
    namespace core {
        template<class T>
        class Singleton : public boost::noncopyable {
        public:
            static void initialize();
            static void destroy();
            static T& getInstance();
        protected:
            Singleton();
            virtual ~Singleton();
        private:
            static T* m_instance;
        };
    }
}

#endif /* SINGLETON_H_ */
