#ifndef _ENCIDL_TESTER_U_H
#define _ENCIDL_TESTER_U_H

#include <openenclave/host.h>

/*
********************************************************************************
**
** Structure definitions
**
********************************************************************************
*/

struct Date
{
    uint32_t mm;
    uint32_t dd;
    uint32_t yyyy;
};

extern const OE_StructTI Date_ti;

struct Object
{
    size_t id;
    char *name;
};

extern const OE_StructTI Object_ti;

struct Node
{
    uint32_t value;
    struct Node *next;
};

extern const OE_StructTI Node_ti;

/*
********************************************************************************
**
** Inbound calls
**
********************************************************************************
*/

OE_EXTERNC int32_t OCALL_MultipleParams(
    const char *strIn,
    uint32_t numIn,
    const struct Object *objectIn,
    char *strOut,
    uint32_t *numOut,
    struct Object *objectOut,
    struct Object **objectRefOut);

/*
********************************************************************************
**
** Outbound calls
**
********************************************************************************
*/

OE_EXTERNC OE_Result ReturnVoid(    OE_Enclave* enclave);

OE_EXTERNC OE_Result ReturnUint32(
    OE_Enclave* enclave,
    uint32_t *ret);

OE_EXTERNC OE_Result ReturnStr(
    OE_Enclave* enclave,
    char **ret);

OE_EXTERNC OE_Result ReturnDate(
    OE_Enclave* enclave,
    struct Date *ret);

OE_EXTERNC OE_Result ReturnObject(
    OE_Enclave* enclave,
    struct Object *ret);

OE_EXTERNC OE_Result ReturnObjects(
    OE_Enclave* enclave,
    struct Object **ret,
    size_t count);

OE_EXTERNC OE_Result ReturnLinkedList(
    OE_Enclave* enclave,
    struct Node **ret);

OE_EXTERNC OE_Result TestStrdup(
    OE_Enclave* enclave,
    char **ret,
    const char *s);

OE_EXTERNC OE_Result CopyObject(
    OE_Enclave* enclave,
    int32_t *ret,
    struct Object *dest,
    const struct Object *src);

OE_EXTERNC OE_Result CopyObjects(
    OE_Enclave* enclave,
    int32_t *ret,
    struct Object dest[2],
    const struct Object src[2]);

OE_EXTERNC OE_Result ECALL_MultipleParams(
    OE_Enclave* enclave,
    int32_t *ret,
    const char *strIn,
    uint32_t numIn,
    const struct Object *objectIn,
    char *strOut,
    uint32_t *numOut,
    struct Object *objectOut,
    struct Object **objectRefOut);

OE_EXTERNC OE_Result GetObjectRef(
    OE_Enclave* enclave,
    int32_t *ret,
    struct Object **object);

OE_EXTERNC OE_Result ModifyObject(
    OE_Enclave* enclave,
    int32_t *ret,
    struct Object *object);

OE_EXTERNC OE_Result TestStrlcpy(
    OE_Enclave* enclave,
    size_t *ret,
    char *dest,
    const char *src,
    size_t dsize);

OE_EXTERNC OE_Result TestOptQualifier(
    OE_Enclave* enclave,
    size_t *ret,
    char *p1,
    const char *p2,
    size_t p1size);

OE_EXTERNC OE_Result ReturnIntPtr(
    OE_Enclave* enclave,
    int **ret,
    int *p,
    size_t n);

OE_EXTERNC OE_Result TestCallback(
    OE_Enclave* enclave,
    void *func);

OE_EXTERNC OE_Result TestIntPtrRef(
    OE_Enclave* enclave,
    bool *ret,
    int **intPtrOut,
    size_t n);

OE_EXTERNC OE_Result TestBufferOverun(
    OE_Enclave* enclave,
    char src[8]);

OE_EXTERNC OE_Result ReturnEnclaveMemory(
    OE_Enclave* enclave,
    void **ret);

OE_EXTERNC OE_Result TestBufferCopy(
    OE_Enclave* enclave,
    void *dest,
    const void *src,
    size_t n,
    bool forceOverwrite);

#endif /* _ENCIDL_TESTER_U_H */
