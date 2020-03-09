#ifndef VARIANT_INC
#define VARIANT_INC

#include <stdint.h>
#include <string>
#include <cstring>
#include <malloc.h>

typedef enum enumVariant {
    eDouble,
    eInt,
    eUnsigned,
    eReference,
    eObjectRef,
    eString,
    eBoolean,
    eNull
} eVariant;

struct tObjectRef {
    tObjectRef() {id = 0; ptr = 0;}
    tObjectRef(uint64_t aId, void* aPtr) {id = aId; ptr = aPtr;}
    uint64_t id;
    void*    ptr;
};

class tVariant {
public:
    tVariant() {type = eNull; dbl = 0.0; ul = 0; il = 0; ptr = 0;}
    tVariant(const tVariant & in);
    tVariant(double d) {type =eDouble; dbl = d; ul = 0; il = 0; ptr = 0;}
    tVariant(long double d) {type =eDouble; dbl = d; ul = 0; il = 0; ptr = 0;}
    tVariant(std::string s) : tVariant(s.c_str()) {}
    tVariant(const char* t);
    tVariant(unsigned long u) {type =eUnsigned; dbl = 0; ul = u; il = 0; ptr = 0;}
    tVariant(unsigned int u) {type =eUnsigned; dbl = 0; ul = u; il = 0; ptr = 0;}
    tVariant(int i) {type =eInt; dbl = 0; ul = 0; il = i; ptr = 0;}
    tVariant(long i) {type =eInt; dbl = 0; ul = 0; il = i; ptr = 0;}
    tVariant(long long i) {type =eInt; dbl = 0; ul = 0; il = i; ptr = 0;}
    tVariant(bool b) {type =eBoolean; dbl = 0; ul = b; il = 0; ptr = 0;}
//    tagVariant(int32_t i) {type =eInt; dbl = 0; ul = 0; il = i; ptr = 0;}
    tVariant(const tObjectRef & ref) {type = eObjectRef; dbl = 0; ul = ref.id; il = 0; ptr = ref.ptr;}
    ~tVariant() {if ((type == eString) && (ptr != 0)) {free(ptr);ptr=0;}}
    eVariant    type;
    void clear() {
        if ((type == eString) && (ptr != 0)) {
            free(ptr);
            ptr=0;
        }
        type = eNull;
    }
    long double dbl;
    uint64_t    ul;
    int64_t     il;
    void*       ptr;

    operator unsigned long() const ;
    operator unsigned char() const {return ((unsigned long) (*this));}
    operator uint16_t() const {return ((unsigned long) (*this));}

    operator double () const;
    operator long double () const {return ((double)(*this));}

    operator long () const;
    operator int () const { return ((long)(*this));}
    operator int16_t () const { return ((long)(*this));}

    operator bool() const;
    operator std::string() const;

    operator tObjectRef() const { return tObjectRef {ul, ptr};}

    const tVariant& operator = (const tVariant& in);

    bool operator==(bool value) const {return ((bool)(*this))==value;}
    bool operator==(double value) const {return ((double)(*this))==value;}
    bool operator==(long value) const {return ((long)(*this))==value;}
    bool operator==(unsigned long value) const {return ((unsigned long)(*this))==value;}
    bool operator==(const std::string& thingie) const {return (std::string)(*this) == thingie;}

    bool operator!=(long unsigned int value) const {return (long unsigned int)(*this) != value;}
    bool operator!=(long value) const {return (long)(*this) != value;}

    unsigned int operator& (unsigned int value) {return (long unsigned)(*this) & value;}
    unsigned long operator|= (unsigned int value) {return (*this) = ((long unsigned)(*this) | value);}

    tVariant & push_back(char c);
    bool empty() {return ((std::string)(*this)).empty();}

    int operator+(int value) {return ((long)(*this))+value;}
    unsigned long operator+(unsigned long value) {return ((unsigned long)(*this))+value;}
    int operator-(int value) {return ((long)(*this))-value;}
    unsigned long operator-(const unsigned long  value) {return ((unsigned long)(*this))-value;}
    int operator/(int value) {return ((long)(*this))/value;}
    int operator*(int value) {return ((long)(*this))*value;}
    unsigned long operator*(unsigned long value) {return ((unsigned long)(*this))*value;}

    //    std::string str;
#if 0
    tagVariant & operator=(double value) {dbl = value;type=eDouble;return *this;}
    tagVariant & operator=(long double value) {dbl = value;type=eDouble;return *this;}
    tagVariant & operator=(int64_t value) {il = value;type=eInt;return *this;}
    tagVariant & operator=(int value) {il = value;type=eInt;return *this;}
    tagVariant & operator=(long long int value) {il = value;type=eInt;return *this;}
    tagVariant & operator=(uint64_t value) {
        ul = value;
        type=eUnsigned;
        return *this;
    }
    tagVariant & operator=(tObjectRef& aRef) {ul = aRef.id; ptr = aRef.ptr; type=eObjectRef; return *this;}
    tagVariant & operator=(const char* value) {str=value; type=eString; return *this;}
    tagVariant & operator=(const std::string& value) {str=value; type=eString; return *this;}
    tagVariant & operator=(bool value) {ul = value;type=eBoolean;return *this;}
    //
    //  Comparision operators.
    bool operator!=(uint64_t value);
    bool operator!=(int64_t value);
    bool operator>(uint64_t value);
    bool operator>(int64_t value);
    bool operator<(uint64_t value);
    bool operator<(uint64_t value) const;
    bool operator<(int64_t value);
    //
    //  Cast operators
    operator std::string() const;
    //operator const char* ();
    operator long double();
    operator double();
    operator double() const;
    operator long int();
    operator long unsigned int() const;
    operator uint16_t();
    operator uint8_t();
    operator int();
//    operator int16_t();
    //
    //  adding operators
    uint64_t operator +(uint64_t value);
    uint64_t operator +(unsigned int value);
    double operator+ (double value);
    //
    //  sub operators
    int32_t operator-(int32_t);
    uint32_t operator-(uint32_t);
    //
    //  Division operators
    int32_t operator/(int32_t);
    uint32_t operator/(uint32_t);
    //
    //  Multiplication operators
    int32_t operator*(int32_t);
    uint32_t operator*(uint32_t);
    int64_t operator*(int64_t);
    uint64_t operator*(uint64_t);
    //
    //  Logical operators
    uint64_t operator |=(uint64_t value);
    int64_t operator |=(int64_t value);

    uint64_t operator&(uint64_t value);
    int64_t operator&(int64_t value);

    uint32_t operator&(uint32_t value);
    int32_t operator&(int32_t value);

#endif
};
uint64_t operator-(uint64_t a, const tVariant& value);
bool operator>(uint64_t a, const tVariant& value);
#endif
