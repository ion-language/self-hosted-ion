

#line 8 "C:\\SRC\\ion\\system_packages\\builtin\\notes.ion"
#define __USE_MINGW_ANSI_STDIO 1
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#ifndef _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#endif

#if _MSC_VER >= 1900 || __STDC_VERSION__ >= 201112L
// Visual Studio 2015 supports enough C99/C11 features for us.
#else
#error C11 support required or Visual Studio 2015 or later
#endif

#if _MSC_VER
#define THREADLOCAL __declspec(thread)
#define INLINE static inline __forceinline
#define NOINLINE __declspec(noinline)
#endif

#if __GNUC__
#define THREADLOCAL __thread
#define INLINE static inline __attribute__((always_inline))
#define NOINLINE __attribute__((noinline))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvarargs"
#endif

#if __GNUC__ || __clang__
#define FORMAT_PRINTF(string__, first_to_check__) __attribute__ ((format (printf, string__, first_to_check__)))
#else
#define FORMAT_PRINTF(string__, first_to_check__)
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char uchar;
typedef signed char schar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef long long llong;
typedef unsigned long long ullong;

#ifdef _MSC_VER
#define alignof(x) __alignof(x)
#else
#define alignof(x) __alignof__(x)
#endif

typedef void *(*AllocFunc)(void *data, size_t size, size_t align);
typedef void (*FreeFunc)(void *data, void *ptr);

typedef struct Allocator {
    AllocFunc alloc;
    FreeFunc free;
} Allocator;

INLINE
void *default_alloc(void *allocator, size_t size, size_t align) {
    // todo: use _aligned_malloc, etc
    return malloc(size);
}

INLINE
void default_free(void *allocator, void *ptr) {
    // todo: use _aligned_free, etc
    free(ptr);
}

THREADLOCAL
Allocator *current_allocator = &(Allocator){default_alloc, default_free};

INLINE
void *generic_alloc(Allocator *allocator, size_t size, size_t align) {
    if (!size) {
        return 0;
    }
    if (!allocator) {
        allocator = current_allocator;
    } 
    return allocator->alloc(allocator, size, align);
}

INLINE
void generic_free(Allocator *allocator, void *ptr) {
    if (!allocator) {
        allocator = current_allocator;
    } 
    allocator->free(allocator, ptr);
}

INLINE
void *generic_alloc_copy(Allocator *allocator, size_t size, size_t align, const void *src) {
    if (!allocator) {
        allocator = current_allocator;
    } 
    void *ptr = allocator->alloc(allocator, size, align);
    if (!ptr) {
        return 0;
    }
    memcpy(ptr, src, size);
    return ptr;
}

#define tls_alloc(size, align) (generic_alloc(current_allocator, (size), (align)))
#define tls_free(ptr) (generic_free(current_allocator, (ptr)))
#define alloc_copy(size, align, src) (generic_alloc_copy(current_allocator, (size), (align), (src)))


#line 2 "C:\\SRC\\ion\\system_packages\\libc\\time.ion"
typedef struct tm tm_t;

#include <limits.h>
#include <stdint.h>
#include <float.h>
#include <ctype.h>
#include <errno.h>
#include <setjmp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct any any;
typedef struct TypeFieldInfo TypeFieldInfo;
typedef struct TypeEnumItemInfo TypeEnumItemInfo;
typedef struct TypeInfo TypeInfo;
typedef struct main_SrcPos main_SrcPos;
typedef struct main_Token main_Token;
typedef struct main_Map main_Map;
typedef struct main_Intern main_Intern;
typedef struct main_Arena main_Arena;
typedef struct libc_VAList libc_VAList;
typedef struct main_BufHdr main_BufHdr;

#line 44 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\main.ion"
void main(int argc, char (*argv));

#line 1 "C:\\SRC\\ion\\system_packages\\builtin\\config_win32.ion"
extern char (*IONOS);

#line 1 "C:\\SRC\\ion\\system_packages\\builtin\\config_x64.ion"
extern char (*IONARCH);

#line 1 "C:\\SRC\\ion\\system_packages\\builtin\\typeinfo.ion"
typedef ullong typeid;

typedef int TypeKind;

#line 4
#define TYPE_NONE ((TypeKind)(0))

#line 5
#define TYPE_VOID ((TypeKind)((TYPE_NONE) + (1)))

#line 6
#define TYPE_BOOL ((TypeKind)((TYPE_VOID) + (1)))

#line 7
#define TYPE_CHAR ((TypeKind)((TYPE_BOOL) + (1)))

#line 8
#define TYPE_UCHAR ((TypeKind)((TYPE_CHAR) + (1)))

#line 9
#define TYPE_SCHAR ((TypeKind)((TYPE_UCHAR) + (1)))

#line 10
#define TYPE_SHORT ((TypeKind)((TYPE_SCHAR) + (1)))

#line 11
#define TYPE_USHORT ((TypeKind)((TYPE_SHORT) + (1)))

#line 12
#define TYPE_INT ((TypeKind)((TYPE_USHORT) + (1)))

#line 13
#define TYPE_UINT ((TypeKind)((TYPE_INT) + (1)))

#line 14
#define TYPE_LONG ((TypeKind)((TYPE_UINT) + (1)))

#line 15
#define TYPE_ULONG ((TypeKind)((TYPE_LONG) + (1)))

#line 16
#define TYPE_LLONG ((TypeKind)((TYPE_ULONG) + (1)))

#line 17
#define TYPE_ULLONG ((TypeKind)((TYPE_LLONG) + (1)))

#line 18
#define TYPE_ENUM ((TypeKind)((TYPE_ULLONG) + (1)))

#line 19
#define TYPE_FLOAT ((TypeKind)((TYPE_ENUM) + (1)))

#line 20
#define TYPE_DOUBLE ((TypeKind)((TYPE_FLOAT) + (1)))

#line 21
#define TYPE_CONST ((TypeKind)((TYPE_DOUBLE) + (1)))

#line 22
#define TYPE_PTR ((TypeKind)((TYPE_CONST) + (1)))

#line 23
#define TYPE_ARRAY ((TypeKind)((TYPE_PTR) + (1)))

#line 24
#define TYPE_STRUCT ((TypeKind)((TYPE_ARRAY) + (1)))

#line 25
#define TYPE_UNION ((TypeKind)((TYPE_STRUCT) + (1)))

#line 26
#define TYPE_FUNC ((TypeKind)((TYPE_UNION) + (1)))

#line 27
#define TYPE_TUPLE ((TypeKind)((TYPE_FUNC) + (1)))

#line 60
TypeKind typeid_kind(ullong type);

#line 64
int typeid_index(ullong type);

#line 68
size_t typeid_size(ullong type);

#line 72
TypeInfo (*get_typeinfo(ullong type));

#line 86
size_t layout_struct(TypeFieldInfo (*fields), size_t num_fields);

#line 66 "C:\\SRC\\ion\\system_packages\\builtin\\types.ion"
#define UCHAR_MIN ((uchar)(0))

#line 89
#define USHORT_MIN ((short)(0))

#line 100
#define UINT_MIN ((uint)(0))

#line 111
#define ULLONG_MIN ((ullong)(0))

#line 116
#define UINT8_MIN (UCHAR_MIN)

#line 127
#define UINT16_MIN (USHORT_MIN)

#line 138
#define UINT32_MIN (UINT_MIN)

#line 149
#define UINT64_MIN (ULLONG_MIN)

#line 164
#define FLOAT_MIN (-(FLT_MAX))

#line 174
#define DOUBLE_MIN (-(DBL_MAX))

#line 19 "C:\\SRC\\ion\\system_packages\\builtin\\types_win32.ion"
#define ULONG_MIN ((ulong)(INT32_MIN))

#line 15 "C:\\SRC\\ion\\system_packages\\builtin\\types_x64.ion"
#define USIZE_MIN (UINT64_MIN)

#line 26
#define UINTPTR_MIN (UINT64_MIN)

#line 81 "C:\\SRC\\ion\\system_packages\\builtin\\typeinfo.ion"
struct any {
    void (*ptr);
    typeid type;
};

#line 839 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\lexer.ion"
void main_init_stream(char (*name), char (*buf));

#line 35 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\main.ion"
extern char (*main_code);

#line 30 "C:\\SRC\\ion\\system_packages\\builtin\\typeinfo.ion"
struct TypeFieldInfo {
    char (*name);
    typeid type;
    int offset;
};

struct TypeEnumItemInfo {
    char (*name);
    int64_t int_value;
};

struct TypeInfo {
    TypeKind kind;
    int size;
    int align;
    char (*name);
    int count;
    typeid base;
    TypeFieldInfo (*fields);
    int num_fields;
    TypeEnumItemInfo (*enum_items);
    int num_enum_items;
};

#line 293 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\lexer.ion"
extern char (*main_stream);

#line 294
extern char (*main_line_start);

#line 93
typedef int main_TokenKind;

#line 163
typedef int main_TokenMod;

#line 172
typedef int main_TokenSuffix;

#line 270
struct main_SrcPos {
    char (*name);
    int line;
};

#line 277
struct main_Token {
    main_TokenKind kind;
    main_TokenMod mod;
    main_TokenSuffix suffix;
    main_SrcPos pos;
    char (*start);
    char (*end);
    union {
        ullong int_val;
        double float_val;
        char (*str_val);
        char (*name);
    };
};

extern main_Token main_token;

#line 595
void main_next_token(void);

#line 94
#define MAIN_TOKEN_EOF ((main_TokenKind)(0))

#line 95
#define MAIN_TOKEN_COLON ((main_TokenKind)((MAIN_TOKEN_EOF) + (1)))

#line 96
#define MAIN_TOKEN_LPAREN ((main_TokenKind)((MAIN_TOKEN_COLON) + (1)))

#line 97
#define MAIN_TOKEN_RPAREN ((main_TokenKind)((MAIN_TOKEN_LPAREN) + (1)))

#line 98
#define MAIN_TOKEN_LBRACE ((main_TokenKind)((MAIN_TOKEN_RPAREN) + (1)))

#line 99
#define MAIN_TOKEN_RBRACE ((main_TokenKind)((MAIN_TOKEN_LBRACE) + (1)))

#line 100
#define MAIN_TOKEN_LBRACKET ((main_TokenKind)((MAIN_TOKEN_RBRACE) + (1)))

#line 101
#define MAIN_TOKEN_RBRACKET ((main_TokenKind)((MAIN_TOKEN_LBRACKET) + (1)))

#line 102
#define MAIN_TOKEN_COMMA ((main_TokenKind)((MAIN_TOKEN_RBRACKET) + (1)))

#line 103
#define MAIN_TOKEN_DOT ((main_TokenKind)((MAIN_TOKEN_COMMA) + (1)))

#line 104
#define MAIN_TOKEN_AT ((main_TokenKind)((MAIN_TOKEN_DOT) + (1)))

#line 105
#define MAIN_TOKEN_POUND ((main_TokenKind)((MAIN_TOKEN_AT) + (1)))

#line 106
#define MAIN_TOKEN_ELLIPSIS ((main_TokenKind)((MAIN_TOKEN_POUND) + (1)))

