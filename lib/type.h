#pragma once

#include "error.h"
#include "varlink.h"

#include <stdio.h>

typedef struct VarlinkType VarlinkType;

typedef enum {
        VARLINK_TYPE_BOOL = 0,
        VARLINK_TYPE_INT,
        VARLINK_TYPE_FLOAT,
        VARLINK_TYPE_STRING,
        VARLINK_TYPE_ARRAY,
        VARLINK_TYPE_ENUM,
        VARLINK_TYPE_OBJECT,
        VARLINK_TYPE_FOREIGN_OBJECT,
        VARLINK_TYPE_ALIAS
} VarlinkTypeKind;

typedef struct VarlinkTypeField {
        char *name;
        VarlinkType *type;
        char *description;
} VarlinkTypeField;

struct VarlinkType {
        unsigned long refcount;
        char *typestring;
        VarlinkTypeKind kind;

        VarlinkTypeField **fields;
        unsigned long n_fields;
        AVLTree *fields_sorted;

        VarlinkType *element_type;
        unsigned long fixed_n_elements;

        char *alias;
};

long varlink_type_new(VarlinkType **typep, const char *typestring);
bool varlink_type_new_from_scanner(VarlinkType **typep, Scanner *scanner);
VarlinkType *varlink_type_ref(VarlinkType *type);
VarlinkType *varlink_type_unref(VarlinkType *type);
void varlink_type_unrefp(VarlinkType **typep);
long varlink_type_allocate(VarlinkType **typep, VarlinkTypeKind kind);
void varlink_type_field_freep(VarlinkTypeField **fieldp);
const char *varlink_type_get_typestring(VarlinkType *type);
VarlinkType *varlink_type_field_get_type(VarlinkType *type, const char *name);
long varlink_type_write_typestring(VarlinkType *type,
                                   FILE *stream,
                                   long indent,
                                   const char *comment_pre, const char *comment_post,
                                   const char *type_pre, const char *type_post);
