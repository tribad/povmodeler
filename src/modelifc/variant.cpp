#include <sstream>
#include "helper.h"
#include "variant.h"

tVariant::tVariant(const tVariant& in){
    type = in.type;
    dbl = in.dbl;
    ul = in.ul;
    il = in.il;
    if (type == eString) {
        ptr = strdup((const char*)(in.ptr));
    } else {
        ptr = in.ptr;
    }
}


const tVariant& tVariant::operator=(const tVariant& in){
    if (type == eString) {
        free(ptr);
    }
    type = in.type;
    dbl = in.dbl;
    ul = in.ul;
    il = in.il;
    if (type == eString) {
        ptr = strdup((const char*)(in.ptr));
    } else {
        ptr = in.ptr;
    }
    return (*this);
}

tVariant::operator unsigned long() const {
    long unsigned int retval = 0ul;

    switch (type) {
    case eDouble:
        retval = (long unsigned int)dbl;
        break;
    case eInt:
        retval = il;
        break;
    case eUnsigned:
    case eObjectRef:
        retval = ul;
        break;
    case eReference:
        retval = *((long unsigned int*)(ptr));
        break;
    case eString:
        retval = strtoul((char*)ptr, 0, 0);
        break;
    case eBoolean:
        if (ul == 0) {
            retval = 0;
        } else {
            retval = 1;
        }
        break;
    case eNull:
        retval = 0;
        break;
    }
    return retval;
}

tVariant::operator double() const {
    double retval = 0.0;

    switch (type) {
    case eDouble:
        retval = dbl;
        break;
    case eInt:
        retval = il;
        break;
    case eUnsigned:
        retval = ul;
        break;
    case eReference:
        retval = *((double*)(ptr));
        break;
    case eString:
        retval = strtod((const char*)ptr, 0);
        break;
    case eBoolean:
        if (ul == 0) {
            retval = 0.0;
        } else {
            retval = 1.0;
        }
        break;
    case eObjectRef:
    case eNull:
        retval = 0.0;
        break;
    }
    return retval;
}

tVariant::operator bool() const {
    bool retval = false;

    switch (type) {
    case eDouble:
        if (dbl == 0.0) {
            retval = false;
        } else {
            retval = true;
        }
        break;
    case eInt:
        if (il == 0) {
            retval = false;
        } else {
            retval = true;
        }
        break;
    case eUnsigned:
    case eBoolean:
        if (ul == 0) {
            retval = false;
        } else {
            retval = true;
        }
        break;
    case eReference:
        if (ptr == 0) {
            retval = false;
        } else {
            retval = true;
        }
        break;
    case eString:
        if ((helper::tolower((const char*)ptr) == "true") || ((*this) != 0ul)) {
            retval = true;
        } else {
            retval = false;
        }
        break;
    case eObjectRef:
        if ((ptr == 0) && (ul == 0)) {
            retval = false;
        }
        break;
    case eNull:
        retval = false;
        break;
    }
    return retval;
}

tVariant::operator long () const {
    long int retval = 0;

    switch (type) {
    case eDouble:
        retval = (long int)dbl;
        break;
    case eInt:
        retval = il;
        break;
    case eUnsigned:
        retval = ul;
        break;
    case eReference:
        retval = *((long int*)(ptr));
        break;
    case eString:
        retval = strtol((char*)ptr, 0, 0);
        break;
    case eBoolean:
        if (ul == 0) {
            retval = 0;
        } else {
            retval = 1;
        }
        break;
    case eObjectRef:
    case eNull:
        retval = 0;
        break;
    }
    return retval;
}

tVariant::operator std::string() const {
    std::ostringstream oss;
    std::string        retval;

    switch (type) {
    case eDouble:
        oss << dbl;
        retval = oss.str();
        break;
    case eInt:
        oss << il;
        retval = oss.str();
        break;
    case eUnsigned:
        oss << ul;
        retval = oss.str();
        break;
    case eReference:
        oss << ptr;
        retval = oss.str();
        break;
    case eString:
        if (ptr != 0) {
            retval=(char*)ptr;
        } else {
            retval.clear();
        }
        break;
    case eObjectRef:
        oss << ul << "::" << ptr;
        retval = oss.str();
        break;
    case eBoolean:
        if (ul == 0) {
            retval = "false";
        } else {
            retval = "true";
        }
        break;
    case eNull:
        retval = "";
        break;
    }
    return retval;
}

