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

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Connection.h"
#pragma once
using boost::asio::ip::tcp;

class Server {
public:
    Server(boost::asio::io_service& io_service, int port = 1337);
private:
    tcp::acceptor _acceptor;
    
    void start_accept();
    void handle_accept(Connection::pointer new_connection,
                       const boost::system::error_code& error);
};
