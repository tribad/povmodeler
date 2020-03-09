#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "json.h"

static int indentation=0;

static std::ostream & dump(std::ostream &output, tJSONArray *array);

inline static void parser_init(tJSON *p) {
    p->state=0;
    p->parent=0;
}

tJSON* parse(std::istream &infile) {
    tJSON* retval = 0;
    char   c;

    while (infile.good()) {
        infile >> c;

        retval=(tJSON*)parse(retval, (uint8_t*)(&c), 1);
        if ((retval != nullptr) && (completed(retval))) {
            break;
        }
    }
    while ((retval != nullptr) && (retval->parent != nullptr)) {
        retval = retval->parent;
    }
    return (retval);
}

tJSON *parse(tJSON *prev, uint8_t*data, size_t size) {
    size_t      index=0;
    bool        again=false;
    tJSON       *root;
    tJSONValue  *jnewvalue;
    tJSONObject *jnewobject;
    tJSONArray  *jnewarray;
    uint8_t     c;

    if (prev==0) {
        root=prev=(tJSON*)(new tJSONObject);
        root->type=eObject;
        parser_init(prev);
    } else {
        root=prev;
        while (root->parent!=0) {
            root=root->parent;
        }
    }

    for (index=0; index<size;) {
        c=data[index];
        switch (root->state) {
        case 0:    // init
            if (c == '{') {
                root->state=1; // we expect a namestart
            }
            break;
        case 1:   // name start
            if (c == '"') {
                root->state=2; // we now take the name
                root->name.clear();
            } else if (c=='}') {
                root->state=-1;
            }
            break;
        case 2:    //   the name literal
            if (c !='"') {
                root->name.push_back((char)(c));
            } else {
                root->state = 3; // Wait colon
            }
            break;
        case 3:    //  Wait colon
            if (c == ':') {
                root->state = 4;  //  Wait next non blank. This tells us what type of object we have to expect.
            }
            break;
        case 4:
            if (!isblank(c)) {
                if (c=='"') {
                    jnewvalue = new tJSONValue;
                    jnewvalue->base.type=eValue;
                    jnewvalue->base.name=root->name;
                    root->name.clear();
                    jnewvalue->base.parent=prev;
                    prev=(tJSON*)jnewvalue;
#if 0
                    stringvar=new tVariant;
                    stringvar->type=eString;
                    jnewvalue->value=(tVariant*)stringvar;
#endif
                    root->state = 199;               //  Wait for end of string

                } else if (toupper(c)=='T') {
                    jnewvalue = new tJSONValue;
                    jnewvalue->base.type=eValue;
                    jnewvalue->base.name=root->name;
                    root->name.clear();
                    jnewvalue->base.parent=prev;
                    prev=(tJSON*)jnewvalue;
#if 0
                    booleanvar=new tBooleanVar;
                    booleanvar->type=eBoolean;
                    booleanvar->value=true;
                    jnewvalue->value=(tVariant*)booleanvar;
#else
                    jnewvalue->value = true;
#endif
                    root->state = 200;               //  Wait for end of value
                } else if (toupper(c)=='F') {
                    jnewvalue = new tJSONValue;
                    jnewvalue->base.type=eValue;
                    jnewvalue->base.name=root->name;
                    root->name.clear();
                    jnewvalue->base.parent=prev;
                    prev=(tJSON*)jnewvalue;
#if 0
                    booleanvar=new tBooleanVar;
                    booleanvar->type=eBoolean;
                    booleanvar->value=false;
                    jnewvalue->value=(tVariant*)booleanvar;
#else
                    jnewvalue->value = false;
#endif
                    root->state = 200;               //  Wait for end of value
                } else if (toupper(c)=='N') {
                    jnewvalue = new tJSONValue;
                    jnewvalue->base.type=eValue;
                    jnewvalue->base.name=root->name;
                    root->name.clear();
                    jnewvalue->base.parent=prev;
                    prev=(tJSON*)jnewvalue;
#if 0
                    nullvar=new tVariant;
                    nullvar->type=eNull;
                    jnewvalue->value=(tVariant*)nullvar;
#endif
                    root->state = 200;               //  Wait for end of value
                } else if (c=='{') {
                    jnewobject = new tJSONObject;
                    jnewobject->base.type=eObject;
                    jnewobject->base.name=root->name;
                    root->name.clear();
                    jnewobject->base.parent=prev;
                    prev=(tJSON*)jnewobject;
                    root->state=1;
                } else if (c=='[') {                   //  Process array
                    jnewarray = new tJSONArray;
                    jnewarray->base.type=eArray;
                    jnewarray->base.name=root->name;
                    root->name.clear();
                    jnewarray->base.parent=prev;
                    prev=(tJSON*)jnewarray;
                } else if (isdigit(c) || (c=='+') || (c=='-')) {
                    jnewvalue = new tJSONValue;
                    jnewvalue->base.type=eValue;
                    jnewvalue->base.name=root->name;
                    root->name.clear();
                    jnewvalue->base.parent=prev;
                    prev=(tJSON*)jnewvalue;
                    root->name.push_back(c);
                    jnewvalue->value=0;
                    root->state = 197;                        //  Process numeric
                } else if (c==']') {
                    root->state = 200;
                }
            }
            break;
        case 197:   //  processing numeric
            if ((c==',') || (c=='}')) {
                tJSONValue* pv=(tJSONValue*)prev;

                if ((*pv) == eNull) {
#if 0
                    intvar=new tIntVar;
                    intvar->type=eInt;
                    intvar->value=strtoll(root->name.c_str(), 0, 10);
                    ((tJSONValue*)prev)->value=(tVariant*)intvar;
#else
                    pv->value = strtoll(root->name.c_str(), 0, 10);
#endif
                } else if ((*pv)==eInt) {
                    pv->value = strtoll(root->name.c_str(), 0, 10);
                } else {
                    pv->value = strtold(root->name.c_str(), 0);
                }
                again=true;
                root->state=200;
                root->name.clear();
            } else if (((toupper(c)=='E') || (c=='.')) && (*((tJSONValue*)prev) == eNull)) {
#if 0
                doublevar=new tDoubleVar;
                doublevar->type=eDouble;
                ((tJSONValue*)prev)->value=(tVariant*)doublevar;
#endif
                root->name.push_back(c);
            } else if ((c==' ') && (*((tJSONValue*)prev) == eNull)) {
#if 0
                intvar=new tIntVar;
                intvar->type=eInt;
                ((tJSONValue*)prev)->value=(tVariant*)intvar;
#endif
            } else {
                root->name.push_back(c);
            }
            break;
        case 198:   // in escape sequence
            //
            // The default follow-up state is the 199.
            // can be changed for special formats.
            root->state = 199;
            if (c=='\\') {
                ((tJSONValue*)prev)->value.push_back('\\');
            } else {
                if (c=='n') {
                    ((tJSONValue*)prev)->value.push_back('\n');
                } else if (c=='t') {
                    ((tJSONValue*)prev)->value.push_back('\t');
                } else if (c=='"') {
                    ((tJSONValue*)prev)->value.push_back('"');
                } else if (c=='r') {
                    ((tJSONValue*)prev)->value.push_back('\r');
                } else if (c=='b') {
                    ((tJSONValue*)prev)->value.push_back('\b');
                } else if (c=='0') {
                    root->name.push_back(c);
                    root->state = 197;           //  octal value
                } else if (c=='x') {
                    root->state = 196;           // hex value
                } else {
                }
            }
            break;
        case 199:                   //  Wait for end of string
            if (c=='\\') {
                root->state = 198;
            } else if (c=='"') {
                root->state = 200;  //  Wait end of value
            } else {
                ((tJSONValue*)prev)->value.push_back(c);
            }
            break;
        case 200:
            if ((c==',') || (c=='}') || (c==']')) {
                if (prev->parent!=0) {
                    if (prev->parent->type==eObject) {
                        ((tJSONObject*)prev->parent)->values.insert(std::pair<std::string, tJSON*>(prev->name, prev));
                        if (c==',') {
                            root->state = 1;      //  Continue with a name
                        } else if (c=='}') {
#if 0
                            prev=prev->parent;
                            if ((prev->parent != 0) && (prev->parent->type==eObject)) {
                                ((tJSONObject*)prev->parent)->values.insert(std::pair<std::string, tJSON*>(prev->name, prev));
                                root->state = 1;      //  Continue with a name
                            } else if ((prev->parent != 0) && (prev->parent->type==eArray)) {
                                ((tJSONArray*)prev->parent)->values.push_back(prev);
                                root->state = 4;      //  Continue with a value;
                            } else if (prev->parent == 0) {
                                root->state = -1;
                            }
#endif
                        }
                    } else if (prev->parent->type==eArray) {
                        ((tJSONArray*)prev->parent)->values.push_back(prev);
                        if (c==',') {
                            root->state = 4;      //  Continue with a value;
                        } else {

                        }
                    }
                    if (prev->parent!=0) {
                        prev=prev->parent;
                        //
                        //  We are now on the root object.
                        if (prev->parent == 0) {
                            //
                            // If it was the closing brace on the root object it is completed.
                            if (c=='}') {
                                root->state=-1;
                            }
                        }
                    }
                } else {
                    if (c=='}') {
                        root->state=-1;
                    }
                }
            }
            break;
        default:
            break;
        }
        if (again) {
            again=false;
        } else {
            index++;
        }
    }
    return (prev);
}