#line 107
#define MAIN_TOKEN_QUESTION ((main_TokenKind)((MAIN_TOKEN_ELLIPSIS) + (1)))

#line 108
#define MAIN_TOKEN_SEMICOLON ((main_TokenKind)((MAIN_TOKEN_QUESTION) + (1)))

#line 109
#define MAIN_TOKEN_KEYWORD ((main_TokenKind)((MAIN_TOKEN_SEMICOLON) + (1)))

#line 110
#define MAIN_TOKEN_INT ((main_TokenKind)((MAIN_TOKEN_KEYWORD) + (1)))

#line 111
#define MAIN_TOKEN_FLOAT ((main_TokenKind)((MAIN_TOKEN_INT) + (1)))

#line 112
#define MAIN_TOKEN_STR ((main_TokenKind)((MAIN_TOKEN_FLOAT) + (1)))

#line 113
#define MAIN_TOKEN_NAME ((main_TokenKind)((MAIN_TOKEN_STR) + (1)))

#line 114
#define MAIN_TOKEN_NEG ((main_TokenKind)((MAIN_TOKEN_NAME) + (1)))

#line 115
#define MAIN_TOKEN_NOT ((main_TokenKind)((MAIN_TOKEN_NEG) + (1)))

#define MAIN_TOKEN_FIRST_MUL ((main_TokenKind)((MAIN_TOKEN_NOT) + (1)))

#line 118
#define MAIN_TOKEN_MUL ((main_TokenKind)(MAIN_TOKEN_FIRST_MUL))

#line 119
#define MAIN_TOKEN_DIV ((main_TokenKind)((MAIN_TOKEN_MUL) + (1)))

#line 120
#define MAIN_TOKEN_MOD ((main_TokenKind)((MAIN_TOKEN_DIV) + (1)))

#line 121
#define MAIN_TOKEN_AND ((main_TokenKind)((MAIN_TOKEN_MOD) + (1)))

#line 122
#define MAIN_TOKEN_LSHIFT ((main_TokenKind)((MAIN_TOKEN_AND) + (1)))

#line 123
#define MAIN_TOKEN_RSHIFT ((main_TokenKind)((MAIN_TOKEN_LSHIFT) + (1)))

#line 124
#define MAIN_TOKEN_LAST_MUL ((main_TokenKind)(MAIN_TOKEN_RSHIFT))

#define MAIN_TOKEN_FIRST_ADD ((main_TokenKind)((MAIN_TOKEN_LAST_MUL) + (1)))

#line 127
#define MAIN_TOKEN_ADD ((main_TokenKind)(MAIN_TOKEN_FIRST_ADD))

#line 128
#define MAIN_TOKEN_SUB ((main_TokenKind)((MAIN_TOKEN_ADD) + (1)))

#line 129
#define MAIN_TOKEN_XOR ((main_TokenKind)((MAIN_TOKEN_SUB) + (1)))

#line 130
#define MAIN_TOKEN_OR ((main_TokenKind)((MAIN_TOKEN_XOR) + (1)))

#line 131
#define MAIN_TOKEN_LAST_ADD ((main_TokenKind)(MAIN_TOKEN_OR))

#define MAIN_TOKEN_FIRST_CMP ((main_TokenKind)((MAIN_TOKEN_LAST_ADD) + (1)))

#line 134
#define MAIN_TOKEN_EQ ((main_TokenKind)(MAIN_TOKEN_FIRST_CMP))

#line 135
#define MAIN_TOKEN_NOTEQ ((main_TokenKind)((MAIN_TOKEN_EQ) + (1)))

#line 136
#define MAIN_TOKEN_LT ((main_TokenKind)((MAIN_TOKEN_NOTEQ) + (1)))

#line 137
#define MAIN_TOKEN_GT ((main_TokenKind)((MAIN_TOKEN_LT) + (1)))

#line 138
#define MAIN_TOKEN_LTEQ ((main_TokenKind)((MAIN_TOKEN_GT) + (1)))

#line 139
#define MAIN_TOKEN_GTEQ ((main_TokenKind)((MAIN_TOKEN_LTEQ) + (1)))

#line 140
#define MAIN_TOKEN_LAST_CMP ((main_TokenKind)(MAIN_TOKEN_GTEQ))

#line 141
#define MAIN_TOKEN_AND_AND ((main_TokenKind)((MAIN_TOKEN_LAST_CMP) + (1)))

#line 142
#define MAIN_TOKEN_OR_OR ((main_TokenKind)((MAIN_TOKEN_AND_AND) + (1)))

#define MAIN_TOKEN_FIRST_ASSIGN ((main_TokenKind)((MAIN_TOKEN_OR_OR) + (1)))

#line 145
#define MAIN_TOKEN_ASSIGN ((main_TokenKind)(MAIN_TOKEN_FIRST_ASSIGN))

#line 146
#define MAIN_TOKEN_ADD_ASSIGN ((main_TokenKind)((MAIN_TOKEN_ASSIGN) + (1)))

#line 147
#define MAIN_TOKEN_SUB_ASSIGN ((main_TokenKind)((MAIN_TOKEN_ADD_ASSIGN) + (1)))

#line 148
#define MAIN_TOKEN_OR_ASSIGN ((main_TokenKind)((MAIN_TOKEN_SUB_ASSIGN) + (1)))

#line 149
#define MAIN_TOKEN_AND_ASSIGN ((main_TokenKind)((MAIN_TOKEN_OR_ASSIGN) + (1)))

#line 150
#define MAIN_TOKEN_XOR_ASSIGN ((main_TokenKind)((MAIN_TOKEN_AND_ASSIGN) + (1)))

#line 151
#define MAIN_TOKEN_LSHIFT_ASSIGN ((main_TokenKind)((MAIN_TOKEN_XOR_ASSIGN) + (1)))

#line 152
#define MAIN_TOKEN_RSHIFT_ASSIGN ((main_TokenKind)((MAIN_TOKEN_LSHIFT_ASSIGN) + (1)))

#line 153
#define MAIN_TOKEN_MUL_ASSIGN ((main_TokenKind)((MAIN_TOKEN_RSHIFT_ASSIGN) + (1)))

#line 154
#define MAIN_TOKEN_DIV_ASSIGN ((main_TokenKind)((MAIN_TOKEN_MUL_ASSIGN) + (1)))

#line 155
#define MAIN_TOKEN_MOD_ASSIGN ((main_TokenKind)((MAIN_TOKEN_DIV_ASSIGN) + (1)))

#line 156
#define MAIN_TOKEN_LAST_ASSIGN ((main_TokenKind)(MAIN_TOKEN_MOD_ASSIGN))

#line 157
#define MAIN_TOKEN_INC ((main_TokenKind)((MAIN_TOKEN_LAST_ASSIGN) + (1)))

#line 158
#define MAIN_TOKEN_DEC ((main_TokenKind)((MAIN_TOKEN_INC) + (1)))

#line 159
#define MAIN_TOKEN_COLON_ASSIGN ((main_TokenKind)((MAIN_TOKEN_DEC) + (1)))

#line 160
#define MAIN_NUM_TOKEN_KINDS ((main_TokenKind)((MAIN_TOKEN_COLON_ASSIGN) + (1)))

#line 164
#define MAIN_MOD_NONE ((main_TokenMod)(0))

#line 165
#define MAIN_MOD_HEX ((main_TokenMod)((MAIN_MOD_NONE) + (1)))

#line 166
#define MAIN_MOD_BIN ((main_TokenMod)((MAIN_MOD_HEX) + (1)))

#line 167
#define MAIN_MOD_OCT ((main_TokenMod)((MAIN_MOD_BIN) + (1)))

#line 168
#define MAIN_MOD_CHAR ((main_TokenMod)((MAIN_MOD_OCT) + (1)))

#line 169
#define MAIN_MOD_MULTILINE ((main_TokenMod)((MAIN_MOD_CHAR) + (1)))

#line 173
#define MAIN_SUFFIX_NONE ((main_TokenSuffix)(0))

#line 174
#define MAIN_SUFFIX_D ((main_TokenSuffix)((MAIN_SUFFIX_NONE) + (1)))

#line 175
#define MAIN_SUFFIX_U ((main_TokenSuffix)((MAIN_SUFFIX_D) + (1)))

#line 176
#define MAIN_SUFFIX_L ((main_TokenSuffix)((MAIN_SUFFIX_U) + (1)))

#line 177
#define MAIN_SUFFIX_UL ((main_TokenSuffix)((MAIN_SUFFIX_L) + (1)))

#line 178
#define MAIN_SUFFIX_LL ((main_TokenSuffix)((MAIN_SUFFIX_UL) + (1)))

#line 179
#define MAIN_SUFFIX_ULL ((main_TokenSuffix)((MAIN_SUFFIX_LL) + (1)))

#line 502
void main_scan_char(void);

#line 536
void main_scan_str(void);

#line 433
void main_scan_float(void);

#line 358
void main_scan_int(void);

#line 430 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\common.ion"
char (*main_str_intern_range(char (*start), char (*end)));

#line 89 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\lexer.ion"
bool main_is_keyword_name(char (*name));

#line 316
void main_error(main_SrcPos pos, char (*fmt), ...);

#line 481
int main_scan_hex_escape(void);

#line 468
extern char (main_escape_to_char[256]);

#line 181 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\common.ion"
void main_buf_push(void (*(*b)), void (*elem), size_t elem_size);

#line 339 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\lexer.ion"
extern uint8_t (main_char_to_digit[256]);

#line 303 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\common.ion"
uint64_t main_hash_bytes(void (*ptr), size_t len);

#line 391
void (*main_map_get_from_uint64(main_Map (*map), uint64_t key));

#line 314
struct main_Map {
    uint64_t (*keys);
    uint64_t (*vals);
    size_t len;
    size_t cap;
};

#line 428
extern main_Map main_interns;

#line 421
struct main_Intern {
    size_t len;
    main_Intern (*next);
    char (str[1]);
};

#line 264
void (*main_arena_alloc(main_Arena (*arena), size_t size));

#line 246
struct main_Arena {
    char (*ptr);
    char (*end);
    char (*(*blocks));
};

#line 427
extern main_Arena main_intern_arena;

#line 395
void main_map_put_from_uint64(main_Map (*map), uint64_t key, void (*val));

#line 26 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\lexer.ion"
extern char (*main_first_keyword);

#line 27
extern char (*main_last_keyword);

#line 19 "C:\\SRC\\ion\\system_packages\\libc\\stdio.ion"
struct libc_VAList {
    #line 21
    char (*bytes);
};

#line 312 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\lexer.ion"
void main_verror(main_SrcPos pos, char (*fmt), va_list args);

#line 173 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\common.ion"
void main_buf_fit(void (*(*b)), size_t new_len, size_t elem_size);

#line 145
size_t main_buf_len(void (*b));

#line 140
main_BufHdr (*main_buf__hdr(void (*b)));

#line 132
struct main_BufHdr {
    size_t len;
    size_t cap;
    #line 136
    char (buf[1]);
};