tVariant & tVariant::push_back(char c) {
    char cc[2] = {c, '\0'};
    if (type != eString) {
        (*this) = cc;
    } else {
        char* longerstring = (char*)malloc(strlen((const char*)(ptr))+2);
        strcpy(longerstring ,(const char*)ptr);
        free (ptr);
        strcat(longerstring, cc);
        ptr = longerstring;
    }

    return *this;
}

tVariant::tVariant(const char* t) {
    type = eString;
    dbl = 0;
    ul = 0;
    il = 0;
    if (t != 0) {
        ptr = malloc(std::strlen(t)+1);
#ifdef DEBUG
        memset(ptr, 0, std::strlen(t)+1);
#endif
        std::strcpy((char*)ptr, t);
    } else {
        ptr = 0;
        type = eNull;
    }
}

#if 0
tVariant::operator long double() {
    long double retval;

    switch (type) {
    case eDouble:
        retval = dbl;
        break;
    case eInt:
        retval = il;
        break;
    case eUnsigned:
        retval = ul;
        break;
    case eReference:
        retval = *((long double*)(ptr));
        break;
    case eString:
        retval = strtold(str.c_str(), 0);
        break;
    case eBoolean:
        if (ul == 0) {
            retval = 0.0;
        } else {
            retval = 1.0;
        }
        break;
    case eObjectRef:
    case eNull:
        retval = 0.0;
        break;
    }
    return retval;
}
tVariant::operator double() const {
    double retval;

    switch (type) {
    case eDouble:
        retval = dbl;
        break;
    case eInt:
        retval = il;
        break;
    case eUnsigned:
        retval = ul;
        break;
    case eReference:
        retval = *((double*)(ptr));
        break;
    case eString:
        retval = strtod(str.c_str(), 0);
        break;
    case eBoolean:
        if (ul == 0) {
            retval = 0.0;
        } else {
            retval = 1.0;
        }
        break;
    case eObjectRef:
    case eNull:
        retval = 0.0;
        break;
    }
    return retval;
}
tVariant::operator int() {
    long int retval;

    switch (type) {
    case eDouble:
        retval = (long int)dbl;
        break;
    case eInt:
        retval = il;
        break;
    case eUnsigned:
        retval = ul;
        break;
    case eReference:
        retval = *((long int*)(ptr));
        break;
    case eString:
        retval = strtol(str.c_str(), 0, 0);
        break;
    case eBoolean:
        if (ul == 0) {
            retval = 0;
        } else {
            retval = 1;
        }
        break;
    case eObjectRef:
    case eNull:
        retval = 0;
        break;
    }
    return (int)retval;
}

tVariant::operator int16_t() {
    int16_t retval;

    switch (type) {
    case eDouble:
        retval = (int16_t)dbl;
        break;
    case eInt:
        retval = (int16_t)il;
        break;
    case eUnsigned:
        retval = (int16_t)ul;
        break;
    case eReference:
        retval = *((int16_t*)(ptr));
        break;
    case eString:
        retval = (int16_t)strtol(str.c_str(), 0, 0);
        break;
    case eBoolean:
        if (ul == 0) {
            retval = 0;
        } else {
            retval = 1;
        }
        break;
    case eObjectRef:
    case eNull:
        retval = 0;
        break;
    }
    return (int)retval;
}


tVariant::operator long unsigned int() {
    long unsigned int retval;

    switch (type) {
    case eDouble:
        retval = (long unsigned int)dbl;
        break;
    case eInt:
        retval = il;
        break;
    case eObjectRef:
    case eUnsigned:
        retval = ul;
        break;
    case eReference:
        retval = *((long unsigned int*)(ptr));
        break;
    case eString:
        retval = strtoul(str.c_str(), 0, 0);
        break;
    case eBoolean:
        if (ul == 0) {
            retval = 0;
        } else {
            retval = 1;
        }
        break;
    case eNull:
        retval = 0;
        break;
    }
    return retval;
}
tVariant::operator uint16_t() {
    long unsigned int retval;

    switch (type) {
    case eDouble:
        retval = (long unsigned int)dbl;
        break;
    case eInt:
        retval = il;
        break;
    case eUnsigned:
        retval = ul;
        break;
    case eReference:
        retval = *((long unsigned int*)(ptr));
        break;
    case eString:
        retval = strtoul(str.c_str(), 0, 0);
        break;
    case eBoolean:
        if (ul == 0) {
            retval = 0;
        } else {
            retval = 1;
        }
        break;
    case eObjectRef:
    case eNull:
        retval = 0;
        break;
    }
    return (uint16_t)retval;
}

