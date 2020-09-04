#ifndef Common_Macro_Hpp
#define Common_Macro_Hpp

#define RELEASE_ARRAY(o) \
if(o != 0)\
{\
    delete [] o; \
    o = 0;\
}\


#define RELEASE_OBJ(o) \
if (o != 0)\
{\
    delete o; \
    o = 0;\
}\

#define COPY_VECTOR_DATA(type, src, dst)\
if(src.size() > 0)\
{\
dst = new type[src.size() * sizeof(type)];\
memcpy(dst, &src[0], src.size() * sizeof(type));\
}

#endif