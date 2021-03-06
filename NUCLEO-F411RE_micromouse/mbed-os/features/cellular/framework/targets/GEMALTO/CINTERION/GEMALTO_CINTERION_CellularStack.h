/*
 * Copyright (c) 2018, Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GEMALTO_CINTERION_CELLULAR_STACK_H_
#define GEMALTO_CINTERION_CELLULAR_STACK_H_

#include "AT_CellularStack.h"

namespace mbed {

class GEMALTO_CINTERION_CellularStack : public AT_CellularStack {
public:
    GEMALTO_CINTERION_CellularStack(ATHandler &atHandler, const char *apn, int cid, nsapi_ip_stack_t stack_type);
    virtual ~GEMALTO_CINTERION_CellularStack();

protected:

    virtual nsapi_error_t socket_stack_init();

    virtual int get_max_socket_count();

    virtual bool is_protocol_supported(nsapi_protocol_t protocol);

    virtual nsapi_error_t socket_close_impl(int sock_id);

    virtual nsapi_error_t create_socket_impl(CellularSocket *socket);

    virtual nsapi_size_or_error_t socket_sendto_impl(CellularSocket *socket, const SocketAddress &address,
                                                     const void *data, nsapi_size_t size);

    virtual nsapi_size_or_error_t socket_recvfrom_impl(CellularSocket *socket, SocketAddress *address,
                                                       void *buffer, nsapi_size_t size);

private:
    // find the socket handle based on socket identifier
    CellularSocket *find_socket(int sock_id);

    // socket URC handlers as per Cinterion AT manuals
    void urc_sis();
    void urc_sisw();
    void urc_sisr();

    // sockets need a connection profile, one profile is enough to support single stack sockets
    bool create_connection_profile();

    // socket open need to be deferred until sendto due to BGS2 does not support UDP server endpoint
    nsapi_error_t socket_open_defer(CellularSocket *socket, const SocketAddress *address = NULL);

    // connection profile configuration needs Access Point Name
    const char *_apn;
};

} // namespace mbed

#endif /* GEMALTO_CINTERION_CELLULAR_STACK_H_ */
