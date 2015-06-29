/***********************************************************************
*
* Copyright (c) 2012-2015 Barbara Geller
* Copyright (c) 2012-2015 Ansel Sermersheim
* Copyright (c) 2012-2014 Digia Plc and/or its subsidiary(-ies).
* Copyright (c) 2008-2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* This file is part of CopperSpice.
*
* CopperSpice is free software: you can redistribute it and/or 
* modify it under the terms of the GNU Lesser General Public License
* version 2.1 as published by the Free Software Foundation.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with CopperSpice.  If not, see 
* <http://www.gnu.org/licenses/>.
*
***********************************************************************/

#ifndef QATOMIC_SPARC_H
#define QATOMIC_SPARC_H

QT_BEGIN_NAMESPACE

#if defined(_LP64)

#define Q_ATOMIC_INT_REFERENCE_COUNTING_IS_ALWAYS_NATIVE

inline bool QBasicAtomicInt::isReferenceCountingNative()
{
   return true;
}
inline bool QBasicAtomicInt::isReferenceCountingWaitFree()
{
   return false;
}

#define Q_ATOMIC_INT_TEST_AND_SET_IS_ALWAYS_NATIVE
#define Q_ATOMIC_INT_TEST_AND_SET_IS_WAIT_FREE

inline bool QBasicAtomicInt::isTestAndSetNative()
{
   return true;
}
inline bool QBasicAtomicInt::isTestAndSetWaitFree()
{
   return true;
}

#define Q_ATOMIC_INT_FETCH_AND_STORE_IS_ALWAYS_NATIVE
#define Q_ATOMIC_INT_FETCH_AND_STORE_IS_WAIT_FREE

inline bool QBasicAtomicInt::isFetchAndStoreNative()
{
   return true;
}
inline bool QBasicAtomicInt::isFetchAndStoreWaitFree()
{
   return true;
}

#define Q_ATOMIC_INT_FETCH_AND_ADD_IS_ALWAYS_NATIVE

inline bool QBasicAtomicInt::isFetchAndAddNative()
{
   return true;
}
inline bool QBasicAtomicInt::isFetchAndAddWaitFree()
{
   return false;
}

#define Q_ATOMIC_POINTER_TEST_AND_SET_IS_ALWAYS_NATIVE
#define Q_ATOMIC_POINTER_TEST_AND_SET_IS_WAIT_FREE

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isTestAndSetNative()
{
   return true;
}
template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isTestAndSetWaitFree()
{
   return true;
}

#define Q_ATOMIC_POINTER_FETCH_AND_STORE_IS_ALWAYS_NATIVE
#define Q_ATOMIC_POINTER_FETCH_AND_STORE_IS_WAIT_FREE

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isFetchAndStoreNative()
{
   return true;
}
template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isFetchAndStoreWaitFree()
{
   return true;
}

#define Q_ATOMIC_POINTER_FETCH_AND_ADD_IS_ALWAYS_NATIVE

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isFetchAndAddNative()
{
   return true;
}
template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isFetchAndAddWaitFree()
{
   return false;
}

extern "C" {
   Q_CORE_EXPORT int q_atomic_increment(volatile int *ptr);
   Q_CORE_EXPORT int q_atomic_decrement(volatile int *ptr);

   Q_CORE_EXPORT int q_atomic_test_and_set_int(volatile int *ptr, int expected, int newval);
   Q_CORE_EXPORT int q_atomic_test_and_set_acquire_int(volatile int *ptr,
         int expected,
         int newval);
   Q_CORE_EXPORT int q_atomic_test_and_set_release_int(volatile int *ptr,
         int expected,
         int newval);

   Q_CORE_EXPORT int q_atomic_set_int(volatile int *ptr, int newval);
   Q_CORE_EXPORT int q_atomic_fetch_and_store_acquire_int(volatile int *ptr, int newval);
   Q_CORE_EXPORT int q_atomic_fetch_and_store_release_int(volatile int *ptr, int newval);

   Q_CORE_EXPORT int q_atomic_fetch_and_add_int(volatile int *ptr, int value);
   Q_CORE_EXPORT int q_atomic_fetch_and_add_acquire_int(volatile int *ptr, int value);
   Q_CORE_EXPORT int q_atomic_fetch_and_add_release_int(volatile int *ptr, int value);

   Q_CORE_EXPORT int q_atomic_test_and_set_ptr(volatile void *ptr, const void *expected, const void *newval);
   Q_CORE_EXPORT int q_atomic_test_and_set_acquire_ptr(volatile void *ptr,
         const void *expected,
         const void *newval);
   Q_CORE_EXPORT int q_atomic_test_and_set_release_ptr(volatile void *ptr,
         const void *expected,
         const void *newval);

   Q_CORE_EXPORT void *q_atomic_set_ptr(volatile void *ptr, const void *newval);
   Q_CORE_EXPORT void *q_atomic_fetch_and_store_acquire_ptr(volatile void *ptr, const void *newval);
   Q_CORE_EXPORT void *q_atomic_fetch_and_store_release_ptr(volatile void *ptr, const void *newval);

   Q_CORE_EXPORT void *q_atomic_fetch_and_add_ptr(volatile void *ptr, int value);
   Q_CORE_EXPORT void *q_atomic_fetch_and_add_acquire_ptr(volatile void *ptr, int value);
   Q_CORE_EXPORT void *q_atomic_fetch_and_add_release_ptr(volatile void *ptr, int value);
}

