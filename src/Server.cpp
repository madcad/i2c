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

#include "Server.h"
#include "Connection.h"

Server::Server(boost::asio::io_service& io_service, int port)
: _acceptor(io_service, tcp::endpoint(tcp::v4(), port))
{
    this->start_accept();
}


void Server::start_accept()
{
    Connection::pointer connection = Connection::create(this->_acceptor.io_service());
    this->_acceptor.async_accept(connection->socket(),
                                 boost::bind(&Server::handle_accept, 
                                             this, 
                                             connection,
                                             boost::asio::placeholders::error)
                                 );
}

void Server::handle_accept(Connection::pointer connection,
                   const boost::system::error_code& error)
{
    if (!error)
    {
        connection->start();
        start_accept();
    }
}

