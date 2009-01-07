/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ActiveMQCPP.h"

#include <decaf/lang/Runtime.h>
#include <activemq/wireformat/WireFormatRegistry.h>
#include <activemq/transport/TransportRegistry.h>
#include <activemq/connector/openwire/OpenWireFormatFactory.h>

#include <activemq/transport/IOTransportFactory.h>
#include <activemq/transport/mock/MockTransportFactory.h>
#include <activemq/transport/tcp/TcpTransportFactory.h>
#include <activemq/transport/logging/LoggingTransportFactory.h>
#include <activemq/transport/correlator/ResponseCorrelatorFactory.h>
#include <activemq/connector/stomp/StompConnectorFactory.h>
#include <activemq/connector/openwire/OpenWireConnectorFactory.h>

using namespace activemq;
using namespace activemq::library;
using namespace activemq::transport;
using namespace activemq::transport::tcp;
using namespace activemq::transport::correlator;
using namespace activemq::transport::logging;
using namespace activemq::transport::mock;
using namespace activemq::wireformat;

////////////////////////////////////////////////////////////////////////////////
void ActiveMQCPP::initializeLibrary() {

    // Initialize the Decaf Library by requesting its runtime.
    decaf::lang::Runtime::getRuntime();

    connector::stomp::StompConnectorFactory::getInstance();
    connector::openwire::OpenWireConnectorFactory::getInstance();

    // Register all WireFormats
    ActiveMQCPP::registerWireFormats();

    // Registr all Transports
    ActiveMQCPP::registerTransports();
}

////////////////////////////////////////////////////////////////////////////////
void ActiveMQCPP::shutdownLibrary() {

}

////////////////////////////////////////////////////////////////////////////////
void ActiveMQCPP::registerWireFormats() {

    // Each of the internally implemented WireFormat's is registered here
    // with the WireFormat Registry

    WireFormatRegistry::getInstance().registerFactory(
        "openwire", new connector::openwire::OpenWireFormatFactory() );

}

////////////////////////////////////////////////////////////////////////////////
void ActiveMQCPP::registerTransports() {

    // Each of the internally implemented WireFormat's is registered here
    // with the WireFormat Registry

    TransportRegistry::getInstance().registerFactory(
        "tcp", new TcpTransportFactory() );
    TransportRegistry::getInstance().registerFactory(
        "transport.logging.LoggingTransport", new LoggingTransportFactory() );
    TransportRegistry::getInstance().registerFactory(
        "transport.correlator.ResponseCorrelator", new ResponseCorrelatorFactory() );
    TransportRegistry::getInstance().registerFactory(
        "transport.IOTransport", new IOTransportFactory() );
    TransportRegistry::getInstance().registerFactory(
        "mock", new MockTransportFactory() );

}
