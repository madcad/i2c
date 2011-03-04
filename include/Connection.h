/**
 * Copyright (C) 2011 Torsten Walluhn <mail@mad-cad.net>
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


#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#pragma once
using boost::asio::ip::tcp;

class Connection : public boost::enable_shared_from_this<Connection> {
public:
    typedef boost::shared_ptr<Connection> pointer;
    
    static pointer create(boost::asio::io_service& io_service) 
    {
        return pointer(new Connection(io_service));
    }
    tcp::socket& socket();
    void start();
    
private:
    Connection(boost::asio::io_service& io_service);
    void handle_write(const boost::system::error_code& /*error*/,
                      size_t /*bytes_transferred*/)
    {};

    tcp::socket _socket;
    std::string _message;
};
