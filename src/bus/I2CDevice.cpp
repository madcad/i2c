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

#include <bitset>
#include "I2CDevice.h"
#include "core/Log.h"
#include "core/Application.h"

#define N_ELEMENTS(X)           (sizeof(X)/sizeof(*(X)))

namespace lionheart {
    namespace bus {

        bool I2CMasterDevice::start() {
            boost::mutex::scoped_lock lock(m_ioMutex);
            return _start();
        }

        bool I2CMasterDevice::stop() {
            boost::mutex::scoped_lock lock(m_ioMutex);
            return _stop();
        }

        bool I2CMasterDevice::read(uint8_t address, void* data, int length) {
            boost::mutex::scoped_lock lock(m_ioMutex);
            return _read(address, data, length);
        }

        bool I2CMasterDevice::write(uint8_t address, uint8_t* data) {
            boost::mutex::scoped_lock lock(m_ioMutex);
            return _write(address, data);
        }
        
        boost::mutex I2CMasterDevice::m_ioMutex;

        uint8_t I2CMasterDevice::getStatus() {
            boost::mutex::scoped_lock lock(m_ioMutex);
            return _getStatus();
        }

        void I2CMasterDevice::findDevice(int8_t address) {
            uint8_t empty_data = 0x00;
            this->start();
            this->write(address, &empty_data);
            this->stop();
        }

        void I2CMasterDevice::scanBus() {
            uint32_t buffer;
            uint8_t last_device = 127;
            for (uint8_t i = 0; i < last_device; i++) {
                this->findDevice(i);
                if (this->getStatus() == STATUS_ADDRESS_ACK) {
                    std::bitset<sizeof (uint8_t) * 8 > binary(i); //sizeof() returns bytes, not bits!
                    std::cout << "found device: " << std::hex << (int) i << std::endl;
                    std::cout << "Binary: " << binary << std::endl;
                }
            }
        }

        I2CTinyUsbDevice::I2CTinyUsbDevice() : I2C_TINY_USB_VID(0x0403), I2C_TINY_USB_PID(0xc631) {
            LOGGER->note() << "I2CTinyUsbDevice created.";
            this->_init(0, false);
            LOGGER->flush();
        }

        I2CTinyUsbDevice::~I2CTinyUsbDevice() {
            LOGGER->note() << "I2CTinyUsbDevice destoyed.";
        }

        bool I2CTinyUsbDevice::_start() {
            return true;
        }

        bool I2CTinyUsbDevice::_stop() {
            return true;
        }

        int8_t I2CTinyUsbDevice::_readMaster(const uint8_t command, void* data, int length) {
            int nBytes;

            /* send control request and accept return value */
            nBytes = usb_control_msg(m_handle,
                    USB_CTRL_IN,
                    command, 0, 0,
                    reinterpret_cast<char*> (data), length, 1000);

            if (nBytes < 0) {
                LOGGER->error() << "USB error: " << usb_strerror();
                return nBytes;
            }

            return 0;
        }

        bool I2CTinyUsbDevice::_read(uint8_t address, void* data, int length) {
            if (usb_control_msg(m_handle,
                    USB_CTRL_IN,
                    CMD_I2C_IO /* + CMD_I2C_END */,
                    I2C_M_RD, address, reinterpret_cast<char*> (data), length,
                    1000) < 1) {
                LOGGER->error() << "USB error: " << usb_strerror();
                return false;
            }

            return true;
        }

        bool I2CTinyUsbDevice::_write(uint8_t address, uint8_t* data) {
            if (usb_control_msg(m_handle, USB_CTRL_OUT,
                    CMD_I2C_IO /* + CMD_I2C_BEGIN + CMD_I2C_END */,
                    0, address, reinterpret_cast<char*> (data),
                    sizeof (data) / sizeof (unsigned short int),
                    1000) < 1) {
                LOGGER->error() << "USB error: " << usb_strerror();
                return false;
            }

            return true;
        }

        uint8_t I2CTinyUsbDevice::_getStatus() {
            int i;
            unsigned char status;

            if ((i = this->_readMaster(CMD_GET_STATUS, &status, sizeof (status))) < 0) {
                LOGGER->error() << "Error reading status";
                return i;
            }

            return status;
        }

        bool I2CTinyUsbDevice::_init(uint16_t address, bool mode10) {
            struct usb_bus *bus;
            struct usb_device *dev;

            usb_init();
            usb_find_busses();
            usb_find_devices();

            for (bus = usb_get_busses(); bus; bus = bus->next) {
                for (dev = bus->devices; dev; dev = dev->next) {
                    if ((dev->descriptor.idVendor == I2C_TINY_USB_VID) &&
                            (dev->descriptor.idProduct == I2C_TINY_USB_PID)) {

                        LOGGER->note() << "Found i2c_tiny_usb device on bus " <<
                                bus->dirname << " device " << dev->filename << ".";

                        /* open device */
                        if (!(m_handle = usb_open(dev))) {
                            LOGGER->error() << "Cannot open the device: " << usb_strerror();
                            LOGGER->flush();
                            return false;
                        }

                        break;
                    }
                }
            }

            if (!m_handle) {
                LOGGER->error() << "No i2c-tiny-usb adapter found.";
                LOGGER->flush();
                return false;
            }

            if ((usb_claim_interface(m_handle, 0)) != 0) {
                LOGGER->error() << "Cannot open the device: " << usb_strerror();
                LOGGER->flush();
                return false;
            }

            this->_getFunctionality();

            /* try to set i2c clock to 100kHz (10us), will actually result in ~50kHz */
            /* since the software generated i2c clock isn't too exact. in fact setting */
            /* it to 10us doesn't do anything at all since this already is the default */
            this->_setValue(CMD_SET_DELAY, 10);

            return true;
        }

        void I2CTinyUsbDevice::_getFunctionality() {
            unsigned long func;

            if (this->_readMaster(CMD_GET_FUNC, &func, sizeof (func)) == 0) {
                LOGGER->note() << "Functionality = " << std::hex << func << std::dec;
            }
        }

        void I2CTinyUsbDevice::_setValue(uint8_t command, int8_t value) {
            if (usb_control_msg(m_handle,
                    USB_TYPE_VENDOR, command, value, 0,
                    NULL, 0, 1000) < 0) {
                LOGGER->error() << "USB error: " << usb_strerror();
            }
        }
    }
}


