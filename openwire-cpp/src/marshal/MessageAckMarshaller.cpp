/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "marshal/MessageAckMarshaller.hpp"

using namespace apache::activemq::client::marshal;

/*
 *  Marshalling code for Open Wire Format for MessageAck
 *
 * NOTE!: This file is autogenerated - do not modify!
 *        if you need to make a change, please see the Groovy scripts in the
 *        activemq-core module
 */

MessageAckMarshaller::MessageAckMarshaller()
{
    // no-op
}

MessageAckMarshaller::~MessageAckMarshaller()
{
    // no-op
}



IDataStructure* MessageAckMarshaller::createObject() 
{
    return new MessageAck();
}

char MessageAckMarshaller::getDataStructureType() 
{
    return MessageAck.ID_MessageAck;
}

    /* 
     * Un-marshal an object instance from the data input stream
     */ 
void MessageAckMarshaller::unmarshal(ProtocolFormat& wireFormat, Object o, BinaryReader& dataIn, BooleanStream& bs) 
{
    base.unmarshal(wireFormat, o, dataIn, bs);

    MessageAck& info = (MessageAck&) o;
        info.setDestination((org.apache.activemq.command.ActiveMQDestination) tightUnmarsalCachedObject(wireFormat, dataIn, bs));
        info.setTransactionId((org.apache.activemq.command.TransactionId) tightUnmarsalCachedObject(wireFormat, dataIn, bs));
        info.setConsumerId((org.apache.activemq.command.ConsumerId) tightUnmarsalCachedObject(wireFormat, dataIn, bs));
        info.setAckType(dataIn.readByte());
        info.setFirstMessageId((org.apache.activemq.command.MessageId) tightUnmarsalNestedObject(wireFormat, dataIn, bs));
        info.setLastMessageId((org.apache.activemq.command.MessageId) tightUnmarsalNestedObject(wireFormat, dataIn, bs));
        info.setMessageCount(dataIn.readInt());

}


/*
 * Write the booleans that this object uses to a BooleanStream
 */
int MessageAckMarshaller::marshal1(ProtocolFormat& wireFormat, Object& o, BooleanStream& bs) {
    MessageAck& info = (MessageAck&) o;

    int rc = base.marshal1(wireFormat, info, bs);
    rc += marshal1CachedObject(wireFormat, info.getDestination(), bs);
    rc += marshal1CachedObject(wireFormat, info.getTransactionId(), bs);
    rc += marshal1CachedObject(wireFormat, info.getConsumerId(), bs);
        rc += marshal1NestedObject(wireFormat, info.getFirstMessageId(), bs);
    rc += marshal1NestedObject(wireFormat, info.getLastMessageId(), bs);
    
    return rc + 2;
}

/* 
 * Write a object instance to data output stream
 */
void MessageAckMarshaller::marshal2(ProtocolFormat& wireFormat, Object& o, BinaryWriter& dataOut, BooleanStream& bs) {
    base.marshal2(wireFormat, o, dataOut, bs);

    MessageAck& info = (MessageAck&) o;
    marshal2CachedObject(wireFormat, info.getDestination(), dataOut, bs);
    marshal2CachedObject(wireFormat, info.getTransactionId(), dataOut, bs);
    marshal2CachedObject(wireFormat, info.getConsumerId(), dataOut, bs);
    DataStreamMarshaller.writeByte(info.getAckType(), dataOut);
    marshal2NestedObject(wireFormat, info.getFirstMessageId(), dataOut, bs);
    marshal2NestedObject(wireFormat, info.getLastMessageId(), dataOut, bs);
    DataStreamMarshaller.writeInt(info.getMessageCount(), dataOut);

}