#line 321
uint64_t main_map_get_uint64_from_uint64(main_Map (*map), uint64_t key);

#line 256
void main_arena_grow(main_Arena (*arena), size_t min_size);

#line 42
void (*main_align_up_ptr(void (*p), size_t a));

#line 252
#define MAIN_ARENA_ALIGNMENT (8)

#line 37
void (*main_align_down_ptr(void (*p), size_t a));

#line 357
void main_map_put_uint64_from_uint64(main_Map (*map), uint64_t key, uint64_t val);

#line 296 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\lexer.ion"
void main_vnotice(char (*level), main_SrcPos pos, char (*fmt), va_list args);

#line 150 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\common.ion"
size_t main_buf_cap(void (*b));

#line 189
void (*main_buf__grow(void (*buf), size_t new_len, size_t elem_size));

#line 22
size_t main_is_pow2(size_t x);

#line 286
uint64_t main_hash_uint64(uint64_t x);

#line 32
uintptr_t main_align_up(uintptr_t n, size_t a);

#line 17
size_t main_clamp_min(size_t x, size_t min);

#line 253
#define MAIN_ARENA_BLOCK_SIZE ((1024) * (1024))

#line 74
void (*main_xmalloc(size_t num_bytes));

#line 27
uintptr_t main_align_down(uintptr_t n, size_t a);

#line 340
void main_map_grow(main_Map (*map), size_t new_cap);

#line 275 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\lexer.ion"
extern main_SrcPos main_pos_builtin;

#line 7 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\common.ion"
size_t main_max(size_t x, size_t y);

#line 65
void (*main_xrealloc(void (*ptr), size_t num_bytes));

#line 56
void (*main_xcalloc(size_t num_elems, size_t elem_size));

#define TYPEID0(index, kind) ((ullong)(index) | ((ullong)(kind) << 24))
#define TYPEID(index, kind, ...) ((ullong)(index) | ((ullong)sizeof(__VA_ARGS__) << 32) | ((ullong)(kind) << 24))

