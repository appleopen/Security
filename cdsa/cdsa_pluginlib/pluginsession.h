/*
 * Copyright (c) 2000-2001 Apple Computer, Inc. All Rights Reserved.
 * 
 * The contents of this file constitute Original Code as defined in and are
 * subject to the Apple Public Source License Version 1.2 (the 'License').
 * You may not use this file except in compliance with the License. Please obtain
 * a copy of the License at http://www.apple.com/publicsource and read it before
 * using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS
 * OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT. Please see the License for the
 * specific language governing rights and limitations under the License.
 */


//
// pluginsession - an attachment session for a CSSM plugin
//
#ifndef _H_PLUGINSESSION
#define _H_PLUGINSESSION

#include <Security/c++plugin.h>
#include <Security/handleobject.h>
#include <Security/cssmalloc.h>


#ifdef _CPP_PLUGINSESSION
# pragma export on
#endif

namespace Security
{

//
// A PluginSession object describes an ongoing connection between a particular
// CSSM client and our plugin. Every time CSSM_SPI_ModuleAttach is called
// (due to the client calling CSSM_ModuleAttach), a new PluginSession object
// is created as a result. Sessions and CSSM_MODULE_HANDLES correspond one-to-one.
//
// PluginSession is meant to be the parent class of your session object.
// This is where you store per-session information.
//
class PluginSession : public CssmAllocator, public HandledObject {
    NOCOPY(PluginSession)
    friend class CssmPlugin;
public:
    PluginSession(CSSM_MODULE_HANDLE theHandle,
                  CssmPlugin &plug,
                  const CSSM_VERSION &Version,
                  uint32 SubserviceID,
                  CSSM_SERVICE_TYPE SubServiceType,
                  CSSM_ATTACH_FLAGS AttachFlags,
                  const CSSM_UPCALLS &upcalls);
    virtual ~PluginSession();
    virtual void detach();

    CssmPlugin &plugin;
    
    void sendCallback(CSSM_MODULE_EVENT event,
    				  uint32 subId = uint32(-1),
                      CSSM_SERVICE_TYPE serviceType = 0) const;

    static void unimplemented() { CssmError::throwMe(CSSM_ERRCODE_FUNCTION_NOT_IMPLEMENTED); }

protected:
    virtual CSSM_MODULE_FUNCS_PTR construct() = 0;

public:
    // implement CssmHeap::Allocator
    void *malloc(size_t size) throw(std::bad_alloc);
    void *realloc(void *addr, size_t size) throw(std::bad_alloc);
    void free(void *addr) throw() { upcalls.free_func(handle(), addr); }

	const CSSM_VERSION &version() const { return mVersion; }
    uint32 subserviceId() const { return mSubserviceId; }
    CSSM_SERVICE_TYPE subserviceType() const { return mSubserviceType; }
    CSSM_ATTACH_FLAGS attachFlags() const { return mAttachFlags; }

private:
    CSSM_VERSION mVersion;
    uint32 mSubserviceId;
    CSSM_SERVICE_TYPE mSubserviceType;
    CSSM_ATTACH_FLAGS mAttachFlags;
    const CSSM_UPCALLS &upcalls;
};

} // end namespace Security

#ifdef _CPP_PLUGINSESSION
# pragma export off
#endif

#endif //_H_PLUGINSESSION