static std::ostream & dump(std::ostream &output, tVariant *value) {
    switch (value->type) {
    case eDouble:
        output << (long double)(*value);
        break;
    case eInt:
        output << (long int)(*value);
        break;
    case eString:
        output << "\"" << (std::string)(*value) << "\"";
        break;
    case eBoolean:
        if ((bool)(*value) == true) {
            output << "true";
        } else {
            output << "false";
        }
        break;
    case eNull:
        output << "null";
        break;
    default:
        break;
    }

    return (output);
}
static std::ostream & dump(std::ostream &output, tJSONObject *obj) {
    std::map<std::string, tJSON*>::iterator i;
    bool delimiter=false;

    if (obj->base.name.size() > 0) {
        output << obj->base.name << " {\n";
    } else {
        output << "{\n";
    }
    indentation+=4;
    for (i=obj->values.begin(); i!=obj->values.end(); ++i) {
        if (delimiter) {
            output << ",\n";
        } else {
            delimiter=true;
        }
        for (int x=0;x<indentation;x++) output << ' ';
        output << "\"" << i->first << "\" : ";
        switch(i->second->type) {
        case eValue:
            dump(output, &((tJSONValue*)(i->second))->value);
            break;
        case eArray:
            dump(output, ((tJSONArray*)(i->second)));
            break;
        case eObject:
            dump(output, (tJSONObject*)i->second);
            delimiter=false;
            break;
        default:
            break;
        }
    }
    indentation-=4;
    output << "\n";
    for (int x=0;x<indentation;x++) output << ' ';
    output << "}\n";
    return (output);
}