TypeInfo *typeinfo_table[264] = {
    [0] = NULL, // No associated type
    [1] = &(TypeInfo){TYPE_VOID, .name = "void", .size = 0, .align = 0},
    [2] = &(TypeInfo){TYPE_BOOL, .size = sizeof(bool), .align = sizeof(bool), .name = "bool"},
    [3] = &(TypeInfo){TYPE_CHAR, .size = sizeof(char), .align = sizeof(char), .name = "char"},
    [4] = &(TypeInfo){TYPE_UCHAR, .size = sizeof(uchar), .align = sizeof(uchar), .name = "uchar"},
    [5] = &(TypeInfo){TYPE_SCHAR, .size = sizeof(schar), .align = sizeof(schar), .name = "schar"},
    [6] = &(TypeInfo){TYPE_SHORT, .size = sizeof(short), .align = sizeof(short), .name = "short"},
    [7] = &(TypeInfo){TYPE_USHORT, .size = sizeof(ushort), .align = sizeof(ushort), .name = "ushort"},
    [8] = &(TypeInfo){TYPE_INT, .size = sizeof(int), .align = sizeof(int), .name = "int"},
    [9] = &(TypeInfo){TYPE_UINT, .size = sizeof(uint), .align = sizeof(uint), .name = "uint"},
    [10] = &(TypeInfo){TYPE_LONG, .size = sizeof(long), .align = sizeof(long), .name = "long"},
    [11] = &(TypeInfo){TYPE_ULONG, .size = sizeof(ulong), .align = sizeof(ulong), .name = "ulong"},
    [12] = &(TypeInfo){TYPE_LLONG, .size = sizeof(llong), .align = sizeof(llong), .name = "llong"},
    [13] = &(TypeInfo){TYPE_ULLONG, .size = sizeof(ullong), .align = sizeof(ullong), .name = "ullong"},
    [14] = &(TypeInfo){TYPE_FLOAT, .size = sizeof(float), .align = sizeof(float), .name = "float"},
    [15] = &(TypeInfo){TYPE_DOUBLE, .size = sizeof(double), .align = sizeof(double), .name = "double"},
    [16] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(3, TYPE_CHAR, char)},
    [17] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID0(1, TYPE_VOID)},
    [18] = NULL, // Func
    [19] = &(TypeInfo){TYPE_STRUCT, .size = sizeof(Allocator), .align = alignof(Allocator), .name = "Allocator", .num_fields = 2, .fields = (TypeFieldInfo[]) {
        {"alloc", .type = TYPEID(23, TYPE_FUNC, void (*(*)(void *, ullong, ullong))), .offset = offsetof(Allocator, alloc)},
        {"free", .type = TYPEID(24, TYPE_FUNC, void (*)(void *, void *)), .offset = offsetof(Allocator, free)},
    }},
    [20] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(19, TYPE_STRUCT, Allocator)},
    [21] = &(TypeInfo){TYPE_STRUCT, .size = sizeof(any), .align = alignof(any), .name = "any", .num_fields = 2, .fields = (TypeFieldInfo[]) {
        {"ptr", .type = TYPEID(17, TYPE_PTR, void *), .offset = offsetof(any, ptr)},
        {"type", .type = TYPEID(13, TYPE_ULLONG, ullong), .offset = offsetof(any, type)},
    }},
    [22] = NULL, // Func
    [23] = NULL, // Func
    [24] = NULL, // Func
    [25] = NULL, // Func
    [26] = NULL, // Func
    [27] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [6]), .align = alignof(char [6]), .base = TYPEID(3, TYPE_CHAR, char), .count = 6},
    [28] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [4]), .align = alignof(char [4]), .base = TYPEID(3, TYPE_CHAR, char), .count = 4},
    [29] = &(TypeInfo){TYPE_ENUM, .size = sizeof(TypeKind), .align = alignof(TypeKind), .name = "TypeKind", .base = TYPEID(8, TYPE_INT, int), .num_enum_items = 24, .enum_items = (TypeEnumItemInfo[]) {{ .name = "TYPE_NONE", .int_value = TYPE_NONE },{ .name = "TYPE_VOID", .int_value = TYPE_VOID },{ .name = "TYPE_BOOL", .int_value = TYPE_BOOL },{ .name = "TYPE_CHAR", .int_value = TYPE_CHAR },{ .name = "TYPE_UCHAR", .int_value = TYPE_UCHAR },{ .name = "TYPE_SCHAR", .int_value = TYPE_SCHAR },{ .name = "TYPE_SHORT", .int_value = TYPE_SHORT },{ .name = "TYPE_USHORT", .int_value = TYPE_USHORT },{ .name = "TYPE_INT", .int_value = TYPE_INT },{ .name = "TYPE_UINT", .int_value = TYPE_UINT },{ .name = "TYPE_LONG", .int_value = TYPE_LONG },{ .name = "TYPE_ULONG", .int_value = TYPE_ULONG },{ .name = "TYPE_LLONG", .int_value = TYPE_LLONG },{ .name = "TYPE_ULLONG", .int_value = TYPE_ULLONG },{ .name = "TYPE_ENUM", .int_value = TYPE_ENUM },{ .name = "TYPE_FLOAT", .int_value = TYPE_FLOAT },{ .name = "TYPE_DOUBLE", .int_value = TYPE_DOUBLE },{ .name = "TYPE_CONST", .int_value = TYPE_CONST },{ .name = "TYPE_PTR", .int_value = TYPE_PTR },{ .name = "TYPE_ARRAY", .int_value = TYPE_ARRAY },{ .name = "TYPE_STRUCT", .int_value = TYPE_STRUCT },{ .name = "TYPE_UNION", .int_value = TYPE_UNION },{ .name = "TYPE_FUNC", .int_value = TYPE_FUNC },{ .name = "TYPE_TUPLE", .int_value = TYPE_TUPLE },}},
    [30] = &(TypeInfo){TYPE_STRUCT, .size = sizeof(TypeFieldInfo), .align = alignof(TypeFieldInfo), .name = "TypeFieldInfo", .num_fields = 3, .fields = (TypeFieldInfo[]) {
        {"name", .type = TYPEID(16, TYPE_PTR, char *), .offset = offsetof(TypeFieldInfo, name)},
        {"type", .type = TYPEID(13, TYPE_ULLONG, ullong), .offset = offsetof(TypeFieldInfo, type)},
        {"offset", .type = TYPEID(8, TYPE_INT, int), .offset = offsetof(TypeFieldInfo, offset)},
    }},
    [31] = &(TypeInfo){TYPE_STRUCT, .size = sizeof(TypeEnumItemInfo), .align = alignof(TypeEnumItemInfo), .name = "TypeEnumItemInfo", .num_fields = 2, .fields = (TypeFieldInfo[]) {
        {"name", .type = TYPEID(16, TYPE_PTR, char *), .offset = offsetof(TypeEnumItemInfo, name)},
        {"int_value", .type = TYPEID(12, TYPE_LLONG, llong), .offset = offsetof(TypeEnumItemInfo, int_value)},
    }},
    [32] = &(TypeInfo){TYPE_STRUCT, .size = sizeof(TypeInfo), .align = alignof(TypeInfo), .name = "TypeInfo", .num_fields = 10, .fields = (TypeFieldInfo[]) {
        {"kind", .type = TYPEID(29, TYPE_ENUM, TypeKind), .offset = offsetof(TypeInfo, kind)},
        {"size", .type = TYPEID(8, TYPE_INT, int), .offset = offsetof(TypeInfo, size)},
        {"align", .type = TYPEID(8, TYPE_INT, int), .offset = offsetof(TypeInfo, align)},
        {"name", .type = TYPEID(16, TYPE_PTR, char *), .offset = offsetof(TypeInfo, name)},
        {"count", .type = TYPEID(8, TYPE_INT, int), .offset = offsetof(TypeInfo, count)},
        {"base", .type = TYPEID(13, TYPE_ULLONG, ullong), .offset = offsetof(TypeInfo, base)},
        {"fields", .type = TYPEID(39, TYPE_PTR, TypeFieldInfo *), .offset = offsetof(TypeInfo, fields)},
        {"num_fields", .type = TYPEID(8, TYPE_INT, int), .offset = offsetof(TypeInfo, num_fields)},
        {"enum_items", .type = TYPEID(44, TYPE_PTR, TypeEnumItemInfo *), .offset = offsetof(TypeInfo, enum_items)},
        {"num_enum_items", .type = TYPEID(8, TYPE_INT, int), .offset = offsetof(TypeInfo, num_enum_items)},
    }},
    [33] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(32, TYPE_STRUCT, TypeInfo)},
    [34] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(33, TYPE_PTR, TypeInfo *)},
    [35] = NULL, // Func
    [36] = NULL, // Func
    [37] = NULL, // Func
    [38] = NULL, // Func
    [39] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(30, TYPE_STRUCT, TypeFieldInfo)},
    [40] = NULL, // Func
    [41] = NULL, // Func
    [42] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [9]), .align = alignof(char [9]), .base = TYPEID(3, TYPE_CHAR, char), .count = 9},
    [43] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [103]), .align = alignof(char [103]), .base = TYPEID(3, TYPE_CHAR, char), .count = 103},
    [44] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(31, TYPE_STRUCT, TypeEnumItemInfo)},
    [45] = &(TypeInfo){TYPE_STRUCT, .size = sizeof(main_Token), .align = alignof(main_Token), .name = "main_Token", .num_fields = 10, .fields = (TypeFieldInfo[]) {
        {"kind", .type = TYPEID(46, TYPE_ENUM, main_TokenKind), .offset = offsetof(main_Token, kind)},
        {"mod", .type = TYPEID(47, TYPE_ENUM, main_TokenMod), .offset = offsetof(main_Token, mod)},
        {"suffix", .type = TYPEID(48, TYPE_ENUM, main_TokenSuffix), .offset = offsetof(main_Token, suffix)},
        {"pos", .type = TYPEID(49, TYPE_STRUCT, main_SrcPos), .offset = offsetof(main_Token, pos)},
        {"start", .type = TYPEID(16, TYPE_PTR, char *), .offset = offsetof(main_Token, start)},
        {"end", .type = TYPEID(16, TYPE_PTR, char *), .offset = offsetof(main_Token, end)},
        {"int_val", .type = TYPEID(13, TYPE_ULLONG, ullong), .offset = offsetof(main_Token, int_val)},
        {"float_val", .type = TYPEID(15, TYPE_DOUBLE, double), .offset = offsetof(main_Token, float_val)},
        {"str_val", .type = TYPEID(16, TYPE_PTR, char *), .offset = offsetof(main_Token, str_val)},
        {"name", .type = TYPEID(16, TYPE_PTR, char *), .offset = offsetof(main_Token, name)},
    }},
    [46] = &(TypeInfo){TYPE_ENUM, .size = sizeof(main_TokenKind), .align = alignof(main_TokenKind), .name = "main_TokenKind", .base = TYPEID(8, TYPE_INT, int), .num_enum_items = 63, .enum_items = (TypeEnumItemInfo[]) {{ .name = "MAIN_TOKEN_EOF", .int_value = MAIN_TOKEN_EOF },{ .name = "MAIN_TOKEN_COLON", .int_value = MAIN_TOKEN_COLON },{ .name = "MAIN_TOKEN_LPAREN", .int_value = MAIN_TOKEN_LPAREN },{ .name = "MAIN_TOKEN_RPAREN", .int_value = MAIN_TOKEN_RPAREN },{ .name = "MAIN_TOKEN_LBRACE", .int_value = MAIN_TOKEN_LBRACE },{ .name = "MAIN_TOKEN_RBRACE", .int_value = MAIN_TOKEN_RBRACE },{ .name = "MAIN_TOKEN_LBRACKET", .int_value = MAIN_TOKEN_LBRACKET },{ .name = "MAIN_TOKEN_RBRACKET", .int_value = MAIN_TOKEN_RBRACKET },{ .name = "MAIN_TOKEN_COMMA", .int_value = MAIN_TOKEN_COMMA },{ .name = "MAIN_TOKEN_DOT", .int_value = MAIN_TOKEN_DOT },{ .name = "MAIN_TOKEN_AT", .int_value = MAIN_TOKEN_AT },{ .name = "MAIN_TOKEN_POUND", .int_value = MAIN_TOKEN_POUND },{ .name = "MAIN_TOKEN_ELLIPSIS", .int_value = MAIN_TOKEN_ELLIPSIS },{ .name = "MAIN_TOKEN_QUESTION", .int_value = MAIN_TOKEN_QUESTION },{ .name = "MAIN_TOKEN_SEMICOLON", .int_value = MAIN_TOKEN_SEMICOLON },{ .name = "MAIN_TOKEN_KEYWORD", .int_value = MAIN_TOKEN_KEYWORD },{ .name = "MAIN_TOKEN_INT", .int_value = MAIN_TOKEN_INT },{ .name = "MAIN_TOKEN_FLOAT", .int_value = MAIN_TOKEN_FLOAT },{ .name = "MAIN_TOKEN_STR", .int_value = MAIN_TOKEN_STR },{ .name = "MAIN_TOKEN_NAME", .int_value = MAIN_TOKEN_NAME },{ .name = "MAIN_TOKEN_NEG", .int_value = MAIN_TOKEN_NEG },{ .name = "MAIN_TOKEN_NOT", .int_value = MAIN_TOKEN_NOT },{ .name = "MAIN_TOKEN_FIRST_MUL", .int_value = MAIN_TOKEN_FIRST_MUL },{ .name = "MAIN_TOKEN_MUL", .int_value = MAIN_TOKEN_MUL },{ .name = "MAIN_TOKEN_DIV", .int_value = MAIN_TOKEN_DIV },{ .name = "MAIN_TOKEN_MOD", .int_value = MAIN_TOKEN_MOD },{ .name = "MAIN_TOKEN_AND", .int_value = MAIN_TOKEN_AND },{ .name = "MAIN_TOKEN_LSHIFT", .int_value = MAIN_TOKEN_LSHIFT },{ .name = "MAIN_TOKEN_RSHIFT", .int_value = MAIN_TOKEN_RSHIFT },{ .name = "MAIN_TOKEN_LAST_MUL", .int_value = MAIN_TOKEN_LAST_MUL },{ .name = "MAIN_TOKEN_FIRST_ADD", .int_value = MAIN_TOKEN_FIRST_ADD },{ .name = "MAIN_TOKEN_ADD", .int_value = MAIN_TOKEN_ADD },{ .name = "MAIN_TOKEN_SUB", .int_value = MAIN_TOKEN_SUB },{ .name = "MAIN_TOKEN_XOR", .int_value = MAIN_TOKEN_XOR },{ .name = "MAIN_TOKEN_OR", .int_value = MAIN_TOKEN_OR },{ .name = "MAIN_TOKEN_LAST_ADD", .int_value = MAIN_TOKEN_LAST_ADD },{ .name = "MAIN_TOKEN_FIRST_CMP", .int_value = MAIN_TOKEN_FIRST_CMP },{ .name = "MAIN_TOKEN_EQ", .int_value = MAIN_TOKEN_EQ },{ .name = "MAIN_TOKEN_NOTEQ", .int_value = MAIN_TOKEN_NOTEQ },{ .name = "MAIN_TOKEN_LT", .int_value = MAIN_TOKEN_LT },{ .name = "MAIN_TOKEN_GT", .int_value = MAIN_TOKEN_GT },{ .name = "MAIN_TOKEN_LTEQ", .int_value = MAIN_TOKEN_LTEQ },{ .name = "MAIN_TOKEN_GTEQ", .int_value = MAIN_TOKEN_GTEQ },{ .name = "MAIN_TOKEN_LAST_CMP", .int_value = MAIN_TOKEN_LAST_CMP },{ .name = "MAIN_TOKEN_AND_AND", .int_value = MAIN_TOKEN_AND_AND },{ .name = "MAIN_TOKEN_OR_OR", .int_value = MAIN_TOKEN_OR_OR },{ .name = "MAIN_TOKEN_FIRST_ASSIGN", .int_value = MAIN_TOKEN_FIRST_ASSIGN },{ .name = "MAIN_TOKEN_ASSIGN", .int_value = MAIN_TOKEN_ASSIGN },{ .name = "MAIN_TOKEN_ADD_ASSIGN", .int_value = MAIN_TOKEN_ADD_ASSIGN },{ .name = "MAIN_TOKEN_SUB_ASSIGN", .int_value = MAIN_TOKEN_SUB_ASSIGN },{ .name = "MAIN_TOKEN_OR_ASSIGN", .int_value = MAIN_TOKEN_OR_ASSIGN },{ .name = "MAIN_TOKEN_AND_ASSIGN", .int_value = MAIN_TOKEN_AND_ASSIGN },{ .name = "MAIN_TOKEN_XOR_ASSIGN", .int_value = MAIN_TOKEN_XOR_ASSIGN },{ .name = "MAIN_TOKEN_LSHIFT_ASSIGN", .int_value = MAIN_TOKEN_LSHIFT_ASSIGN },{ .name = "MAIN_TOKEN_RSHIFT_ASSIGN", .int_value = MAIN_TOKEN_RSHIFT_ASSIGN },{ .name = "MAIN_TOKEN_MUL_ASSIGN", .int_value = MAIN_TOKEN_MUL_ASSIGN },{ .name = "MAIN_TOKEN_DIV_ASSIGN", .int_value = MAIN_TOKEN_DIV_ASSIGN },{ .name = "MAIN_TOKEN_MOD_ASSIGN", .int_value = MAIN_TOKEN_MOD_ASSIGN },{ .name = "MAIN_TOKEN_LAST_ASSIGN", .int_value = MAIN_TOKEN_LAST_ASSIGN },{ .name = "MAIN_TOKEN_INC", .int_value = MAIN_TOKEN_INC },{ .name = "MAIN_TOKEN_DEC", .int_value = MAIN_TOKEN_DEC },{ .name = "MAIN_TOKEN_COLON_ASSIGN", .int_value = MAIN_TOKEN_COLON_ASSIGN },{ .name = "MAIN_NUM_TOKEN_KINDS", .int_value = MAIN_NUM_TOKEN_KINDS },}},
    [47] = &(TypeInfo){TYPE_ENUM, .size = sizeof(main_TokenMod), .align = alignof(main_TokenMod), .name = "main_TokenMod", .base = TYPEID(8, TYPE_INT, int), .num_enum_items = 6, .enum_items = (TypeEnumItemInfo[]) {{ .name = "MAIN_MOD_NONE", .int_value = MAIN_MOD_NONE },{ .name = "MAIN_MOD_HEX", .int_value = MAIN_MOD_HEX },{ .name = "MAIN_MOD_BIN", .int_value = MAIN_MOD_BIN },{ .name = "MAIN_MOD_OCT", .int_value = MAIN_MOD_OCT },{ .name = "MAIN_MOD_CHAR", .int_value = MAIN_MOD_CHAR },{ .name = "MAIN_MOD_MULTILINE", .int_value = MAIN_MOD_MULTILINE },}},
    [48] = &(TypeInfo){TYPE_ENUM, .size = sizeof(main_TokenSuffix), .align = alignof(main_TokenSuffix), .name = "main_TokenSuffix", .base = TYPEID(8, TYPE_INT, int), .num_enum_items = 7, .enum_items = (TypeEnumItemInfo[]) {{ .name = "MAIN_SUFFIX_NONE", .int_value = MAIN_SUFFIX_NONE },{ .name = "MAIN_SUFFIX_D", .int_value = MAIN_SUFFIX_D },{ .name = "MAIN_SUFFIX_U", .int_value = MAIN_SUFFIX_U },{ .name = "MAIN_SUFFIX_L", .int_value = MAIN_SUFFIX_L },{ .name = "MAIN_SUFFIX_UL", .int_value = MAIN_SUFFIX_UL },{ .name = "MAIN_SUFFIX_LL", .int_value = MAIN_SUFFIX_LL },{ .name = "MAIN_SUFFIX_ULL", .int_value = MAIN_SUFFIX_ULL },}},
    [49] = &(TypeInfo){TYPE_STRUCT, .size = sizeof(main_SrcPos), .align = alignof(main_SrcPos), .name = "main_SrcPos", .num_fields = 2, .fields = (TypeFieldInfo[]) {
        {"name", .type = TYPEID(16, TYPE_PTR, char *), .offset = offsetof(main_SrcPos, name)},
        {"line", .type = TYPEID(8, TYPE_INT, int), .offset = offsetof(main_SrcPos, line)},
    }},
    [50] = NULL, // No associated type
    [51] = NULL, // Func
    [52] = NULL, // Func
    [53] = NULL, // Func
    [54] = NULL, // Func
    [55] = NULL, // Func
    [56] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [29]), .align = alignof(char [29]), .base = TYPEID(3, TYPE_CHAR, char), .count = 29},
    [57] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [36]), .align = alignof(char [36]), .base = TYPEID(3, TYPE_CHAR, char), .count = 36},
    [58] = NULL, // Func
    [59] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [256]), .align = alignof(char [256]), .base = TYPEID(3, TYPE_CHAR, char), .count = 256},
    [60] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [34]), .align = alignof(char [34]), .base = TYPEID(3, TYPE_CHAR, char), .count = 34},
    [61] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [38]), .align = alignof(char [38]), .base = TYPEID(3, TYPE_CHAR, char), .count = 38},
    [62] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(17, TYPE_PTR, void *)},
    [63] = NULL, // Func
    [64] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(16, TYPE_PTR, char *)},
    [65] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [56]), .align = alignof(char [56]), .base = TYPEID(3, TYPE_CHAR, char), .count = 56},
    [66] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [45]), .align = alignof(char [45]), .base = TYPEID(3, TYPE_CHAR, char), .count = 45},
    [67] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(8, TYPE_INT, int)},
    [68] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [57]), .align = alignof(char [57]), .base = TYPEID(3, TYPE_CHAR, char), .count = 57},
    [69] = &(TypeInfo){TYPE_CONST, .size = sizeof(char const ), .align = alignof(char const ), .base = TYPEID(3, TYPE_CHAR, char)},
    [70] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(69, TYPE_CONST, char const )},
    [71] = NULL, // Func
    [72] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [23]), .align = alignof(char [23]), .base = TYPEID(3, TYPE_CHAR, char), .count = 23},
    [73] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(uchar [256]), .align = alignof(uchar [256]), .base = TYPEID(4, TYPE_UCHAR, uchar), .count = 256},
    [74] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(4, TYPE_UCHAR, uchar)},
    [75] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [25]), .align = alignof(char [25]), .base = TYPEID(3, TYPE_CHAR, char), .count = 25},
    [76] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [33]), .align = alignof(char [33]), .base = TYPEID(3, TYPE_CHAR, char), .count = 33},
    [77] = NULL, // Func
    [78] = &(TypeInfo){TYPE_STRUCT, .size = sizeof(main_Intern), .align = alignof(main_Intern), .name = "main_Intern", .num_fields = 3, .fields = (TypeFieldInfo[]) {
        {"len", .type = TYPEID(13, TYPE_ULLONG, ullong), .offset = offsetof(main_Intern, len)},
        {"next", .type = TYPEID(79, TYPE_PTR, main_Intern *), .offset = offsetof(main_Intern, next)},
        {"str", .type = TYPEID(84, TYPE_ARRAY, char [1]), .offset = offsetof(main_Intern, str)},
    }},
    [79] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(78, TYPE_STRUCT, main_Intern)},
    [80] = &(TypeInfo){TYPE_STRUCT, .size = sizeof(main_Map), .align = alignof(main_Map), .name = "main_Map", .num_fields = 4, .fields = (TypeFieldInfo[]) {
        {"keys", .type = TYPEID(83, TYPE_PTR, ullong *), .offset = offsetof(main_Map, keys)},
        {"vals", .type = TYPEID(83, TYPE_PTR, ullong *), .offset = offsetof(main_Map, vals)},
        {"len", .type = TYPEID(13, TYPE_ULLONG, ullong), .offset = offsetof(main_Map, len)},
        {"cap", .type = TYPEID(13, TYPE_ULLONG, ullong), .offset = offsetof(main_Map, cap)},
    }},
    [81] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(80, TYPE_STRUCT, main_Map)},
    [82] = NULL, // Func
    [83] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(13, TYPE_ULLONG, ullong)},
    [84] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [1]), .align = alignof(char [1]), .base = TYPEID(3, TYPE_CHAR, char), .count = 1},
    [85] = NULL, // Func
    [86] = &(TypeInfo){TYPE_STRUCT, .size = sizeof(main_Arena), .align = alignof(main_Arena), .name = "main_Arena", .num_fields = 3, .fields = (TypeFieldInfo[]) {
        {"ptr", .type = TYPEID(16, TYPE_PTR, char *), .offset = offsetof(main_Arena, ptr)},
        {"end", .type = TYPEID(16, TYPE_PTR, char *), .offset = offsetof(main_Arena, end)},
        {"blocks", .type = TYPEID(64, TYPE_PTR, char (**)), .offset = offsetof(main_Arena, blocks)},
    }},
    [87] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(86, TYPE_STRUCT, main_Arena)},
    [88] = NULL, // Func
    [89] = &(TypeInfo){TYPE_CONST, .size = 0, .align = 0, .base = TYPEID0(1, TYPE_VOID)},
    [90] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID0(89, TYPE_CONST)},
    [91] = NULL, // Func
    [92] = NULL, // Func
    [93] = &(TypeInfo){TYPE_STRUCT, .size = sizeof(libc_VAList), .align = alignof(libc_VAList), .name = "libc_VAList", .num_fields = 1, .fields = (TypeFieldInfo[]) {
        {"bytes", .type = TYPEID(16, TYPE_PTR, char *), .offset = offsetof(libc_VAList, bytes)},
    }},
    [94] = NULL, // Func
    [95] = NULL, // Func
    [96] = NULL, // Func
    [97] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [30]), .align = alignof(char [30]), .base = TYPEID(3, TYPE_CHAR, char), .count = 30},
    [98] = NULL, // Func
    [99] = NULL, // Func
    [100] = &(TypeInfo){TYPE_STRUCT, .size = sizeof(main_BufHdr), .align = alignof(main_BufHdr), .name = "main_BufHdr", .num_fields = 3, .fields = (TypeFieldInfo[]) {
        {"len", .type = TYPEID(13, TYPE_ULLONG, ullong), .offset = offsetof(main_BufHdr, len)},
        {"cap", .type = TYPEID(13, TYPE_ULLONG, ullong), .offset = offsetof(main_BufHdr, cap)},
        {"buf", .type = TYPEID(84, TYPE_ARRAY, char [1]), .offset = offsetof(main_BufHdr, buf)},
    }},
    [101] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(100, TYPE_STRUCT, main_BufHdr)},
    [102] = NULL, // Func
    [103] = NULL, // Func
    [104] = NULL, // Func
    [105] = NULL, // Func
    [106] = NULL, // Func
    [107] = NULL, // Func
    [108] = NULL, // Func
    [109] = NULL, // Func
    [110] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(64, TYPE_PTR, char (**))},
    [111] = NULL, // Func
    [112] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [10]), .align = alignof(char [10]), .base = TYPEID(3, TYPE_CHAR, char), .count = 10},
    [113] = NULL, // Func
    [114] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [13]), .align = alignof(char [13]), .base = TYPEID(3, TYPE_CHAR, char), .count = 13},
    [115] = NULL, // Func
    [116] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [2]), .align = alignof(char [2]), .base = TYPEID(3, TYPE_CHAR, char), .count = 2},
    [117] = NULL, // Func
    [118] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [15]), .align = alignof(char [15]), .base = TYPEID(3, TYPE_CHAR, char), .count = 15},
    [119] = NULL, // Func
    [120] = NULL, // Func
    [121] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [16]), .align = alignof(char [16]), .base = TYPEID(3, TYPE_CHAR, char), .count = 16},
    [122] = NULL, // Func
    [123] = NULL, // Func
    [124] = NULL, // Func
    [125] = NULL, // Func
    [126] = NULL, // Func
    [127] = NULL, // Func
    [128] = NULL, // Func
    [129] = NULL, // Func
    [130] = NULL, // Func
    [131] = NULL, // Func
    [132] = NULL, // Func
    [133] = NULL, // No associated type
    [134] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char *[7]), .align = alignof(char *[7]), .base = TYPEID(16, TYPE_PTR, char *), .count = 7},
    [135] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [3]), .align = alignof(char [3]), .base = TYPEID(3, TYPE_CHAR, char), .count = 3},
    [136] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char *[7]), .align = alignof(char *[7]), .base = TYPEID(16, TYPE_PTR, char *), .count = 7},
    [137] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char *[54]), .align = alignof(char *[54]), .base = TYPEID(16, TYPE_PTR, char *), .count = 54},
    [138] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [8]), .align = alignof(char [8]), .base = TYPEID(3, TYPE_CHAR, char), .count = 8},
    [139] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [7]), .align = alignof(char [7]), .base = TYPEID(3, TYPE_CHAR, char), .count = 7},
    [140] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [5]), .align = alignof(char [5]), .base = TYPEID(3, TYPE_CHAR, char), .count = 5},
    [141] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char *[54]), .align = alignof(char *[54]), .base = TYPEID(16, TYPE_PTR, char *), .count = 54},
    [142] = NULL, // Func
    [143] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(main_TokenKind [54]), .align = alignof(main_TokenKind [54]), .base = TYPEID(46, TYPE_ENUM, main_TokenKind), .count = 54},
    [144] = NULL, // Func
    [145] = NULL, // Func
    [146] = NULL, // Func
    [147] = NULL, // No associated type
    [148] = NULL, // Func
    [149] = NULL, // Func
    [150] = NULL, // Func
    [151] = NULL, // Func
    [152] = NULL, // Func
    [153] = NULL, // Func
    [154] = NULL, // Func
    [155] = NULL, // Func
    [156] = NULL, // Func
    [157] = NULL, // Func
    [158] = NULL, // Func
    [159] = NULL, // Func
    [160] = NULL, // Func
    [161] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(14, TYPE_FLOAT, float)},
    [162] = NULL, // Func
    [163] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(15, TYPE_DOUBLE, double)},
    [164] = NULL, // Func
    [165] = NULL, // Func
    [166] = NULL, // Func
    [167] = NULL, // Func
    [168] = NULL, // Func
    [169] = NULL, // Func
    [170] = NULL, // Func
    [171] = NULL, // Func
    [172] = NULL, // Func
    [173] = NULL, // Func
    [174] = NULL, // Func
    [175] = NULL, // Func
    [176] = NULL, // Func
    [177] = NULL, // Func
    [178] = NULL, // No associated type
    [179] = NULL, // No associated type
    [180] = NULL, // No associated type
    [181] = NULL, // Func
    [182] = NULL, // Func
    [183] = NULL, // Func
    [184] = NULL, // Func
    [185] = NULL, // Func
    [186] = NULL, // Func
    [187] = NULL, // Func
    [188] = NULL, // Func
    [189] = NULL, // Func
    [190] = NULL, // Func
    [191] = NULL, // Func
    [192] = NULL, // Func
    [193] = NULL, // Func
    [194] = NULL, // Func
    [195] = NULL, // Func
    [196] = NULL, // Func
    [197] = NULL, // Func
    [198] = NULL, // Func
    [199] = NULL, // Func
    [200] = NULL, // Func
    [201] = NULL, // Func
    [202] = NULL, // No associated type
    [203] = NULL, // Func
    [204] = NULL, // Func
    [205] = NULL, // Func
    [206] = NULL, // Func
    [207] = NULL, // No associated type
    [208] = NULL, // No associated type
    [209] = NULL, // No associated type
    [210] = NULL, // Func
    [211] = NULL, // Func
    [212] = NULL, // Func
    [213] = NULL, // Func
    [214] = NULL, // Func
    [215] = NULL, // Func
    [216] = NULL, // Func
    [217] = NULL, // Func
    [218] = NULL, // Func
    [219] = NULL, // Func
    [220] = NULL, // Func
    [221] = NULL, // Func
    [222] = NULL, // Func
    [223] = NULL, // Func
    [224] = NULL, // Func
    [225] = NULL, // Func
    [226] = NULL, // Func
    [227] = NULL, // Func
    [228] = NULL, // Func
    [229] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(6, TYPE_SHORT, short)},
    [230] = NULL, // Func
    [231] = NULL, // Func
    [232] = NULL, // Func
    [233] = &(TypeInfo){TYPE_CONST, .size = sizeof(short const ), .align = alignof(short const ), .base = TYPEID(6, TYPE_SHORT, short)},
    [234] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(233, TYPE_CONST, short const )},
    [235] = NULL, // Func
    [236] = NULL, // Func
    [237] = NULL, // Func
    [238] = NULL, // Func
    [239] = NULL, // Func
    [240] = NULL, // Func
    [241] = NULL, // Func
    [242] = NULL, // Func
    [243] = NULL, // Func
    [244] = NULL, // Func
    [245] = NULL, // Func
    [246] = NULL, // Func
    [247] = NULL, // No associated type
    [248] = NULL, // Func
    [249] = NULL, // Func
    [250] = NULL, // No associated type
    [251] = NULL, // Func
    [252] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(12, TYPE_LLONG, llong)},
    [253] = NULL, // Func
    [254] = NULL, // No associated type
    [255] = NULL, // No associated type
    [256] = NULL, // Func
    [257] = &(TypeInfo){TYPE_CONST, .size = sizeof(llong const ), .align = alignof(llong const ), .base = TYPEID(12, TYPE_LLONG, llong)},
    [258] = &(TypeInfo){TYPE_PTR, .size = sizeof(void *), .align = alignof(void *), .base = TYPEID(257, TYPE_CONST, llong const )},
    [259] = NULL, // Func
    [260] = NULL, // Func
    [261] = NULL, // Func
    [262] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [14]), .align = alignof(char [14]), .base = TYPEID(3, TYPE_CHAR, char), .count = 14},
    [263] = &(TypeInfo){TYPE_ARRAY, .size = sizeof(char [26]), .align = alignof(char [26]), .base = TYPEID(3, TYPE_CHAR, char), .count = 26},
};

