/*
 * Copyright (c) 2003-2004,2011-2014 Apple Inc. All Rights Reserved.
 * 
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _SECURITY_SECKEYCHAINPRIV_H_
#define _SECURITY_SECKEYCHAINPRIV_H_

#include <Security/Security.h>
#include <Security/SecBasePriv.h>
#include <Security/SecKeychain.h>
#include <CoreFoundation/CoreFoundation.h>

#if defined(__cplusplus)
extern "C" {
#endif

enum {kSecKeychainEnteredBatchModeEvent = 14,
	  kSecKeychainLeftBatchModeEvent = 15};
enum {kSecKeychainEnteredBatchModeEventMask = 1 << kSecKeychainEnteredBatchModeEvent,
	  kSecKeychainLeftBatchModeEventMask = 1 << kSecKeychainLeftBatchModeEvent};


/* Keychain management */
OSStatus SecKeychainCreateNew(SecKeychainRef keychainRef, UInt32 passwordLength, const char* inPassword)
    __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
OSStatus SecKeychainMakeFromFullPath(const char *fullPathName, SecKeychainRef *keychainRef)
    __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
OSStatus SecKeychainIsValid(SecKeychainRef keychainRef, Boolean* isValid)
    __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
OSStatus SecKeychainChangePassword(SecKeychainRef keychainRef, UInt32 oldPasswordLength, const void *oldPassword,  UInt32 newPasswordLength, const void *newPassword)
    __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);
OSStatus SecKeychainOpenWithGuid(const CSSM_GUID *guid, uint32 subserviceId, uint32 subserviceType, const char* dbName, const CSSM_NET_ADDRESS *dbLocation, SecKeychainRef *keychain)
    API_DEPRECATED("CSSM_GUID/CSSM_NET_ADDRESS is deprecated", macos(10.4,10.14)) API_UNAVAILABLE(ios);
OSStatus SecKeychainSetBatchMode (SecKeychainRef kcRef, Boolean mode, Boolean rollback)
    __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/* Keychain list management */
UInt16 SecKeychainListGetCount(void)
    __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);
OSStatus SecKeychainListCopyKeychainAtIndex(UInt16 index, SecKeychainRef *keychainRef)
    __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);
OSStatus SecKeychainListRemoveKeychain(SecKeychainRef *keychainRef)
    __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);
OSStatus SecKeychainRemoveFromSearchList(SecKeychainRef keychainRef)
    __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Login keychain support */
OSStatus SecKeychainLogin(UInt32 nameLength, const void* name, UInt32 passwordLength, const void* password)
    __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);
OSStatus SecKeychainStash(void)
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);
OSStatus SecKeychainLogout(void)
    __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);
OSStatus SecKeychainCopyLogin(SecKeychainRef *keychainRef)
    __OSX_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_NA);
OSStatus SecKeychainResetLogin(UInt32 passwordLength, const void* password, Boolean resetSearchList)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_NA);

OSStatus SecKeychainVerifyKeyStorePassphrase(uint32_t retries)
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);
OSStatus SecKeychainChangeKeyStorePassphrase(void)
    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_NA);

/* Keychain synchronization */
enum {
  kSecKeychainNotSynchronized = 0,
  kSecKeychainSynchronizedWithDotMac = 1
};
typedef UInt32 SecKeychainSyncState;

OSStatus SecKeychainCopySignature(SecKeychainRef keychainRef, CFDataRef *keychainSignature)
    __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
OSStatus SecKeychainCopyBlob(SecKeychainRef keychainRef, CFDataRef *dbBlob)
    __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
OSStatus SecKeychainRecodeKeychain(SecKeychainRef keychainRef, CFArrayRef dbBlobArray, CFDataRef extraData)
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);
OSStatus SecKeychainCreateWithBlob(const char* fullPathName, CFDataRef dbBlob, SecKeychainRef *kcRef)
    __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Keychain list manipulation */
OSStatus SecKeychainAddDBToKeychainList (SecPreferencesDomain domain, const char* dbName, const CSSM_GUID *guid, uint32 subServiceType)
    API_DEPRECATED("CSSM_GUID is deprecated", macos(10.4,10.14)) API_UNAVAILABLE(ios);
OSStatus SecKeychainDBIsInKeychainList (SecPreferencesDomain domain, const char* dbName, const CSSM_GUID *guid, uint32 subServiceType)
    API_DEPRECATED("CSSM_GUID is deprecated", macos(10.4,10.14)) API_UNAVAILABLE(ios);
OSStatus SecKeychainRemoveDBFromKeychainList (SecPreferencesDomain domain, const char* dbName, const CSSM_GUID *guid, uint32 subServiceType)
    API_DEPRECATED("CSSM_GUID is deprecated", macos(10.4,10.14)) API_UNAVAILABLE(ios);

/* server operation (keychain inhibit) */
void SecKeychainSetServerMode(void)
    __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/* special calls */
OSStatus SecKeychainCleanupHandles(void)
    __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);
OSStatus SecKeychainSystemKeychainCheckWouldDeadlock(void)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
OSStatus SecKeychainStoreUnlockKey(SecKeychainRef userKeychainRef, SecKeychainRef systemKeychainRef, CFStringRef username, CFStringRef password)
    __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_NA);

/* Token login support */
OSStatus SecKeychainStoreUnlockKeyWithPubKeyHash(CFDataRef pubKeyHash, CFStringRef tokenID, CFDataRef wrapPubKeyHash, SecKeychainRef userKeychain, CFStringRef password)
    __OSX_AVAILABLE_STARTING(__MAC_10_12, __IPHONE_NA);
OSStatus SecKeychainEraseUnlockKeyWithPubKeyHash(CFDataRef pubKeyHash)
    __OSX_AVAILABLE_STARTING(__MAC_10_12, __IPHONE_NA);

/* calls to interact with keychain versions */
OSStatus SecKeychainGetKeychainVersion(SecKeychainRef keychain, UInt32* version)
    __OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_NA);

OSStatus SecKeychainAttemptMigrationWithMasterKey(SecKeychainRef keychain, UInt32 version, const char* masterKeyFilename)
    __OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_NA);

/* calls for testing only */
OSStatus SecKeychainGetUserPromptAttempts(uint32_t* attempts)
    __OSX_AVAILABLE_STARTING(__MAC_10_12, __IPHONE_NA);

/*!
 @function SecKeychainMDSInstall
 Set up MDS.
 */
OSStatus SecKeychainMDSInstall(void);

#if defined(__cplusplus)
}
#endif

#endif /* !_SECURITY_SECKEYCHAINPRIV_H_ */
