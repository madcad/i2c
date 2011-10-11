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

#ifndef _I2CDEVICE_H_
#define _I2CDEVICE_H_

#include <boost/thread/mutex.hpp>
#include <stdint.h>
#include <usb.h>

#define USB_CTRL_IN    (USB_TYPE_CLASS | USB_ENDPOINT_IN)
#define USB_CTRL_OUT   (USB_TYPE_CLASS)

#define I2C_M_RD        0x01

/* commands via USB, must e.g. match command ids firmware */
#define CMD_ECHO       0
#define CMD_GET_FUNC   1
#define CMD_SET_DELAY  2
#define CMD_GET_STATUS 3
#define CMD_I2C_IO     4
#define CMD_I2C_BEGIN  1  // flag to I2C_IO
#define CMD_I2C_END    2  // flag to I2C_IO

#define STATUS_IDLE          0
#define STATUS_ADDRESS_ACK   1
#define STATUS_ADDRESS_NAK   2

namespace lionheart {
    namespace bus {
        /*
         * I2C Device interface class.
         */
        class I2CMasterDevice {
        public:
            bool start();
            bool stop();
            /*
             * Read data from the device.
             */
            bool read(uint8_t address, void* data, int length);
            /*
             * Write data to the device.
             */
            bool write(uint8_t address, uint8_t* data);
            /*
             * Get status from the device.
             */
            uint8_t getStatus();
            void findDevice(const int8_t address);
            void scanBus();
        private:
            virtual bool _start() = 0;
            virtual bool _stop() = 0;
            /*
             * Read data from the device.
             */
            virtual bool _read(uint8_t address, void* data, int length) = 0;
            /*
             * Write data to the device.
             */
            virtual bool _write(uint8_t address, uint8_t* data) = 0;
            /*
             * Get status from the device.
             */
            virtual uint8_t _getStatus() = 0;
        protected:
            static boost::mutex m_ioMutex;
        };

        class I2CTinyUsbDevice : public I2CMasterDevice {
        public:
            I2CTinyUsbDevice();
            ~I2CTinyUsbDevice();
            const uint16_t I2C_TINY_USB_VID;
            const uint16_t I2C_TINY_USB_PID;
        private:
            uint8_t _getStatus();
            bool _start();
            bool _stop();
            /*
             * Read data from the i2c-tiny-usb device.
             */
            bool _read(uint8_t address, void* data, int length);
            /*
             * Read data from the i2c-tiny-usb device Master.
             */
            int8_t _readMaster(const uint8_t command, void* data, int length);
            /*
             * Write command and data to the i2c-tiny-usb device.
             */
            bool _write(uint8_t address, uint8_t* data);
            /*
             * Get status from the i2c-tiny-usb device.
             */
        protected:
            /*
             * Initialize the i2c-tiny-usb device.
             */
            bool _init(uint16_t address, bool mode10);

            /*
             * Get functionality sting from i2c-tiny-usb device.
             */
            void _getFunctionality();

            /*
             * Set a value for a spicific command to the i2c-tiny-usb device.
             */
            void _setValue(uint8_t command, int8_t value);
        private:
            /*
             * i2c-tiny-usb device handle
             */
            usb_dev_handle* m_handle;
        };
    }
}

#endif /* _I2CDEVICE_H_ */