int num_typeinfos = 264;
TypeInfo **typeinfos = (TypeInfo **)typeinfo_table;
#line 44 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\main.ion"
void main(int argc, char (*argv)) {
    #line 46
    main_init_stream("test.ion", main_code);
}

char (*IONOS) = "win32";
char (*IONARCH) = "x64";
#line 60 "C:\\SRC\\ion\\system_packages\\builtin\\typeinfo.ion"
TypeKind typeid_kind(ullong type) {
    return (TypeKind)((((type) >> (24))) & (0xff));
}

int typeid_index(ullong type) {
    return (int)((type) & (0xffffff));
}

size_t typeid_size(ullong type) {
    return (size_t)((type) >> (32));
}

TypeInfo (*get_typeinfo(ullong type)) {
    int index = typeid_index(type);
    if ((typeinfos) && ((index) < (num_typeinfos))) {
        return typeinfos[index];
    } else {
        return NULL;
    }
}

#line 86
size_t layout_struct(TypeFieldInfo (*fields), size_t num_fields) {
    int alignment = 0;
    int off = 0;
    for (int i = 0; (i) < (num_fields); (i)++) {
        TypeInfo (*ti) = get_typeinfo(fields[i].type);
        off = ((((off) + (ti->align)) - (1))) & (~(((ti->align) - (1))));
        fields[i].offset = off;
        alignment = ((alignment) < (ti->align) ? ti->align : alignment);
        off += ti->size;
    }
    return alignment;
}

