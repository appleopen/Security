/*
 * Copyright (c) 2015 Apple Inc. All Rights Reserved.
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

#include "SecInternalReleasePriv.h"


#include <dispatch/dispatch.h>
#include <AssertMacros.h>
#include <strings.h>

#if TARGET_OS_EMBEDDED
#include <MobileGestalt.h>
#else
#include <sys/utsname.h>
#endif


bool
SecIsInternalRelease(void)
{
    static bool isInternal = false;

    return isInternal;
}

bool SecIsProductionFused(void) {
    static bool isProduction = true;
#if TARGET_OS_EMBEDDED
    static dispatch_once_t once = 0;

    dispatch_once(&once, ^{
        CFBooleanRef productionFused = MGCopyAnswer(kMGQSigningFuse, NULL);
        if (productionFused) {
            if (CFEqual(productionFused, kCFBooleanFalse)) {
                isProduction = false;
            }
            CFRelease(productionFused);
        }
    });
#else
    /* Consider all Macs dev-fused. */
    return false;
#endif
    return isProduction;
}

