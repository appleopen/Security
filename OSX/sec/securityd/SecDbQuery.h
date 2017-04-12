/*
 * Copyright (c) 2013-2014 Apple Inc. All Rights Reserved.
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

/*!
 @header SecDbQuery.h - The thing that does the stuff with the gibli.
 */

#ifndef _SECURITYD_SECDBQUERY_H_
#define _SECURITYD_SECDBQUERY_H_

#include <securityd/SecKeybagSupport.h>
#include <securityd/SecDbItem.h>

__BEGIN_DECLS

typedef struct Pair *SecDbPairRef;
typedef struct Query *SecDbQueryRef;

/* Return types. */
typedef uint32_t ReturnTypeMask;
enum
{
    kSecReturnDataMask = 1 << 0,
    kSecReturnAttributesMask = 1 << 1,
    kSecReturnRefMask = 1 << 2,
    kSecReturnPersistentRefMask = 1 << 3,
};

/* Constant indicating there is no limit to the number of results to return. */
enum
{
    kSecMatchUnlimited = kCFNotFound
};

typedef struct Pair
{
    const void *key;
    const void *value;
} Pair;

/* Nothing in this struct is retained since all the
 values below are extracted from the dictionary passed in by the
 caller. */
typedef struct Query
{
    /* Class of this query. */
    const SecDbClass *q_class;

    /* Dictionary with all attributes and values in clear (to be encrypted). */
    CFMutableDictionaryRef q_item;

    /* q_pairs is an array of Pair structs.  Elements with indices
     [0, q_attr_end) contain attribute key value pairs.  Elements with
     indices [q_match_begin, q_match_end) contain match key value pairs.
     Thus q_attr_end is the number of attrs in q_pairs and
     q_match_begin - q_match_end is the number of matches in q_pairs.  */
    CFIndex q_match_begin;
    CFIndex q_match_end;
    CFIndex q_attr_end;

    CFErrorRef q_error;
    ReturnTypeMask q_return_type;

    CFDataRef q_data;
    CFTypeRef q_ref;
    sqlite_int64 q_row_id;

    CFArrayRef q_use_item_list;
    CFBooleanRef q_use_tomb;

    /* Value of kSecMatchLimit key if present. */
    CFIndex q_limit;

    /* True if query contained a kSecAttrSynchronizable attribute,
     * regardless of its actual value. If this is false, then we
     * will add an explicit sync=0 to the query. */
    bool q_sync;

    // Set to true if we modified any item as part of executing this query
    bool q_changed;

    // Set to true if we modified any synchronizable item as part of executing this query
    bool q_sync_changed;
    
    /* Keybag handle to use for this item. */
    keybag_handle_t q_keybag;

    /* musr view to use when modifying the database */
    CFDataRef q_musrView;

    /* ACL and credHandle passed to the query. q_cred_handle contain LA context object. */
    SecAccessControlRef q_access_control;
    CFDataRef q_use_cred_handle;
    
    // Flag indicating that ui-protected items should be simply skipped
    // instead of reporting them to the client as an error.
    bool q_skip_acl_items;

    // SHA1 digest of DER encoded primary key
    CFDataRef q_primary_key_digest;

    CFArrayRef q_match_issuer;

    /* Caller acces groups for AKS */
    CFArrayRef q_caller_access_groups;
    bool q_system_keychain;
    int32_t q_sync_bubble;
    bool q_spindump_on_failure;

    //policy for filtering certs and identities
    SecPolicyRef q_match_policy;
    //date for filtering certs and identities
    CFDateRef q_match_valid_on_date;
    //trusted only certs and identities
    CFBooleanRef q_match_trusted_only;

    CFIndex q_pairs_count;
    Pair q_pairs[];
} Query;

Query *query_create(const SecDbClass *qclass, CFDataRef musr, CFDictionaryRef query, CFErrorRef *error);
bool query_destroy(Query *q, CFErrorRef *error);
bool query_error(Query *q, CFErrorRef *error);
Query *query_create_with_limit(CFDictionaryRef query, CFDataRef musr, CFIndex limit, CFErrorRef *error);
void query_add_attribute(const void *key, const void *value, Query *q);
void query_add_or_attribute(const void *key, const void *value, Query *q);
void query_add_not_attribute(const void *key, const void *value, Query *q);
void query_add_attribute_with_desc(const SecDbAttr *desc, const void *value, Query *q);
void query_ensure_access_control(Query *q, CFStringRef agrp);
void query_pre_add(Query *q, bool force_date);
bool query_notify_and_destroy(Query *q, bool ok, CFErrorRef *error);
CFIndex query_match_count(const Query *q);
CFIndex query_attr_count(const Query *q);
Pair query_attr_at(const Query *q, CFIndex ix);
bool query_update_parse(Query *q, CFDictionaryRef update, CFErrorRef *error);
const SecDbClass *kc_class_with_name(CFStringRef name);
void query_set_caller_access_groups(Query *q, CFArrayRef caller_access_groups);
void query_set_policy(Query *q, SecPolicyRef policy);
void query_set_valid_on_date(Query *q, CFDateRef policy);
void query_set_trusted_only(Query *q, CFBooleanRef trusted_only);

CFDataRef
SecMUSRCopySystemKeychainUUID(void);

CFDataRef
SecMUSRGetSystemKeychainUUID(void);

CFDataRef
SecMUSRGetSingleUserKeychainUUID(void);

bool
SecMUSRIsSingleUserView(CFDataRef uuid);

CFDataRef
SecMUSRGetAllViews(void);

bool
SecMUSRIsViewAllViews(CFDataRef musr);

#if TARGET_OS_IPHONE
CFDataRef
SecMUSRCreateActiveUserUUID(uid_t uid);

CFDataRef
SecMUSRCreateSyncBubbleUserUUID(uid_t uid);

CFDataRef
SecMUSRCreateBothUserAndSystemUUID(uid_t uid);

bool
SecMUSRGetBothUserAndSystemUUID(CFDataRef musr, uid_t *uid);

#endif


__END_DECLS

#endif /* _SECURITYD_SECDBQUERY_H_ */