#line 839 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\lexer.ion"
void main_init_stream(char (*name), char (*buf)) {
    main_stream = buf;
    main_line_start = main_stream;
    main_token.pos.name = (name ? name : (char *)("<string>"));
    main_token.pos.line = 1;
    main_next_token();
}

char (*main_code) = 
    "\n"
    "#include <stdio.h>\n"
    "\n"
    "int main(int argc, char **argv) {\n"
    "    printf(\"Hello, world!\\n\");\n"
    "    return 0;\n"
    "}\n";
char (*main_stream);
char (*main_line_start);
main_Token main_token;
#line 595
void main_next_token(void) {
    repeat: ;
    main_token.start = main_stream;
    main_token.mod = 0;
    main_token.suffix = 0;
    switch (*(main_stream)) {
    case ' ':
    case '\n':
    case '\r':
    case '\t':
    case '\v': {
        #line 602
        while (isspace(*(main_stream))) {
            if ((*((main_stream)++)) == ('\n')) {
                main_line_start = main_stream;
                (main_token.pos.line)++;
            }
        }
        goto repeat;
        break;
    }
    case '\'': {
        #line 610
        main_scan_char();
        break;
    }
    case '\"': {
        #line 612
        main_scan_str();
        break;
    }
    case '.': {
        #line 614
        if (isdigit(main_stream[1])) {
            main_scan_float();
        } else if (((main_stream[1]) == ('.')) && ((main_stream[2]) == ('.'))) {
            main_token.kind = MAIN_TOKEN_ELLIPSIS;
            main_stream += 3;
        } else {
            main_token.kind = MAIN_TOKEN_DOT;
            (main_stream)++;
        }
        break;
    }
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
        #line 623
        {
            while (isdigit(*(main_stream))) {
                (main_stream)++;
            }
            char c = *(main_stream);
            main_stream = main_token.start;
            if (((c) == ('.')) || ((tolower(c)) == ('e'))) {
                main_scan_float();
            } else {
                main_scan_int();
            }
        }
        break;
    }
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
    case '_': {
        #line 641
        while ((isalnum(*(main_stream))) || ((*(main_stream)) == ('_'))) {
            (main_stream)++;
        }
        main_token.name = main_str_intern_range(main_token.start, main_stream);
        main_token.kind = (main_is_keyword_name(main_token.name) ? MAIN_TOKEN_KEYWORD : MAIN_TOKEN_NAME);
        break;
    }
    case '<': {
        #line 647
        main_token.kind = MAIN_TOKEN_LT;
        (main_stream)++;
        if ((*(main_stream)) == ('<')) {
            main_token.kind = MAIN_TOKEN_LSHIFT;
            (main_stream)++;
            if ((*(main_stream)) == ('=')) {
                main_token.kind = MAIN_TOKEN_LSHIFT_ASSIGN;
                (main_stream)++;
            }
        } else if ((*(main_stream)) == ('=')) {
            main_token.kind = MAIN_TOKEN_LTEQ;
            (main_stream)++;
        }
        break;
    }
    case '>': {
        #line 661
        main_token.kind = MAIN_TOKEN_GT;
        (main_stream)++;
        if ((*(main_stream)) == ('>')) {
            main_token.kind = MAIN_TOKEN_RSHIFT;
            (main_stream)++;
            if ((*(main_stream)) == ('=')) {
                main_token.kind = MAIN_TOKEN_RSHIFT_ASSIGN;
                (main_stream)++;
            }
        } else if ((*(main_stream)) == ('=')) {
            main_token.kind = MAIN_TOKEN_GTEQ;
            (main_stream)++;
        }
        break;
    }
    case '/': {
        #line 675
        main_token.kind = MAIN_TOKEN_DIV;
        (main_stream)++;
        if ((*(main_stream)) == ('=')) {
            main_token.kind = MAIN_TOKEN_DIV_ASSIGN;
            (main_stream)++;
        } else if ((*(main_stream)) == ('/')) {
            (main_stream)++;
            while ((*(main_stream)) && ((*(main_stream)) != ('\n'))) {
                (main_stream)++;
            }
            goto repeat;
        } else if ((*(main_stream)) == ('*')) {
            (main_stream)++;
            int level = 1;
            while ((*(main_stream)) && ((level) > (0))) {
                if (((main_stream[0]) == ('/')) && ((main_stream[1]) == ('*'))) {
                    (level)++;
                    main_stream += 2;
                } else if (((main_stream[0]) == ('*')) && ((main_stream[1]) == ('/'))) {
                    (level)--;
                    main_stream += 2;
                } else {
                    if ((*(main_stream)) == ('\n')) {
                        (main_token.pos.line)++;
                    }
                    (main_stream)++;
                }
            }
            goto repeat;
        }
        break;
    }
    case '\0': {
        #line 709
        main_token.kind = MAIN_TOKEN_EOF;
        (main_stream)++;
        break;
    }
    case '(': {
        #line 712
        main_token.kind = MAIN_TOKEN_LPAREN;
        (main_stream)++;
        break;
    }
    case ')': {
        #line 715
        main_token.kind = MAIN_TOKEN_RPAREN;
        (main_stream)++;
        break;
    }
    case '{': {
        #line 718
        main_token.kind = MAIN_TOKEN_LBRACE;
        (main_stream)++;
        break;
    }
    case '}': {
        #line 721
        main_token.kind = MAIN_TOKEN_RBRACE;
        (main_stream)++;
        break;
    }
    case '[': {
        #line 724
        main_token.kind = MAIN_TOKEN_LBRACKET;
        (main_stream)++;
        break;
    }
    case ']': {
        #line 727
        main_token.kind = MAIN_TOKEN_RBRACKET;
        (main_stream)++;
        break;
    }
    case ',': {
        #line 730
        main_token.kind = MAIN_TOKEN_COMMA;
        (main_stream)++;
        break;
    }
    case '@': {
        #line 733
        main_token.kind = MAIN_TOKEN_AT;
        (main_stream)++;
        break;
    }
    case '#': {
        #line 736
        main_token.kind = MAIN_TOKEN_POUND;
        (main_stream)++;
        break;
    }
    case '?': {
        #line 739
        main_token.kind = MAIN_TOKEN_QUESTION;
        (main_stream)++;
        break;
    }
    case ';': {
        #line 742
        main_token.kind = MAIN_TOKEN_SEMICOLON;
        (main_stream)++;
        break;
    }
    case '~': {
        #line 745
        main_token.kind = MAIN_TOKEN_NEG;
        (main_stream)++;
        break;
    }
    case '!': {
        #line 749
        main_token.kind = MAIN_TOKEN_NOT;
        (main_stream)++;
        if ((*(main_stream)) == ('=')) {
            main_token.kind = MAIN_TOKEN_NOTEQ;
            (main_stream)++;
        }
        break;
    }
    case ':': {
        #line 756
        main_token.kind = MAIN_TOKEN_COLON;
        (main_stream)++;
        if ((*(main_stream)) == ('=')) {
            main_token.kind = MAIN_TOKEN_COLON_ASSIGN;
            (main_stream)++;
        }
        break;
    }
    case '=': {
        #line 763
        main_token.kind = MAIN_TOKEN_ASSIGN;
        (main_stream)++;
        if ((*(main_stream)) == ('=')) {
            main_token.kind = MAIN_TOKEN_EQ;
            (main_stream)++;
        }
        break;
    }
    case '^': {
        #line 770
        main_token.kind = MAIN_TOKEN_XOR;
        (main_stream)++;
        if ((*(main_stream)) == ('=')) {
            main_token.kind = MAIN_TOKEN_XOR_ASSIGN;
            (main_stream)++;
        }
        break;
    }
    case '*': {
        #line 777
        main_token.kind = MAIN_TOKEN_MUL;
        (main_stream)++;
        if ((*(main_stream)) == ('=')) {
            main_token.kind = MAIN_TOKEN_MUL_ASSIGN;
            (main_stream)++;
        }
        break;
    }
    case '%': {
        #line 784
        main_token.kind = MAIN_TOKEN_MOD;
        (main_stream)++;
        if ((*(main_stream)) == ('=')) {
            main_token.kind = MAIN_TOKEN_MOD_ASSIGN;
            (main_stream)++;
        }
        break;
    }
    case '+': {
        #line 792
        main_token.kind = MAIN_TOKEN_ADD;
        (main_stream)++;
        if ((*(main_stream)) == ('=')) {
            main_token.kind = MAIN_TOKEN_ADD_ASSIGN;
            (main_stream)++;
        } else if ((*(main_stream)) == ('+')) {
            main_token.kind = MAIN_TOKEN_INC;
            (main_stream)++;
        }
        break;
    }
    case '-': {
        #line 802
        main_token.kind = MAIN_TOKEN_SUB;
        (main_stream)++;
        if ((*(main_stream)) == ('=')) {
            main_token.kind = MAIN_TOKEN_SUB_ASSIGN;
            (main_stream)++;
        } else if ((*(main_stream)) == ('-')) {
            main_token.kind = MAIN_TOKEN_DEC;
            (main_stream)++;
        }
        break;
    }
    case '&': {
        #line 812
        main_token.kind = MAIN_TOKEN_AND;
        (main_stream)++;
        if ((*(main_stream)) == ('=')) {
            main_token.kind = MAIN_TOKEN_AND_ASSIGN;
            (main_stream)++;
        } else if ((*(main_stream)) == ('&')) {
            main_token.kind = MAIN_TOKEN_AND_AND;
            (main_stream)++;
        }
        break;
    }
    case '|': {
        #line 822
        main_token.kind = MAIN_TOKEN_OR;
        (main_stream)++;
        if ((*(main_stream)) == ('=')) {
            main_token.kind = MAIN_TOKEN_OR_ASSIGN;
            (main_stream)++;
        } else if ((*(main_stream)) == ('|')) {
            main_token.kind = MAIN_TOKEN_OR_OR;
            (main_stream)++;
        }
        break;
    }
    default: {
        #line 832
        main_error(main_token.pos, "Invalid \'%c\' token, skipping", *(main_stream));
        (main_stream)++;
        goto repeat;
        break;
    }
    }
    #line 836
    main_token.end = main_stream;
}