static std::ostream & dump(std::ostream &output, tJSONArray *array) {
    std::vector<tJSON*>::iterator i;
    output << "[ ";

    for (i=array->values.begin(); i!=array->values.end(); ++i) {
        if (i!=array->values.begin()) {
            output << ", ";
        }
        switch ((*i)->type) {
        case eValue:
            dump(output, &((tJSONValue*)(*i))->value);
            break;
        case eArray:
            dump(output, ((tJSONArray*)(*i)));
            break;
        case eObject:
            dump(output, (tJSONObject*)(*i));
            break;
        default:
            break;
        }
    }
    output << " ]";
    return (output);
}



std::ostream & dump(std::ostream & output, tJSON *root) {
    indentation=0;
//    while (root->parent != 0) root=root->parent;
    return (dump(output, (tJSONObject*)root));
}


tJSON *find(tJSON *root, std::string path) {
    size_t end;
    std::map<std::string, tJSON*>::iterator i;

    if (root->type==eObject) {
        end=path.find_first_of('/');
        tJSONObject *o=(tJSONObject*)(root);
        std::string s=path.substr(0, end);
        i=o->values.find(s);
        if (i!=o->values.end()) {
            return (i->second);
        } else {
        }
    } else if (root->type==eArray) {
        end=path.find_first_of(':');
    } else {
        return (root);
    }
    return (0);
}

int to_int(tJSON *j) {
    return ((tJSONValue*)j)->value;
}

unsigned long to_unsigned_long(tJSON *j) {
    return ((((tJSONValue*)j)->value));
}


long to_long(tJSON *j) {
    return ((long)(((tJSONValue*)j)->value));
}

int64_t to_int64_t(tJSON *j) {
    return ((long)(((tJSONValue*)j)->value));
}

uint8_t to_uint8_t(tJSON *j) {
    uint64_t retval = (((tJSONValue*)j)->value);

    return (uint8_t)retval;
}

uint16_t to_uint16_t(tJSON *j) {
    return (((tJSONValue*)j)->value);
}

uint64_t to_uint64_t(tJSON *j) {
    return (((tJSONValue*)j)->value);
}

int16_t to_int16_t(tJSON *j) {
    return (((tJSONValue*)j)->value);
}

bool to_bool(tJSON* j) {
    return ((bool)(((tJSONValue*)j)->value));
}

std::string to_string(tJSON *j) {
    return ((std::string)(((tJSONValue*)j)->value));
}

double to_double (tJSON* j) {
    return ((double)(((tJSONValue*)j)->value));
}

bool completed(tJSON *root) {
    if (root != 0) {
        return (root->state == -1);
    }
    return (false);
}

#ifdef TEST
#include <stdio.h>

FILE *infile=stdin;

int main(int argc, char **argv) {
    uint8_t buffer[512];
    size_t dataread;
    tJSON *pp=0;

    if (argc > 1) {
        infile=fopen(argv[1], "r+t");
    }
    if (infile != 0) {
        while (!feof(infile)) {
            dataread=fread(buffer, 1, 512, infile);
            pp=parse(pp, buffer, dataread);
        }
        dump(std::cout, pp);
    } else {
    }
    return (0);
}

#endif