inline bool QBasicAtomicInt::ref()
{
   return fetchAndAddRelaxed(1) != -1;
}

inline bool QBasicAtomicInt::deref()
{
   return fetchAndAddRelaxed(-1) != 1;
}

inline bool QBasicAtomicInt::testAndSetRelaxed(int expectedValue, int newValue)
{
   return q_atomic_test_and_set_int(&_q_value, expectedValue, newValue) != 0;
}

inline bool QBasicAtomicInt::testAndSetAcquire(int expectedValue, int newValue)
{
   return q_atomic_test_and_set_acquire_int(&_q_value, expectedValue, newValue) != 0;
}

inline bool QBasicAtomicInt::testAndSetRelease(int expectedValue, int newValue)
{
   return q_atomic_test_and_set_release_int(&_q_value, expectedValue, newValue) != 0;
}

inline bool QBasicAtomicInt::testAndSetOrdered(int expectedValue, int newValue)
{
   return q_atomic_test_and_set_acquire_int(&_q_value, expectedValue, newValue) != 0;
}

inline int QBasicAtomicInt::fetchAndStoreRelaxed(int newValue)
{
   return q_atomic_set_int(&_q_value, newValue);
}

inline int QBasicAtomicInt::fetchAndStoreAcquire(int newValue)
{
   return q_atomic_fetch_and_store_acquire_int(&_q_value, newValue);
}

inline int QBasicAtomicInt::fetchAndStoreRelease(int newValue)
{
   return q_atomic_fetch_and_store_release_int(&_q_value, newValue);
}

inline int QBasicAtomicInt::fetchAndStoreOrdered(int newValue)
{
   return q_atomic_fetch_and_store_acquire_int(&_q_value, newValue);
}

inline int QBasicAtomicInt::fetchAndAddRelaxed(int newValue)
{
   return q_atomic_fetch_and_add_int(&_q_value, newValue);
}

inline int QBasicAtomicInt::fetchAndAddAcquire(int newValue)
{
   return q_atomic_fetch_and_add_acquire_int(&_q_value, newValue);
}

inline int QBasicAtomicInt::fetchAndAddRelease(int newValue)
{
   return q_atomic_fetch_and_add_release_int(&_q_value, newValue);
}

