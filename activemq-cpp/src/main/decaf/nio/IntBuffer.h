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

#ifndef _DECAF_NIO_INTBUFFER_H_
#define _DECAF_NIO_INTBUFFER_H_

#include <decaf/nio/Buffer.h>
#include <decaf/lang/Comparable.h>
#include <decaf/lang/exceptions/NullPointerException.h>
#include <decaf/lang/exceptions/IndexOutOfBoundsException.h>
#include <decaf/nio/BufferUnderflowException.h>
#include <decaf/nio/BufferOverflowException.h>
#include <decaf/nio/ReadOnlyBufferException.h>

namespace decaf{
namespace nio{

    /**
     * This class defines four categories of operations upon int buffers:
     *
     * o Absolute and relative get and put methods that read and write single ints;
     * o Relative bulk get methods that transfer contiguous sequences of ints from
     *   this buffer into an array; and
     * o Relative bulk put methods that transfer contiguous sequences of ints from a
     *   int array or some other int buffer into this buffer
     * o Methods for compacting, duplicating, and slicing a int buffer.
     *
     * Double buffers can be created either by allocation, which allocates space for the
     * buffer's content, by wrapping an existing int array into a buffer, or by
     * creating a view of an existing byte buffer
     *
     * Methods in this class that do not otherwise have a value to return are specified
     * to return the buffer upon which they are invoked. This allows method invocations
     * to be chained.
     */
    class DECAF_API IntBuffer : public Buffer,
                                public lang::Comparable<IntBuffer> {
    protected:

        /**
        * Creates a IntBuffer object that has its backing array allocated internally
        * and is then owned and deleted when this object is deleted.  The array is
        * initially created with all elements initialized to zero.
        * @param capacity - size and limit of the Buffer in doubles
        */
        IntBuffer( std::size_t capacity );

    public:

        virtual ~IntBuffer() {}

        /**
         * @returns a std::string describing this object
         */
        virtual std::string toString() const;

        /**
         * Returns the int array that backs this buffer  (optional operation).
         * <p>
         * Modifications to this buffer's content will cause the returned array's content
         * to be modified, and vice versa.
         * <p>
         * Invoke the hasArray method before invoking this method in order to ensure that
         * this buffer has an accessible backing array.
         * @returns the array that backs this Buffer
         * @throws ReadOnlyBufferException if this Buffer is read only.
         * @throws UnsupportedOperationException if the underlying store has no array.
         */
        virtual int* array()
            throw( decaf::lang::exceptions::UnsupportedOperationException,
                   ReadOnlyBufferException ) = 0;

        /**
         * Returns the offset within this buffer's backing array of the first element of
         * the buffer  (optional operation).
         * <p>
         * Invoke the hasArray method before invoking this method in order to ensure that
         * this buffer has an accessible backing array.
         * @returns The offset into the backing array where index zero starts.
         * @throws ReadOnlyBufferException if this Buffer is read only.
         * @throws UnsupportedOperationException if the underlying store has no array.
         */
        virtual std::size_t arrayOffset()
            throw( decaf::lang::exceptions::UnsupportedOperationException,
                   ReadOnlyBufferException ) = 0;

        /**
         * Creates a new, read-only int buffer that shares this buffer's content.
         * <p>
         * The content of the new buffer will be that of this buffer. Changes to this
         * buffer's content will be visible in the new buffer; the new buffer itself,
         * however, will be read-only and will not allow the shared content to be
         * modified. The two buffers' position, limit, and mark values will be
         * independent.
         * <p>
         * If this buffer is itself read-only then this method behaves in exactly the
         * same way as the duplicate method.
         * <p>
         * The new buffer's capacity, limit, position, and mark values will be
         * identical to those of this buffer.
         * @return The new, read-only int buffer which the caller then owns.
         */
        virtual IntBuffer* asReadOnlyBuffer() const = 0;

        /**
         * Compacts this buffer
         * <p>
         * The bytes between the buffer's current position and its limit, if any, are
         * copied to the beginning of the buffer. That is, the byte at index
         * p = position() is copied to index zero, the byte at index p + 1 is copied
         * to index one, and so forth until the byte at index limit() - 1 is copied
         * to index n = limit() - 1 - p. The buffer's position is then set to n+1 and
         * its limit is set to its capacity. The mark, if defined, is discarded.
         * <p>
         * The buffer's position is set to the number of bytes copied, rather than to
         * zero, so that an invocation of this method can be followed immediately by
         * an invocation of another relative put method.
         * @returns a reference to this IntBuffer
         * @throws ReadOnlyBufferException - If this buffer is read-only
         */
        virtual IntBuffer& compact() throw( ReadOnlyBufferException ) = 0;

        /**
         * Creates a new int buffer that shares this buffer's content.
         * <p>
         * The content of the new buffer will be that of this buffer. Changes to this
         * buffer's content will be visible in the new buffer, and vice versa; the two
         * buffers' position, limit, and mark values will be independent.
         * <p>
         * The new buffer's capacity, limit, position, and mark values will be identical
         * to those of this buffer. The new buffer will be read-only if, and only if,
         * this buffer is read-only.
         * @returns a new int Buffer which the caller owns.
         */
        virtual IntBuffer* duplicate() = 0;

        /**
         * Relative get method. Reads the value at this buffer's current position,
         * and then increments the position.
         * @returns the int at the current position
         * @throws BufferUnderflowException if there no more data to return
         */
        virtual int get() throw ( BufferUnderflowException ) = 0;

        /**
         * Absolute get method. Reads the value at the given index.
         * @param index - the index in the Buffer where the int is to be read
         * @returns the int that is located at the given index
         * @throws IndexOutOfBoundsException - If index is not smaller than the
         * buffer's limit
         */
        virtual int get( std::size_t index ) const
            throw ( lang::exceptions::IndexOutOfBoundsException ) = 0;

        /**
         * Relative bulk get method.
         * <p>
         * This method transfers values from this buffer into the given destination
         * vector. An invocation of this method of the form src.get(a) behaves in
         * exactly the same way as the invocation.  The vector must be sized to the
         * amount of data that is to be read, that is to say, the caller should call
         * buffer.resize( N ) before calling this get method.
         * @returns a reference to this Buffer
         * @throws BufferUnderflowException - If there are fewer than length ints
         * remaining in this buffer
         */
        IntBuffer& get( std::vector<int> buffer )
            throw ( BufferUnderflowException );

        /**
         * Relative bulk get method.
         * <p>
         * This method transfers ints from this buffer into the given destination array.
         * If there are fewer ints remaining in the buffer than are required to satisfy
         * the request, that is, if length > remaining(), then no bytes are transferred
         * and a BufferUnderflowException is thrown.
         * <p>
         * Otherwise, this method copies length ints from this buffer into the given
         * array, starting at the current position of this buffer and at the given offset
         * in the array. The position of this buffer is then incremented by length.
         * <p>
         * @param buffer - pointer to an allocated buffer to fill
         * @param offset - position in the buffer to start filling
         * @param length - amount of data to put in the passed buffer
         * @returns a reference to this Buffer
         * @throws BufferUnderflowException - If there are fewer than length ints
         * remaining in this buffer
         * @throws NullPointerException if the passed buffer is null.
         */
        IntBuffer& get( int* buffer, std::size_t offset, std::size_t length )
            throw( BufferUnderflowException,
                   lang::exceptions::NullPointerException );

        /**
         * Tells whether or not this buffer is backed by an accessible int array.
         * If this method returns true then the array and arrayOffset methods may safely
         * be invoked.  Subclasses should override this method if they do not have a
         * backing array as this class always returns true.
         * @returns true if, and only if, this buffer is backed by an array and is not
         * read-only
         */
        virtual bool hasArray() const = 0;

        /**
         * This method transfers the ints remaining in the given source buffer into
         * this buffer. If there are more ints remaining in the source buffer than in
         * this buffer, that is, if src.remaining() > remaining(), then no ints are
         * transferred and a BufferOverflowException is thrown.
         * <p>
         * Otherwise, this method copies n = src.remaining() ints from the given
         * buffer into this buffer, starting at each buffer's current position. The
         * positions of both buffers are then incremented by n.
         * @param src - the buffer to take ints from an place in this one.
         * @returns a reference to this buffer
         * @throws BufferOverflowException - If there is insufficient space in this
         * buffer for the remaining ints in the source buffer
         * @throws IllegalArgumentException - If the source buffer is this buffer
         * @throws ReadOnlyBufferException - If this buffer is read-only
         */
        IntBuffer& put( IntBuffer& src )
            throw( BufferOverflowException, ReadOnlyBufferException,
                   lang::exceptions::IllegalArgumentException );

        /**
         * This method transfers ints into this buffer from the given source array.
         * If there are more ints to be copied from the array than remain in this buffer,
         * that is, if length > remaining(), then no ints are transferred and a
         * BufferOverflowException is thrown.
         * <p>
         * Otherwise, this method copies length bytes from the given array into this
         * buffer, starting at the given offset in the array and at the current position
         * of this buffer. The position of this buffer is then incremented by length.
         * @param buffer- The array from which ints are to be read
         * @param offset- The offset within the array of the first int to be read;
         * @param length - The number of ints to be read from the given array
         * @returns a reference to this buffer
         * @throws BufferOverflowException - If there is insufficient space in this buffer
         * @throws ReadOnlyBufferException - If this buffer is read-only
         * @throws NullPointerException if the passed buffer is null.
         */
        IntBuffer& put( const int* buffer, std::size_t offset, std::size_t length )
            throw( BufferOverflowException, ReadOnlyBufferException,
                   lang::exceptions::NullPointerException );

        /**
         * This method transfers the entire content of the given source ints array into
         * this buffer.  This is the same as calling put( &buffer[0], 0, buffer.size()
         * @param buffer - The buffer whose contents are copied to this IntBuffer
         * @returns a reference to this buffer
         * @throws BufferOverflowException - If there is insufficient space in this buffer
         * @throws ReadOnlyBufferException - If this buffer is read-only
         */
        IntBuffer& put( std::vector<int>& buffer )
            throw( BufferOverflowException, ReadOnlyBufferException );

        /**
         * Writes the given ints into this buffer at the current position, and then
         * increments the position.
         * @param value - the ints value to be written
         * @returns a reference to this buffer
         * @throws BufferOverflowException - If this buffer's current position is not
         * smaller than its limit
         * @throws ReadOnlyBufferException - If this buffer is read-only
         */
        virtual IntBuffer& put( int value )
            throw( BufferOverflowException, ReadOnlyBufferException ) = 0;

        /**
         * Writes the given ints into this buffer at the given index.
         * @param index - position in the Buffer to write the data
         * @param value - the ints to write.
         * @returns a reference to this buffer
         * @throws IndexOutOfBoundsException - If index greater than the buffer's limit
         * minus the size of the type being written.
         * @throws ReadOnlyBufferException - If this buffer is read-only
         */
        virtual IntBuffer& put( std::size_t index, int value )
            throw( lang::exceptions::IndexOutOfBoundsException,
                   ReadOnlyBufferException ) = 0;

        /**
         * Creates a new IntBuffer whose content is a shared subsequence of this
         * buffer's content.  The content of the new buffer will start at this buffer's
         * current position. Changes to this buffer's content will be visible in the new
         * buffer, and vice versa; the two buffers' position, limit, and mark values will
         * be independent.
         * <p>
         * The new buffer's position will be zero, its capacity and its limit will be the
         * number of bytes remaining in this buffer, and its mark will be undefined. The
         * new buffer will be read-only if, and only if, this buffer is read-only.
         * @returns the newly create IntBuffer which the caller owns.
         */
        virtual IntBuffer* slice() const = 0;

    public:  // Comparable

        /**
         * Compares this object with the specified object for order. Returns a
         * negative integer, zero, or a positive integer as this object is less
         * than, equal to, or greater than the specified object.
         * @param value - the Object to be compared.
         * @returns a negative integer, zero, or a positive integer as this
         * object is less than, equal to, or greater than the specified object.
         */
        virtual int compareTo( const IntBuffer& value ) const;

        /**
         * @return true if this value is considered equal to the passed value.
         */
        virtual bool equals( const IntBuffer& value ) const;

        /**
         * Compares equality between this object and the one passed.
         * @param value - the value to be compared to this one.
         * @return true if this object is equal to the one passed.
         */
        virtual bool operator==( const IntBuffer& value ) const;

        /**
         * Compares this object to another and returns true if this object
         * is considered to be less than the one passed.  This
         * @param value - the value to be compared to this one.
         * @return true if this object is equal to the one passed.
         */
        virtual bool operator<( const IntBuffer& value ) const;

    public:   // Statics

        /**
         * Allocates a new Double buffer.
         * <p>
         * The new buffer's position will be zero, its limit will be its capacity, and
         * its mark will be undefined. It will have a backing array, and its array offset
         * will be zero.
         * @param capacity - The size of the Double buffer in ints
         * @returns the IntBuffer that was allocated, caller owns.
         */
        static IntBuffer* allocate( std::size_t capacity );

        /**
         * Wraps the passed buffer with a new IntBuffer.
         * <p>
         * The new buffer will be backed by the given int array; that is, modifications
         * to the buffer will cause the array to be modified and vice versa. The new
         * buffer's capacity will be array.length, its position will be offset, its limit
         * will be offset + length, and its mark will be undefined. Its backing array
         * will be the given array, and its array offset will be zero.
         * @param array - The array that will back the new buffer
         * @param offset - The offset of the subarray to be used
         * @param length - The length of the subarray to be used
         * @returns a new IntBuffer that is backed by buffer, caller owns.
         */
        static IntBuffer* wrap( int* array, std::size_t offset, std::size_t length )
            throw( lang::exceptions::NullPointerException );

        /**
         * Wraps the passed STL int Vector in a IntBuffer.
         * <p>
         * The new buffer will be backed by the given int array; modifications to the
         * buffer will cause the array to be modified and vice versa. The new buffer's
         * capacity and limit will be buffer.size(), its position will be zero, and its
         * mark will be undefined. Its backing array will be the given array, and its
         * array offset will be zero.
         * @param buffer - The vector that will back the new buffer, the vector must
         * have been sized to the desired size already by calling vector.resize( N ).
         * @returns a new IntBuffer that is backed by buffer, caller owns.
         */
        static IntBuffer* wrap( std::vector<int>& buffer );

    };

}}

#endif /*_DECAF_NIO_INTBUFFER_H_*/