tVariant::operator uint8_t() {
    long unsigned int retval;

    switch (type) {
    case eDouble:
        retval = (long unsigned int)dbl;
        break;
    case eInt:
        retval = il;
        break;
    case eUnsigned:
        retval = ul;
        break;
    case eReference:
        retval = *((long unsigned int*)(ptr));
        break;
    case eString:
        retval = strtoul(str.c_str(), 0, 0);
        break;
    case eBoolean:
        if (ul == 0) {
            retval = 0;
        } else {
            retval = 1;
        }
        break;
    case eObjectRef:
    case eNull:
        retval = 0;
        break;
    }
    return (uint8_t)retval;
}




tagVariant::operator tObjectRef() {
    tObjectRef retval = {ul, ptr};

    return retval;
}

bool tagVariant::operator==(bool aCheck) {
    bool retval = false;

    switch (type) {
    case eDouble:
        if (dbl != 0.0) {
            retval = true;
        }
        break;
    case eInt:
        if (il != 0) {
            retval = true;
        }
        break;
    case eUnsigned:
    case eBoolean:
        if (ul != 0u) {
            retval = true;
        }
        break;
    case eReference:
        if (ptr != 0) {
            retval = true;
        }
        break;
    case eString:
        retval = !str.empty();
        break;
    case eObjectRef:
        if ((ptr != 0) || (ul != 0)) {
            retval = true;
        }
        break;
    case eNull:
        break;
    }
    return retval==aCheck;
}

bool tagVariant::operator==(uint64_t aCheck) {
    bool retval = false;

    switch (type) {
    case eDouble:
        retval = ((uint64_t)(dbl))==aCheck;
        break;
    case eInt:
        retval = ((uint64_t)(il))==aCheck;
        break;
    case eUnsigned:
    case eBoolean:
        retval = (ul == aCheck);
        break;
    case eReference:
        retval = ((uint64_t)(ptr))==aCheck;
        break;
    case eString:
        retval = (strtoul(str.c_str(), 0, 0) == aCheck);
        break;
    case eObjectRef:
        retval = (ul==aCheck);
        break;
    case eNull:
        break;
    }
    return retval;
}

bool tagVariant::operator==(int64_t aCheck) {
    bool retval = false;

    switch (type) {
    case eDouble:
        retval = ((int64_t)(dbl))==aCheck;
        break;
    case eInt:
        retval = (il==aCheck);
        break;
    case eUnsigned:
    case eBoolean:
        retval = ((int64_t)(ul) == aCheck);
        break;
    case eReference:
        retval = ((int64_t)(ptr))==aCheck;
        break;
    case eString:
        retval = (strtol(str.c_str(), 0, 0) == aCheck);
        break;
    case eObjectRef:
        retval = (((int64_t)ul) == aCheck);
        break;
    case eNull:
        break;
    }
    return retval;
}


bool tagVariant::operator!=(uint64_t aCheck) {
    bool retval = false;

    switch (type) {
    case eDouble:
        retval = ((uint64_t)(dbl))!=aCheck;
        break;
    case eInt:
        retval = ((uint64_t)(il))!=aCheck;
        break;
    case eUnsigned:
    case eBoolean:
        retval = (ul != aCheck);
        break;
    case eReference:
        retval = ((uint64_t)(ptr))!=aCheck;
        break;
    case eString:
        retval = (strtoul(str.c_str(), 0, 0) != aCheck);
        break;
    case eObjectRef:
        retval = (ul != aCheck);
        break;
    case eNull:
        break;
    }
    return retval;
}

bool tagVariant::operator!=(int64_t aCheck) {
    bool retval = false;

    switch (type) {
    case eDouble:
        retval = ((int64_t)(dbl))!=aCheck;
        break;
    case eInt:
        retval = (il!=aCheck);
        break;
    case eUnsigned:
    case eBoolean:
        retval = ((int64_t)(ul) != aCheck);
        break;
    case eReference:
        retval = ((int64_t)(ptr))!=aCheck;
        break;
    case eString:
        retval = (strtol(str.c_str(), 0, 0) != aCheck);
        break;
    case eObjectRef:
        retval = (((int64_t)ul) != aCheck);
        break;
    case eNull:
        break;
    }
    return retval;
}