inline int QBasicAtomicInt::fetchAndAddOrdered(int newValue)
{
   return q_atomic_fetch_and_add_acquire_int(&_q_value, newValue);
}

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::testAndSetRelaxed(T *expectedValue, T *newValue)
{
   return q_atomic_test_and_set_ptr(&_q_value, expectedValue, newValue) != 0;
}

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::testAndSetAcquire(T *expectedValue, T *newValue)
{
   return q_atomic_test_and_set_acquire_ptr(&_q_value, expectedValue, newValue) != 0;
}

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::testAndSetRelease(T *expectedValue, T *newValue)
{
   return q_atomic_test_and_set_release_ptr(&_q_value, expectedValue, newValue) != 0;
}

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::testAndSetOrdered(T *expectedValue, T *newValue)
{
   return q_atomic_test_and_set_acquire_ptr(&_q_value, expectedValue, newValue) != 0;
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndStoreRelaxed(T *newValue)
{
   return reinterpret_cast<T *>(q_atomic_set_ptr(&_q_value, newValue));
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndStoreAcquire(T *newValue)
{
   return reinterpret_cast<T *>(q_atomic_fetch_and_store_acquire_ptr(&_q_value, newValue));
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndStoreRelease(T *newValue)
{
   return reinterpret_cast<T *>(q_atomic_fetch_and_store_release_ptr(&_q_value, newValue));
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndStoreOrdered(T *newValue)
{
   return reinterpret_cast<T *>(q_atomic_fetch_and_store_acquire_ptr(&_q_value, newValue));
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndAddRelaxed(qptrdiff valueToAdd)
{
   return reinterpret_cast<T *>(q_atomic_fetch_and_add_ptr(&_q_value, valueToAdd * sizeof(T)));
}

template <typename T>
Q_INLINE_TEMPLATE
T *QBasicAtomicPointer<T>::fetchAndAddAcquire(qptrdiff valueToAdd)
{
   return reinterpret_cast<T *>(q_atomic_fetch_and_add_acquire_ptr(&_q_value, valueToAdd * sizeof(T)));
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndAddRelease(qptrdiff valueToAdd)
{
   return reinterpret_cast<T *>(q_atomic_fetch_and_add_release_ptr(&_q_value, valueToAdd * sizeof(T)));
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndAddOrdered(qptrdiff valueToAdd)
{
   return reinterpret_cast<T *>(q_atomic_fetch_and_add_acquire_ptr(&_q_value, valueToAdd * sizeof(T)));
}

#else

#define Q_ATOMIC_INT_REFERENCE_COUNTING_IS_NOT_NATIVE

inline bool QBasicAtomicInt::isReferenceCountingNative()
{
   return false;
}
inline bool QBasicAtomicInt::isReferenceCountingWaitFree()
{
   return false;
}

#define Q_ATOMIC_INT_TEST_AND_SET_IS_NOT_NATIVE

inline bool QBasicAtomicInt::isTestAndSetNative()
{
   return false;
}
inline bool QBasicAtomicInt::isTestAndSetWaitFree()
{
   return false;
}

#define Q_ATOMIC_INT_FETCH_AND_STORE_IS_ALWAYS_NATIVE
#define Q_ATOMIC_INT_FETCH_AND_STORE_IS_WAIT_FREE

inline bool QBasicAtomicInt::isFetchAndStoreNative()
{
   return true;
}
inline bool QBasicAtomicInt::isFetchAndStoreWaitFree()
{
   return true;
}

#define Q_ATOMIC_INT_FETCH_AND_ADD_IS_NOT_NATIVE

inline bool QBasicAtomicInt::isFetchAndAddNative()
{
   return false;
}
inline bool QBasicAtomicInt::isFetchAndAddWaitFree()
{
   return false;
}

#define Q_ATOMIC_POINTER_TEST_AND_SET_IS_NOT_NATIVE

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isTestAndSetNative()
{
   return false;
}
template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isTestAndSetWaitFree()
{
   return false;
}

#define Q_ATOMIC_POINTER_FETCH_AND_STORE_IS_ALWAYS_NATIVE
#define Q_ATOMIC_POINTER_FETCH_AND_STORE_IS_WAIT_FREE

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isFetchAndStoreNative()
{
   return true;
}
template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isFetchAndStoreWaitFree()
{
   return true;
}

#define Q_ATOMIC_POINTER_FETCH_AND_ADD_IS_NOT_NATIVE

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isFetchAndAddNative()
{
   return false;
}
template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::isFetchAndAddWaitFree()
{
   return false;
}

extern "C" {
   Q_CORE_EXPORT int q_atomic_lock_int(volatile int *addr);
   Q_CORE_EXPORT int q_atomic_lock_ptr(volatile void *addr);
   Q_CORE_EXPORT void q_atomic_unlock(volatile void *addr, int value);
   Q_CORE_EXPORT int q_atomic_set_int(volatile int *ptr, int newval);
   Q_CORE_EXPORT void *q_atomic_set_ptr(volatile void *ptr, void *newval);
} // extern "C"

inline bool QBasicAtomicInt::ref()
{
   const int val = q_atomic_lock_int(&_q_value);
   q_atomic_unlock(&_q_value, val + 1);
   return val != -1;
}

inline bool QBasicAtomicInt::deref()
{
   const int val = q_atomic_lock_int(&_q_value);
   q_atomic_unlock(&_q_value, val - 1);
   return val != 1;
}

inline bool QBasicAtomicInt::testAndSetOrdered(int expectedValue, int newValue)
{
   int val = q_atomic_lock_int(&_q_value);
   if (val == expectedValue) {
      q_atomic_unlock(&_q_value, newValue);
      return true;
   }
   q_atomic_unlock(&_q_value, val);
   return false;
}

inline bool QBasicAtomicInt::testAndSetRelaxed(int expectedValue, int newValue)
{
   return testAndSetOrdered(expectedValue, newValue);
}

inline bool QBasicAtomicInt::testAndSetAcquire(int expectedValue, int newValue)
{
   return testAndSetOrdered(expectedValue, newValue);
}

inline bool QBasicAtomicInt::testAndSetRelease(int expectedValue, int newValue)
{
   return testAndSetOrdered(expectedValue, newValue);
}

inline int QBasicAtomicInt::fetchAndStoreOrdered(int newValue)
{
   return q_atomic_set_int(&_q_value, newValue);
}

inline int QBasicAtomicInt::fetchAndStoreRelaxed(int newValue)
{
   return fetchAndStoreOrdered(newValue);
}

inline int QBasicAtomicInt::fetchAndStoreAcquire(int newValue)
{
   return fetchAndStoreOrdered(newValue);
}

inline int QBasicAtomicInt::fetchAndStoreRelease(int newValue)
{
   return fetchAndStoreOrdered(newValue);
}

inline int QBasicAtomicInt::fetchAndAddOrdered(int valueToAdd)
{
   const int originalValue = q_atomic_lock_int(&_q_value);
   q_atomic_unlock(&_q_value, originalValue + valueToAdd);
   return originalValue;
}

inline int QBasicAtomicInt::fetchAndAddRelaxed(int valueToAdd)
{
   return fetchAndAddOrdered(valueToAdd);
}

inline int QBasicAtomicInt::fetchAndAddAcquire(int valueToAdd)
{
   return fetchAndAddOrdered(valueToAdd);
}

inline int QBasicAtomicInt::fetchAndAddRelease(int valueToAdd)
{
   return fetchAndAddOrdered(valueToAdd);
}

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::testAndSetOrdered(T *expectedValue, T *newValue)
{
   T *val = reinterpret_cast<T *>(q_atomic_lock_ptr(&_q_value));
   if (val == expectedValue) {
      q_atomic_unlock(&_q_value, reinterpret_cast<int>(newValue));
      return true;
   }
   q_atomic_unlock(&_q_value, reinterpret_cast<int>(val));
   return false;
}

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::testAndSetRelaxed(T *expectedValue, T *newValue)
{
   return testAndSetOrdered(expectedValue, newValue);
}

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::testAndSetAcquire(T *expectedValue, T *newValue)
{
   return testAndSetOrdered(expectedValue, newValue);
}

template <typename T>
Q_INLINE_TEMPLATE bool QBasicAtomicPointer<T>::testAndSetRelease(T *expectedValue, T *newValue)
{
   return testAndSetOrdered(expectedValue, newValue);
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndStoreOrdered(T *newValue)
{
   return reinterpret_cast<T *>(q_atomic_set_ptr(&_q_value, newValue));
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndStoreRelaxed(T *newValue)
{
   return fetchAndStoreOrdered(newValue);
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndStoreAcquire(T *newValue)
{
   return fetchAndStoreOrdered(newValue);
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndStoreRelease(T *newValue)
{
   return fetchAndStoreOrdered(newValue);
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndAddOrdered(qptrdiff valueToAdd)
{
   T *originalValue = reinterpret_cast<T *>(q_atomic_lock_ptr(&_q_value));
   q_atomic_unlock(&_q_value, int(originalValue + valueToAdd));
   return originalValue;
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndAddRelaxed(qptrdiff valueToAdd)
{
   return fetchAndAddOrdered(valueToAdd);
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndAddAcquire(qptrdiff valueToAdd)
{
   return fetchAndAddOrdered(valueToAdd);
}

template <typename T>
Q_INLINE_TEMPLATE T *QBasicAtomicPointer<T>::fetchAndAddRelease(qptrdiff valueToAdd)
{
   return fetchAndAddOrdered(valueToAdd);
}

#endif // _LP64

QT_END_NAMESPACE

#endif // QATOMIC_SPARC_H