#line 502
void main_scan_char(void) {
    assert((*(main_stream)) == ('\''));
    (main_stream)++;
    int val = 0;
    if ((*(main_stream)) == ('\'')) {
        main_error(main_token.pos, "Char literal cannot be empty");
        (main_stream)++;
    } else if ((*(main_stream)) == ('\n')) {
        main_error(main_token.pos, "Char literal cannot contain newline");
    } else if ((*(main_stream)) == ('\\')) {
        (main_stream)++;
        if ((*(main_stream)) == ('x')) {
            val = main_scan_hex_escape();
        } else {
            val = main_escape_to_char[(uchar)(*(main_stream))];
            if (((val) == (0)) && ((*(main_stream)) != ('0'))) {
                main_error(main_token.pos, "Invalid char literal escape \'\\%c\'", *(main_stream));
            }
            (main_stream)++;
        }
    } else {
        val = *(main_stream);
        (main_stream)++;
    }
    if ((*(main_stream)) != ('\'')) {
        main_error(main_token.pos, "Expected closing char quote, got \'%c\'", *(main_stream));
    } else {
        (main_stream)++;
    }
    main_token.kind = MAIN_TOKEN_INT;
    main_token.int_val = val;
    main_token.mod = MAIN_MOD_CHAR;
}

void main_scan_str(void) {
    assert((*(main_stream)) == ('\"'));
    (main_stream)++;
    char (*str) = NULL;
    if (((main_stream[0]) == ('\"')) && ((main_stream[1]) == ('\"'))) {
        main_stream += 2;
        while (*(main_stream)) {
            if ((((main_stream[0]) == ('\"')) && ((main_stream[1]) == ('\"'))) && ((main_stream[2]) == ('\"'))) {
                main_stream += 3;
                break;
            }
            if ((*(main_stream)) != ('\r')) {
                #line 549
                main_buf_push((void (**))(&(str)), (void *)(main_stream), 1);
            }
            if ((*(main_stream)) == ('\n')) {
                (main_token.pos.line)++;
            }
            (main_stream)++;
        }
        if (!(*(main_stream))) {
            main_error(main_token.pos, "Unexpected end of file within multi-line string literal");
        }
        main_token.mod = MAIN_MOD_MULTILINE;
    } else {
        while ((*(main_stream)) && ((*(main_stream)) != ('\"'))) {
            char val = *(main_stream);
            if ((val) == ('\n')) {
                main_error(main_token.pos, "String literal cannot contain newline");
                break;
            } else if ((val) == ('\\')) {
                (main_stream)++;
                if ((*(main_stream)) == ('x')) {
                    val = main_scan_hex_escape();
                } else {
                    val = main_escape_to_char[(uchar)(*(main_stream))];
                    if (((val) == (0)) && ((*(main_stream)) != ('0'))) {
                        main_error(main_token.pos, "Invalid string literal escape \'\\%c\'", *(main_stream));
                    }
                    (main_stream)++;
                }
            } else {
                (main_stream)++;
            }
            main_buf_push((void (**))(&(str)), &(val), 1);
        }
        if (*(main_stream)) {
            (main_stream)++;
        } else {
            main_error(main_token.pos, "Unexpected end of file within string literal");
        }
    }
    #line 589
    int nul = '\0';
    main_buf_push((void (**))(&(str)), &(nul), 1);
    main_token.kind = MAIN_TOKEN_STR;
    main_token.str_val = str;
}

#line 433
void main_scan_float(void) {
    char (*start) = main_stream;
    while (isdigit(*(main_stream))) {
        (main_stream)++;
    }
    if ((*(main_stream)) == ('.')) {
        (main_stream)++;
    }
    while (isdigit(*(main_stream))) {
        (main_stream)++;
    }
    if ((tolower(*(main_stream))) == ('e')) {
        (main_stream)++;
        if (((*(main_stream)) == ('+')) || ((*(main_stream)) == ('-'))) {
            (main_stream)++;
        }
        if (!(isdigit(*(main_stream)))) {
            main_error(main_token.pos, "Expected digit after float literal exponent, found \'%c\'.", *(main_stream));
        }
        while (isdigit(*(main_stream))) {
            (main_stream)++;
        }
    }
    double val = strtod(start, NULL);
    if ((val) == (HUGE_VAL)) {
        main_error(main_token.pos, "Float literal overflow");
    }
    main_token.kind = MAIN_TOKEN_FLOAT;
    main_token.float_val = val;
    if ((tolower(*(main_stream))) == ('d')) {
        main_token.suffix = MAIN_SUFFIX_D;
        (main_stream)++;
    }
}

#line 358
void main_scan_int(void) {
    int base = 10;
    char (*start_digits) = main_stream;
    if ((*(main_stream)) == ('0')) {
        (main_stream)++;
        if ((tolower(*(main_stream))) == ('x')) {
            (main_stream)++;
            main_token.mod = MAIN_MOD_HEX;
            base = 16;
            start_digits = main_stream;
        } else if ((tolower(*(main_stream))) == ('b')) {
            (main_stream)++;
            main_token.mod = MAIN_MOD_BIN;
            base = 2;
            start_digits = main_stream;
        } else if (isdigit(*(main_stream))) {
            main_token.mod = MAIN_MOD_OCT;
            base = 8;
            start_digits = main_stream;
        }
    }
    ullong val = 0;
    for (;;) {
        if ((*(main_stream)) == ('_')) {
            (main_stream)++;
            continue;
        }
        uchar digit = main_char_to_digit[(uchar)(*(main_stream))];
        if (((digit) == (0)) && ((*(main_stream)) != ('0'))) {
            break;
        }
        if ((digit) >= (base)) {
            main_error(main_token.pos, "Digit \'%c\' out of range for base %d", *(main_stream), base);
            digit = 0;
        }
        if ((val) > ((((ULLONG_MAX) - (digit))) / (base))) {
            main_error(main_token.pos, "Integer literal overflow");
            while (isdigit(*(main_stream))) {
                (main_stream)++;
            }
            val = 0;
            break;
        }
        val = ((val) * (base)) + (digit);
        (main_stream)++;
    }
    if ((main_stream) == (start_digits)) {
        main_error(main_token.pos, "Expected base %d digit, got \'%c\'", base, *(main_stream));
    }
    main_token.kind = MAIN_TOKEN_INT;
    main_token.int_val = val;
    if ((tolower(*(main_stream))) == ('u')) {
        main_token.suffix = MAIN_SUFFIX_U;
        (main_stream)++;
        if ((tolower(*(main_stream))) == ('l')) {
            main_token.suffix = MAIN_SUFFIX_UL;
            (main_stream)++;
            if ((tolower(*(main_stream))) == ('l')) {
                main_token.suffix = MAIN_SUFFIX_ULL;
                (main_stream)++;
            }
        }
    } else if ((tolower(*(main_stream))) == ('l')) {
        main_token.suffix = MAIN_SUFFIX_L;
        (main_stream)++;
        if ((tolower(*(main_stream))) == ('l')) {
            main_token.suffix = MAIN_SUFFIX_LL;
            (main_stream)++;
        }
    }
}