bool tagVariant::operator>(uint64_t aCheck) {
    bool retval = false;

    switch (type) {
    case eDouble:
        retval = ((uint64_t)(dbl))>aCheck;
        break;
    case eInt:
        retval = ((uint64_t)(il))>aCheck;
        break;
    case eUnsigned:
    case eBoolean:
        retval = (ul > aCheck);
        break;
    case eReference:
        retval = ((uint64_t)(ptr))>aCheck;
        break;
    case eString:
        retval = (strtoul(str.c_str(), 0, 0) > aCheck);
        break;
    case eObjectRef:
        retval = (ul > aCheck);
        break;
    case eNull:
        break;
    }
    return retval;
}

bool tagVariant::operator>(int64_t aCheck) {
    bool retval = false;

    switch (type) {
    case eDouble:
        retval = ((int64_t)(dbl))>aCheck;
        break;
    case eInt:
        retval = (il>aCheck);
        break;
    case eUnsigned:
    case eBoolean:
        retval = ((int64_t)(ul) >aCheck);
        break;
    case eReference:
        retval = ((int64_t)(ptr))>aCheck;
        break;
    case eString:
        retval = (strtol(str.c_str(), 0, 0) > aCheck);
        break;
    case eObjectRef:
        retval = (((int64_t)ul) > aCheck);
        break;
    case eNull:
        break;
    }
    return retval;
}


bool tagVariant::operator<(uint64_t aCheck) {
    bool retval = false;

    switch (type) {
    case eDouble:
        retval = ((uint64_t)(dbl))<aCheck;
        break;
    case eInt:
        retval = ((uint64_t)(il))<aCheck;
        break;
    case eUnsigned:
    case eBoolean:
        retval = (ul < aCheck);
        break;
    case eReference:
        retval = ((uint64_t)(ptr))<aCheck;
        break;
    case eString:
        retval = (strtoul(str.c_str(), 0, 0) < aCheck);
        break;
    case eObjectRef:
        retval = (ul < aCheck);
        break;
    case eNull:
        break;
    }
    return retval;
}
bool tagVariant::operator<(uint64_t aCheck) const {
    bool retval = false;

    switch (type) {
    case eDouble:
        retval = ((uint64_t)(dbl))<aCheck;
        break;
    case eInt:
        retval = ((uint64_t)(il))<aCheck;
        break;
    case eUnsigned:
    case eBoolean:
        retval = (ul < aCheck);
        break;
    case eReference:
        retval = ((uint64_t)(ptr))<aCheck;
        break;
    case eString:
        retval = (strtoul(str.c_str(), 0, 0) < aCheck);
        break;
    case eObjectRef:
        retval = (ul < aCheck);
        break;
    case eNull:
        break;
    }
    return retval;
}

bool tagVariant::operator<(int64_t aCheck) {
    bool retval = false;

    switch (type) {
    case eDouble:
        retval = ((int64_t)(dbl))<aCheck;
        break;
    case eInt:
        retval = (il<aCheck);
        break;
    case eUnsigned:
    case eBoolean:
        retval = ((int64_t)(ul) <aCheck);
        break;
    case eReference:
        retval = ((int64_t)(ptr))<aCheck;
        break;
    case eString:
        retval = (strtol(str.c_str(), 0, 0) < aCheck);
        break;
    case eObjectRef:
        retval = (((int64_t)ul) < aCheck);
        break;
    case eNull:
        break;
    }
    return retval;
}



uint64_t tagVariant::operator +(uint64_t value) {
    uint64_t retval = value;

    switch (type) {
    case eDouble:
        retval = retval+dbl;
        break;
    case eInt:
        retval = retval+il;
        break;
    case eUnsigned:
    case eBoolean:
        retval = retval+ul;
        break;
    case eObjectRef:
    case eReference:
        break;
    case eString:
        retval = retval + strtol(str.c_str(), 0, 0);
        break;
    case eNull:
        retval = 0;
        break;
    }
    return retval;
}

uint64_t tagVariant::operator +(unsigned int value) {
    uint64_t retval = value;

    switch (type) {
    case eDouble:
        retval = retval+dbl;
        break;
    case eInt:
        retval = retval+il;
        break;
    case eUnsigned:
    case eBoolean:
        retval = retval+ul;
        break;
    case eObjectRef:
    case eReference:
        break;
    case eString:
        retval = retval + strtol(str.c_str(), 0, 0);
        break;
    case eNull:
        retval = 0;
        break;
    }
    return retval;
}


