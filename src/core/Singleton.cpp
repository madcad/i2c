/*
 * Singleton.cpp
 *
 *  Created on: 24.04.2011
 *      Author: walluhn
 */

#include "Singleton.h"
#include "Exceptions.h"

namespace lionheart {
    namespace core {
        template<class T>
        Singleton<T>::Singleton() {
            if (m_instance != 0) {
                throw PreconditionException(
                        "Attempt to double-initialize singleton.");
            }

            m_instance = static_cast<T*> (this); // cast self to type of T*
        }

        template<class T>
        Singleton<T>::~Singleton() {
        }

        template<class T>
        void Singleton<T>::destroy() {
            if (m_instance == 0) {
                throw PreconditionException(
                        "Attempt to destroy null singleton.");
            }

            if (m_instance) {
                delete m_instance;
                m_instance = 0;
            }
        }

        template<class T>
        T& Singleton<T>::getInstance() {
            if (m_instance == 0) {
                throw PreconditionException("Attempt to access null singleton.");
            }

            return *m_instance; //return dereferenced instance
        }

        template<class T>
        T* Singleton<T>::m_instance(0);
    }
}