#line 430 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\common.ion"
char (*main_str_intern_range(char (*start), char (*end))) {
    size_t len = (end) - (start);
    ullong hash = main_hash_bytes(start, len);
    uint64_t key = (hash ? hash : 1);
    main_Intern (*intern) = main_map_get_from_uint64(&(main_interns), key);
    for (main_Intern (*it) = intern; it; it = it->next) {
        if (((it->len) == (len)) && ((strncmp(it->str, start, len)) == (0))) {
            return it->str;
        }
    }
    main_Intern (*new_intern) = main_arena_alloc(&(main_intern_arena), ((offsetof(main_Intern, str)) + (len)) + (1));
    new_intern->len = len;
    new_intern->next = intern;
    memcpy(new_intern->str, start, len);
    new_intern->str[len] = 0;
    main_map_put_from_uint64(&(main_interns), key, new_intern);
    return new_intern->str;
}

#line 89 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\lexer.ion"
bool main_is_keyword_name(char (*name)) {
    return ((main_first_keyword) <= (name)) && ((name) <= (main_last_keyword));
}

#line 316
void main_error(main_SrcPos pos, char (*fmt), ...) {
    va_list args = {0};
    va_start(args, &(fmt));
    main_verror(pos, fmt, args);
    va_end(args);
}

#line 481
int main_scan_hex_escape(void) {
    assert((*(main_stream)) == ('x'));
    (main_stream)++;
    uchar val = main_char_to_digit[(uchar)(*(main_stream))];
    if ((!(val)) && ((*(main_stream)) != ('0'))) {
        main_error(main_token.pos, "\\x needs at least 1 hex digit");
    }
    (main_stream)++;
    uchar digit = main_char_to_digit[(uchar)(*(main_stream))];
    if ((digit) || ((*(main_stream)) == ('0'))) {
        val *= 16;
        val += digit;
        if ((val) > (0xff)) {
            main_error(main_token.pos, "\\x argument out of range");
            val = 0xff;
        }
        (main_stream)++;
    }
    return val;
}

char (main_escape_to_char[256]) = {['0'] = '\0', ['\''] = '\'', ['\"'] = '\"', ['\\'] = '\\', ['n'] = '\n', ['r'] = '\r', ['t'] = '\t', ['v'] = '\v', ['b'] = '\b', ['a'] = '\a'};
#line 181 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\common.ion"
void main_buf_push(void (*(*b)), void (*elem), size_t elem_size) {
    main_buf_fit(b, (1) + (main_buf_len(*(b))), elem_size);
    memcpy(((char *)(*(b))) + ((elem_size) * ((main_buf__hdr(*(b))->len)++)), elem, elem_size);
}

uint8_t (main_char_to_digit[256]) = {['0'] = 0, ['1'] = 1, ['2'] = 2, ['3'] = 3, ['4'] = 4, ['5'] = 5, ['6'] = 6, ['7'] = 7, ['8'] = 8, ['9'] = 9, ['a'] = 10, ['A'] = 10, ['b'] = 11, ['B'] = 11, ['c'] = 12, ['C'] = 12, ['d'] = 13, ['D'] = 13, ['e'] = 14, ['E'] = 14, ['f'] = 15, ['F'] = 15};
#line 303
uint64_t main_hash_bytes(void (*ptr), size_t len) {
    uint64_t x = 0xcbf29ce484222325;
    char (*buf) = (char *)(ptr);
    for (size_t i = 0; (i) < (len); (i)++) {
        x ^= buf[i];
        x *= 0x100000001b3;
        x ^= (x) >> (32);
    }
    return x;
}

#line 391
void (*main_map_get_from_uint64(main_Map (*map), uint64_t key)) {
    return (void *)((uintptr_t)(main_map_get_uint64_from_uint64(map, key)));
}

main_Map main_interns;
#line 264
void (*main_arena_alloc(main_Arena (*arena), size_t size)) {
    if ((size) > ((size_t)(((arena->end) - (arena->ptr))))) {
        main_arena_grow(arena, size);
        assert((size) <= ((size_t)(((arena->end) - (arena->ptr)))));
    }
    char (*ptr) = arena->ptr;
    arena->ptr = main_align_up_ptr((arena->ptr) + (size), MAIN_ARENA_ALIGNMENT);
    assert((arena->ptr) <= (arena->end));
    assert((ptr) == (main_align_down_ptr(ptr, MAIN_ARENA_ALIGNMENT)));
    return ptr;
}

main_Arena main_intern_arena;
#line 395
void main_map_put_from_uint64(main_Map (*map), uint64_t key, void (*val)) {
    main_map_put_uint64_from_uint64(map, key, (uint64_t)((uintptr_t)(val)));
}

char (*main_first_keyword);
char (*main_last_keyword);
#line 312 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\lexer.ion"
void main_verror(main_SrcPos pos, char (*fmt), va_list args) {
    main_vnotice("error", pos, fmt, args);
}

#line 173 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\common.ion"
void main_buf_fit(void (*(*b)), size_t new_len, size_t elem_size) {
    if ((new_len) > (main_buf_cap(*(b)))) {
        *(b) = main_buf__grow(*(b), new_len, elem_size);
    }
}

#line 145
size_t main_buf_len(void (*b)) {
    return (b ? main_buf__hdr(b)->len : 0);
}

#line 140
main_BufHdr (*main_buf__hdr(void (*b))) {
    return (main_BufHdr *)((((char *)(b)) - (offsetof(main_BufHdr, buf))));
}

#line 321
uint64_t main_map_get_uint64_from_uint64(main_Map (*map), uint64_t key) {
    if ((map->len) == (0)) {
        return 0;
    }
    assert(main_is_pow2(map->cap));
    ullong i = (size_t)(main_hash_uint64(key));
    assert((map->len) < (map->cap));
    for (;;) {
        i &= (map->cap) - (1);
        if ((map->keys[i]) == (key)) {
            return map->vals[i];
        } else if (!(map->keys[i])) {
            return 0;
        }
        (i)++;
    }
    return 0;
}

#line 256
void main_arena_grow(main_Arena (*arena), size_t min_size) {
    ullong size = main_align_up(main_clamp_min(min_size, MAIN_ARENA_BLOCK_SIZE), MAIN_ARENA_ALIGNMENT);
    arena->ptr = main_xmalloc(size);
    assert((arena->ptr) == (main_align_down_ptr(arena->ptr, MAIN_ARENA_ALIGNMENT)));
    arena->end = (arena->ptr) + (size);
    main_buf_push((void (**))(&(arena->blocks)), &(arena->ptr), sizeof(arena->ptr));
}

#line 42
void (*main_align_up_ptr(void (*p), size_t a)) {
    return (void *)(main_align_up((uintptr_t)(p), a));
}

#line 37
void (*main_align_down_ptr(void (*p), size_t a)) {
    return (void *)(main_align_down((uintptr_t)(p), a));
}

#line 357
void main_map_put_uint64_from_uint64(main_Map (*map), uint64_t key, uint64_t val) {
    assert(key);
    if (!(val)) {
        return;
    }
    if (((2) * (map->len)) >= (map->cap)) {
        main_map_grow(map, (2) * (map->cap));
    }
    assert(((2) * (map->len)) < (map->cap));
    assert(main_is_pow2(map->cap));
    ullong i = (size_t)(main_hash_uint64(key));
    for (;;) {
        i &= (map->cap) - (1);
        if (!(map->keys[i])) {
            (map->len)++;
            map->keys[i] = key;
            map->vals[i] = val;
            return;
        } else if ((map->keys[i]) == (key)) {
            map->vals[i] = val;
            return;
        }
        (i)++;
    }
}

#line 296 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\lexer.ion"
void main_vnotice(char (*level), main_SrcPos pos, char (*fmt), va_list args) {
    if ((pos.name) == (NULL)) {
        pos = main_pos_builtin;
    }
    printf("%s(%d): %s: ", pos.name, pos.line, level);
    vprintf(fmt, args);
    printf("\n");
}

#line 150 "C:\\Users\\mlb\\Documents\\DEV\\github\\ion\\self-hosting-ion\\main\\common.ion"
size_t main_buf_cap(void (*b)) {
    return (b ? main_buf__hdr((void *)(b))->cap : 0);
}

#line 189
void (*main_buf__grow(void (*buf), size_t new_len, size_t elem_size)) {
    assert((main_buf_cap(buf)) <= ((((SIZE_MAX) - (1))) / (2)));
    ullong new_cap = main_clamp_min((2) * (main_buf_cap(buf)), main_max(new_len, 16));
    assert((new_len) <= (new_cap));
    assert((new_cap) <= ((((SIZE_MAX) - (offsetof(main_BufHdr, buf)))) / (elem_size)));
    ullong new_size = (offsetof(main_BufHdr, buf)) + ((new_cap) * (elem_size));
    main_BufHdr (*new_hdr) = {0};
    if (buf) {
        new_hdr = main_xrealloc(main_buf__hdr((void *)(buf)), new_size);
    } else {
        new_hdr = main_xmalloc(new_size);
        new_hdr->len = 0;
    }
    new_hdr->cap = new_cap;
    return new_hdr->buf;
}

#line 22
size_t main_is_pow2(size_t x) {
    return ((x) != (0)) && (((x) & (((x) - (1)))) == (0));
}

#line 286
uint64_t main_hash_uint64(uint64_t x) {
    x *= 0xff51afd7ed558ccd;
    x ^= (x) >> (32);
    return x;
}

#line 32
uintptr_t main_align_up(uintptr_t n, size_t a) {
    return main_align_down(((n) + (a)) - (1), a);
}

#line 17
size_t main_clamp_min(size_t x, size_t min) {
    return main_max(x, min);
}

#line 74
void (*main_xmalloc(size_t num_bytes)) {
    void (*ptr) = malloc(num_bytes);
    if (!(ptr)) {
        perror("xmalloc failed");
        exit(1);
    }
    return ptr;
}

#line 27
uintptr_t main_align_down(uintptr_t n, size_t a) {
    return (n) & (~(((a) - (1))));
}

#line 340
void main_map_grow(main_Map (*map), size_t new_cap) {
    new_cap = main_clamp_min(new_cap, 16);
    main_Map new_map = {.keys = main_xcalloc(new_cap, sizeof(uint64_t)), .vals = main_xmalloc((new_cap) * (sizeof(uint64_t))), .cap = new_cap};
    #line 347
    for (size_t i = 0; (i) < (map->cap); (i)++) {
        if (map->keys[i]) {
            main_map_put_uint64_from_uint64(&(new_map), map->keys[i], map->vals[i]);
        }
    }
    free((void *)(map->keys));
    free(map->vals);
    *(map) = new_map;
}

main_SrcPos main_pos_builtin = {.name = "<builtin>"};
#line 7
size_t main_max(size_t x, size_t y) {
    return ((x) >= (y) ? x : y);
}

#line 65
void (*main_xrealloc(void (*ptr), size_t num_bytes)) {
    ptr = realloc(ptr, num_bytes);
    if (!(ptr)) {
        perror("xrealloc failed");
        exit(1);
    }
    return ptr;
}

#line 56
void (*main_xcalloc(size_t num_elems, size_t elem_size)) {
    void (*ptr) = calloc(num_elems, elem_size);
    if (!(ptr)) {
        perror("xcalloc failed");
        exit(1);
    }
    return ptr;
}



#line 124 "C:\\SRC\\ion\\system_packages\\builtin\\notes.ion"

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