double tagVariant::operator +(double value) {
    double retval = value;

    switch (type) {
    case eDouble:
        retval = retval+dbl;
        break;
    case eInt:
        retval = retval+il;
        break;
    case eUnsigned:
    case eBoolean:
        retval = retval+ul;
        break;
    case eObjectRef:
    case eReference:
        break;
    case eString:
        retval = retval + strtold(str.c_str(), 0);
        break;
    case eNull:
        retval = 0;
        break;
    }
    return retval;
}

uint32_t tagVariant::operator/(uint32_t value) {
    uint32_t retval = 0;

    switch (type) {
    case eDouble:
        retval = dbl/value;
        break;
    case eInt:
        retval = il/value;
        break;
    case eUnsigned:
    case eBoolean:
        retval = ul/value;
        break;
    case eObjectRef:
    case eReference:
        break;
    case eString:
        retval = strtoul(str.c_str(), 0, 0)/value;
        break;
    case eNull:
        retval = 0;
        break;
    }
    return retval;
}

int32_t tagVariant::operator/(int32_t value) {
    int32_t retval = 0;

    switch (type) {
    case eDouble:
        retval = dbl/value;
        break;
    case eInt:
        retval = il/value;
        break;
    case eUnsigned:
    case eBoolean:
        retval = ul/value;
        break;
    case eObjectRef:
    case eReference:
        break;
    case eString:
        retval = strtol(str.c_str(), 0, 0)/value;
        break;
    case eNull:
        retval = 0;
        break;
    }
    return retval;
}


uint32_t tagVariant::operator*(uint32_t value) {
    uint32_t retval = 0;

    switch (type) {
    case eDouble:
        retval = dbl*value;
        break;
    case eInt:
        retval = il*value;
        break;
    case eUnsigned:
    case eBoolean:
        retval = ul*value;
        break;
    case eObjectRef:
    case eReference:
        break;
    case eString:
        retval = strtoul(str.c_str(), 0, 0)*value;
        break;
    case eNull:
        retval = 0;
        break;
    }
    return retval;
}

int32_t tagVariant::operator*(int32_t value) {
    int32_t retval = 0;

    switch (type) {
    case eDouble:
        retval = dbl*value;
        break;
    case eInt:
        retval = il*value;
        break;
    case eUnsigned:
    case eBoolean:
        retval = ul*value;
        break;
    case eObjectRef:
    case eReference:
        break;
    case eString:
        retval = strtol(str.c_str(), 0, 0)*value;
        break;
    case eNull:
        retval = 0;
        break;
    }
    return retval;
}

uint64_t tagVariant::operator*(uint64_t value) {
    uint64_t retval = 0;

    switch (type) {
    case eDouble:
        retval = dbl*value;
        break;
    case eInt:
        retval = il*value;
        break;
    case eUnsigned:
    case eBoolean:
        retval = ul*value;
        break;
    case eObjectRef:
    case eReference:
        break;
    case eString:
        retval = strtoull(str.c_str(), 0, 0)*value;
        break;
    case eNull:
        retval = 0;
        break;
    }
    return retval;
}

int64_t tagVariant::operator*(int64_t value) {
    int64_t retval = 0;

    switch (type) {
    case eDouble:
        retval = dbl*value;
        break;
    case eInt:
        retval = il*value;
        break;
    case eUnsigned:
    case eBoolean:
        retval = ul*value;
        break;
    case eObjectRef:
    case eReference:
        break;
    case eString:
        retval = strtoll(str.c_str(), 0, 0)*value;
        break;
    case eNull:
        retval = 0;
        break;
    }
    return retval;
}

uint32_t tagVariant::operator-(uint32_t value) {
    uint32_t retval = 0;

    switch (type) {
    case eDouble:
        retval = dbl-value;
        break;
    case eInt:
        retval = il-value;
        break;
    case eUnsigned:
    case eBoolean:
        retval = ul-value;
        break;
    case eObjectRef:
    case eReference:
        break;
    case eString:
        retval = strtoul(str.c_str(), 0, 0)-value;
        break;
    case eNull:
        retval = 0;
        break;
    }
    return retval;
}

