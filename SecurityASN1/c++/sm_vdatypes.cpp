//   NOTE: this is a machine generated file--editing not recommended
//
// sm_vdatypes.cpp - class member functions for ASN.1 module VdaEnhancedTypes
//
//   This file was generated by snacc on Mon Apr 22 22:34:19 2002
//   UBC snacc written by Mike Sample
//   A couple of enhancements made by IBM European Networking Center


#include "asn-incl.h"
#include "sm_vdatypes.h"
#include "sm_x501ud.h"
#include "sm_x411ub.h"
#include "sm_x411mtsas.h"
#include "sm_x501if.h"
#include "sm_x520sa.h"
#include "sm_x509cmn.h"
#include "sm_x509af.h"
#include "sm_x509ce.h"
#include "pkcs1oids.h"
#include "pkcs9oids.h"
#include "sm_cms.h"
#include "sm_ess.h"
#include "pkcs7.h"
#include "pkcs8.h"
#include "appleoids.h"
#include "pkcs10.h"

//------------------------------------------------------------------------------
// value defs


//------------------------------------------------------------------------------
// class member definitions:

AsnType *BigIntegerStr::Clone() const
{
  return new BigIntegerStr;
}

AsnType *BigIntegerStr::Copy() const
{
  return new BigIntegerStr (*this);
}

AsnLen BigIntegerStr::BEnc (BUF_TYPE b)
{
    AsnLen l;
    l = BEncContent (b);
    l += BEncDefLen (b, l);

    l += BEncTag1 (b, UNIV, PRIM, INTEGER_TAG_CODE);
    return l;
}

void BigIntegerStr::BDec (BUF_TYPE b, AsnLen &bytesDecoded, ENV_TYPE env)
{
    AsnTag tag;
    AsnLen elmtLen1;

    if (((tag = BDecTag (b, bytesDecoded, env)) != MAKE_TAG_ID (UNIV, PRIM, INTEGER_TAG_CODE))
        && (tag != MAKE_TAG_ID (UNIV, CONS, INTEGER_TAG_CODE)))
    {
        Asn1Error << "BigIntegerStr::BDec: ERROR - wrong tag" << endl;
        SnaccExcep::throwMe(-100);
    }
    elmtLen1 = BDecLen (b, bytesDecoded, env);
    BDecContent (b, tag, elmtLen1, bytesDecoded, env);
}

