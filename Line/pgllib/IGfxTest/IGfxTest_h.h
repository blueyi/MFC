
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Wed Nov 06 14:39:57 2002
 */
/* Compiler settings for IGfxTest.odl:
    Os, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __IGfxTest_h_h__
#define __IGfxTest_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IIGfxTest_FWD_DEFINED__
#define __IIGfxTest_FWD_DEFINED__
typedef interface IIGfxTest IIGfxTest;
#endif 	/* __IIGfxTest_FWD_DEFINED__ */


#ifndef __Document_FWD_DEFINED__
#define __Document_FWD_DEFINED__

#ifdef __cplusplus
typedef class Document Document;
#else
typedef struct Document Document;
#endif /* __cplusplus */

#endif 	/* __Document_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __IGfxTest_LIBRARY_DEFINED__
#define __IGfxTest_LIBRARY_DEFINED__

/* library IGfxTest */
/* [version][uuid] */ 


DEFINE_GUID(LIBID_IGfxTest,0xDB8C9A99,0x02EC,0x4990,0xAD,0x82,0x11,0xAD,0x25,0xAA,0xCD,0x28);

#ifndef __IIGfxTest_DISPINTERFACE_DEFINED__
#define __IIGfxTest_DISPINTERFACE_DEFINED__

/* dispinterface IIGfxTest */
/* [uuid] */ 


DEFINE_GUID(DIID_IIGfxTest,0xB4F0F0E1,0xF5FF,0x42B8,0xB0,0xC4,0x95,0xA0,0xA7,0x21,0x61,0xD4);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B4F0F0E1-F5FF-42B8-B0C4-95A0A72161D4")
    IIGfxTest : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IIGfxTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIGfxTest * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIGfxTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIGfxTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IIGfxTest * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IIGfxTest * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IIGfxTest * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IIGfxTest * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IIGfxTestVtbl;

    interface IIGfxTest
    {
        CONST_VTBL struct IIGfxTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIGfxTest_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IIGfxTest_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IIGfxTest_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IIGfxTest_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IIGfxTest_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IIGfxTest_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IIGfxTest_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IIGfxTest_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_Document,0x7C219655,0xBEA2,0x4F36,0x8E,0xD4,0x97,0x04,0xA7,0xCD,0xEC,0xD9);

#ifdef __cplusplus

class DECLSPEC_UUID("7C219655-BEA2-4F36-8ED4-9704A7CDECD9")
Document;
#endif
#endif /* __IGfxTest_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


