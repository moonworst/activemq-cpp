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
 
#ifndef ACTIVEMQ_TRANSPORT_EXCEPTIONRESPONSE_H_
#define ACTIVEMQ_TRANSPORT_EXCEPTIONRESPONSE_H_

#include <activemq/transport/Response.h>
#include <activemq/transport/BrokerError.h>

namespace activemq{
namespace transport{
  
    /**
     * A response object that indicates an error occurred at the
     * broker.
     */
    class ExceptionResponse : public Response{        
    public:
  
        virtual ~ExceptionResponse(){}
        
        /**
         * Gets the error from the broker.
         * @returns the error provided from the broker
         */
        virtual const BrokerError* getException() const = 0;
        
    };
    
}}

#endif /*ACTIVEMQ_TRANSPORT_EXCEPTIONRESPONSE_H_*/
