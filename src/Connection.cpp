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

#include <ctime>
#include <boost/bind.hpp>
#include "Connection.h"

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

Connection::Connection(boost::asio::io_service& io_service)
: _socket(io_service)
{
}

tcp::socket& Connection::socket() 
{
    return this->_socket;
}

void Connection::start()
{
    this->_message = make_daytime_string();
    
    boost::asio::async_write(
                             this->_socket,
                             boost::asio::buffer(this->_message),
                             boost::bind(
                                         &Connection::handle_write,
                                         shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred
                                         )
                             );
}

