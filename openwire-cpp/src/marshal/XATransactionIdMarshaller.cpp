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
#include "marshal/XATransactionIdMarshaller.hpp"

using namespace apache::activemq::client::marshal;

/*
 *  Marshalling code for Open Wire Format for XATransactionId
 *
 * NOTE!: This file is autogenerated - do not modify!
 *        if you need to make a change, please see the Groovy scripts in the
 *        activemq-core module
 */

XATransactionIdMarshaller::XATransactionIdMarshaller()
{
    // no-op
}

XATransactionIdMarshaller::~XATransactionIdMarshaller()
{
    // no-op
}



IDataStructure* XATransactionIdMarshaller::createObject() 
{
    return new XATransactionId();
}

char XATransactionIdMarshaller::getDataStructureType() 
{
    return XATransactionId.ID_XATransactionId;
}

    /* 
     * Un-marshal an object instance from the data input stream
     */ 
void XATransactionIdMarshaller::unmarshal(ProtocolFormat& wireFormat, Object o, BinaryReader& dataIn, BooleanStream& bs) 
{
    base.unmarshal(wireFormat, o, dataIn, bs);

    XATransactionId& info = (XATransactionId&) o;
        info.setFormatId(dataIn.readInt());
        info.setGlobalTransactionId(tightUnmarshalByteArray(dataIn, bs));
        info.setBranchQualifier(tightUnmarshalByteArray(dataIn, bs));

}


/*
 * Write the booleans that this object uses to a BooleanStream
 */
int XATransactionIdMarshaller::marshal1(ProtocolFormat& wireFormat, Object& o, BooleanStream& bs) {
    XATransactionId& info = (XATransactionId&) o;

    int rc = base.marshal1(wireFormat, info, bs);
        bs.writeBoolean(info.getGlobalTransactionId()!=null);
    rc += info.getGlobalTransactionId()==null ? 0 : info.getGlobalTransactionId().Length+4;
    bs.writeBoolean(info.getBranchQualifier()!=null);
    rc += info.getBranchQualifier()==null ? 0 : info.getBranchQualifier().Length+4;

    return rc + 1;
}

/* 
 * Write a object instance to data output stream
 */
void XATransactionIdMarshaller::marshal2(ProtocolFormat& wireFormat, Object& o, BinaryWriter& dataOut, BooleanStream& bs) {
    base.marshal2(wireFormat, o, dataOut, bs);

    XATransactionId& info = (XATransactionId&) o;
    DataStreamMarshaller.writeInt(info.getFormatId(), dataOut);
    if(bs.readBoolean()) {
       DataStreamMarshaller.writeInt(info.getGlobalTransactionId().Length, dataOut);
       dataOut.write(info.getGlobalTransactionId());
    }
    if(bs.readBoolean()) {
       DataStreamMarshaller.writeInt(info.getBranchQualifier().Length, dataOut);
       dataOut.write(info.getBranchQualifier());
    }

}