uint64_t tagVariant::operator-(uint64_t value) const {
    uint64_t retval = 0;

    switch (type) {
    case eDouble:
        retval = dbl-value;
        break;
    case eInt:
        retval = il-value;
        break;
    case eUnsigned:
    case eBoolean:
        retval = ul-value;
        break;
    case eObjectRef:
    case eReference:
        break;
    case eString:
        retval = strtoul(str.c_str(), 0, 0)-value;
        break;
    case eNull:
        retval = 0;
        break;
    }
    return retval;
}

int32_t tagVariant::operator-(int32_t value) {
    int32_t retval = 0;

    switch (type) {
    case eDouble:
        retval = dbl-value;
        break;
    case eInt:
        retval = il-value;
        break;
    case eUnsigned:
    case eBoolean:
        retval = ul-value;
        break;
    case eObjectRef:
    case eReference:
        break;
    case eString:
        retval = strtol(str.c_str(), 0, 0)-value;
        break;
    case eNull:
        retval = 0;
        break;
    }
    return retval;
}


uint64_t tagVariant::operator|=(uint64_t value) {
    uint64_t retval = 0;

    switch (type) {
    case eDouble:
        retval = ((uint64_t)dbl)|value;
        break;
    case eInt:
        retval = il|value;
        break;
    case eUnsigned:
    case eBoolean:
        retval = ul|value;
        break;
    case eObjectRef:
    case eReference:
        break;
    case eString:
        retval = strtoull(str.c_str(), 0, 0)|value;
        break;
    case eNull:
        retval = 0;
        break;
    }
    (*this)=retval;
    return retval;
}

int64_t tagVariant::operator|=(int64_t value) {
    int64_t retval = 0;

    switch (type) {
    case eDouble:
        retval = ((int64_t)dbl)|value;
        break;
    case eInt:
        retval = il|value;
        break;
    case eUnsigned:
    case eBoolean:
        retval = ul|value;
        break;
    case eObjectRef:
    case eReference:
        break;
    case eString:
        retval = strtoll(str.c_str(), 0, 0)|value;
        break;
    case eNull:
        retval = 0;
        break;
    }
    (*this)=retval;
    return retval;
}


uint64_t tagVariant::operator&(uint64_t value) {
    uint64_t retval = 0;

    switch (type) {
    case eDouble:
        retval = ((uint64_t)dbl)&value;
        break;
    case eInt:
        retval = il&value;
        break;
    case eUnsigned:
    case eBoolean:
        retval = ul&value;
        break;
    case eObjectRef:
    case eReference:
        break;
    case eString:
        retval = strtoull(str.c_str(), 0, 0)&value;
        break;
    case eNull:
        retval = 0;
        break;
    }
    return retval;
}

int64_t tagVariant::operator&(int64_t value) {
    int64_t retval = 0;

    switch (type) {
    case eDouble:
        retval = ((int64_t)dbl)&value;
        break;
    case eInt:
        retval = il&value;
        break;
    case eUnsigned:
    case eBoolean:
        retval = ul&value;
        break;
    case eObjectRef:
    case eReference:
        break;
    case eString:
        retval = strtoll(str.c_str(), 0, 0)&value;
        break;
    case eNull:
        retval = 0;
        break;
    }
    return retval;
}
uint32_t tagVariant::operator&(uint32_t value) {
    uint32_t retval = 0;

    switch (type) {
    case eDouble:
        retval = ((uint32_t)dbl)&value;
        break;
    case eInt:
        retval = (uint32_t)(il&value);
        break;
    case eUnsigned:
    case eBoolean:
        retval = (uint32_t)(ul&value);
        break;
    case eObjectRef:
    case eReference:
        break;
    case eString:
        retval = (uint32_t)(strtoul(str.c_str(), 0, 0))&value;
        break;
    case eNull:
        retval = 0;
        break;
    }
    return retval;
}

int32_t tagVariant::operator&(int32_t value) {
    int32_t retval = 0;

    switch (type) {
    case eDouble:
        retval = ((int32_t)dbl)&value;
        break;
    case eInt:
        retval = (int32_t)(il&value);
        break;
    case eUnsigned:
    case eBoolean:
        retval = (int32_t)(ul&value);
        break;
    case eObjectRef:
    case eReference:
        break;
    case eString:
        retval = (int32_t)(strtol(str.c_str(), 0, 0))&value;
        break;
    case eNull:
        retval = 0;
        break;
    }
    return retval;
}


#endif

unsigned long operator-(unsigned long a, const tVariant& value) {
    return (-((unsigned long)(value) - a));
}

bool operator>(uint64_t a, const tVariant& value) {
    return ((unsigned long)(value) < a);
}
