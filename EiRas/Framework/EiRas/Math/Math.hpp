//
//  Math.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/22/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef Math_hpp
#define Math_hpp

namespace Math {

template<typename T>void swap(T& a, T& b)
{
    T tmp = b;
    b = a;
    a = tmp;
}

class int2;

class float2;
class float3;
class float4;

class rect_int
{
public:
    int top, left;
    int width, height;
    
    rect_int()
    {}
};

class int2
{
public:
    int x, y;
public: 
    int2()
    {
        x = 0;
        y = 0;
    }
};

class float2
{
public:
    float x, y;
    
    float2()
    {
        x = 0;
        y = 0;
    }
    
    float2(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
};

class float3
{
public:
    float x, y, z;
    
    float3()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    
    float3(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
};

class float4
{
public:
    float x, y, z, w;
    
    float4()
    {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }
    
    float4(float _x, float _y, float _z, float _w)
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }
};

class Matrix2X2
{
public:
    float m11,m12;
    float m21,m22;
    
    Matrix2X2()
    {
        m11 = 1;
        m12 = 0;
        
        m21 = 0;
        m22 = 1;
    }
    
    static Matrix2X2 mul(const Matrix2X2& mat1, const Matrix2X2& mat2)
    {
        Matrix2X2 mat3;
        mat3.m11 = mat1.m11 * mat2.m11 + mat1.m12 * mat2.m21;
        mat3.m12 = mat1.m11 * mat2.m12 + mat1.m12 * mat2.m22;
        
        mat3.m21 = mat1.m21 * mat2.m11 + mat1.m22 * mat2.m21;
        mat3.m22 = mat1.m21 * mat2.m12 + mat1.m22 * mat2.m22;
        
        return mat3;
    }
    
    static float2 mul(const Matrix2X2& mat, const float2& vec)
    {
        float2 bVec;
        
        bVec.x = mat.m11 * vec.x + mat.m12 * vec.y;
        bVec.y = mat.m21 * vec.x + mat.m22 * vec.y;
        
        return bVec;
    }
};

class Matrix3X3
{
    
public:
    
    float m11,m12,m13;
    float m21,m22,m23;
    float m31,m32,m33;
    
    Matrix3X3()
    {
        m11 = 1;
        m12 = 0;
        m13 = 0;
        
        m21 = 0;
        m22 = 1;
        m23 = 0;
        
        m31 = 0;
        m32 = 0;
        m33 = 1;
    }
    
    
    static Matrix3X3 mul(const Matrix3X3& mat1, const Matrix3X3& mat2)
    {
        Matrix3X3 mat3;
        mat3.m11 = mat1.m11 * mat2.m11 + mat1.m12 * mat2.m21 + mat1.m13 * mat2.m31;
        mat3.m12 = mat1.m11 * mat2.m12 + mat1.m12 * mat2.m22 + mat1.m13 * mat2.m32;
        mat3.m13 = mat1.m11 * mat2.m13 + mat1.m12 * mat2.m23 + mat1.m13 * mat2.m33;
        
        mat3.m21 = mat1.m21 * mat2.m11 + mat1.m22 * mat2.m21 + mat1.m23 * mat2.m31;
        mat3.m22 = mat1.m21 * mat2.m12 + mat1.m22 * mat2.m22 + mat1.m23 * mat2.m32;
        mat3.m23 = mat1.m21 * mat2.m13 + mat1.m22 * mat2.m23 + mat1.m23 * mat2.m33;
        
        mat3.m31 = mat1.m31 * mat2.m11 + mat1.m32 * mat2.m21 + mat1.m33 * mat2.m31;
        mat3.m32 = mat1.m31 * mat2.m12 + mat1.m32 * mat2.m22 + mat1.m33 * mat2.m32;
        mat3.m33 = mat1.m31 * mat2.m13 + mat1.m32 * mat2.m23 + mat1.m33 * mat2.m33;
        
        return mat3;
    }
    
    static float3 mul(const Matrix3X3& mat, const float3& vec)
    {
        float3 bVec;
        
        bVec.x = mat.m11 * vec.x + mat.m12 * vec.y + mat.m13 * vec.z;
        bVec.y = mat.m21 * vec.x + mat.m22 * vec.y + mat.m23 * vec.z;
        bVec.z = mat.m31 * vec.x + mat.m32 * vec.y + mat.m33 * vec.z;
        
        return bVec;
    }
};

class Matrix4X4
{
public:
    
    float m11,m12,m13,m14;
    float m21,m22,m23,m24;
    float m31,m32,m33,m34;
    float m41,m42,m43,m44;
    
    Matrix4X4()
    {
        m11 = 1;
        m12 = 0;
        m13 = 0;
        m14 = 0;
        
        m21 = 0;
        m22 = 1;
        m23 = 0;
        m24 = 0;
        
        m31 = 0;
        m32 = 0;
        m33 = 1;
        m34 = 0;
        
        m41 = 0;
        m42 = 0;
        m43 = 0;
        m44 = 1;
    }
    
    void transpose()
    {
        swap(m12, m21);
        swap(m13, m31);
        swap(m14, m41);
        
        swap(m23, m32);
        swap(m42, m24);
        swap(m43, m34);
    }
    
    static Matrix4X4 mul(const Matrix4X4& mat1, const Matrix4X4& mat2)
    {
        Matrix4X4 mat3;
        
        mat3.m11 = mat1.m11 * mat2.m11 + mat1.m12 * mat2.m21 + mat1.m13 * mat2.m31 + mat1.m14 * mat2.m41;
        mat3.m12 = mat1.m11 * mat2.m12 + mat1.m12 * mat2.m22 + mat1.m13 * mat2.m32 + mat1.m14 * mat2.m42;
        mat3.m13 = mat1.m11 * mat2.m13 + mat1.m12 * mat2.m23 + mat1.m13 * mat2.m33 + mat1.m14 * mat2.m43;
        mat3.m14 = mat1.m11 * mat2.m14 + mat1.m12 * mat2.m24 + mat1.m13 * mat2.m34 + mat1.m14 * mat2.m44;
        
        mat3.m21 = mat1.m21 * mat2.m11 + mat1.m22 * mat2.m21 + mat1.m23 * mat2.m31 + mat1.m24 * mat2.m41;
        mat3.m22 = mat1.m21 * mat2.m12 + mat1.m22 * mat2.m22 + mat1.m23 * mat2.m32 + mat1.m24 * mat2.m42;
        mat3.m23 = mat1.m21 * mat2.m13 + mat1.m22 * mat2.m23 + mat1.m23 * mat2.m33 + mat1.m24 * mat2.m43;
        mat3.m24 = mat1.m21 * mat2.m14 + mat1.m22 * mat2.m24 + mat1.m23 * mat2.m34 + mat1.m24 * mat2.m44;
        
        
        mat3.m31 = mat1.m31 * mat2.m11 + mat1.m32 * mat2.m21 + mat1.m33 * mat2.m31 + mat1.m34 * mat2.m41;
        mat3.m32 = mat1.m31 * mat2.m12 + mat1.m32 * mat2.m22 + mat1.m33 * mat2.m32 + mat1.m34 * mat2.m42;
        mat3.m33 = mat1.m31 * mat2.m13 + mat1.m32 * mat2.m23 + mat1.m33 * mat2.m33 + mat1.m34 * mat2.m43;
        mat3.m34 = mat1.m31 * mat2.m14 + mat1.m32 * mat2.m24 + mat1.m33 * mat2.m34 + mat1.m34 * mat2.m44;
        
        mat3.m41 = mat1.m41 * mat2.m11 + mat1.m42 * mat2.m21 + mat1.m43 * mat2.m31 + mat1.m44 * mat2.m41;
        mat3.m42 = mat1.m41 * mat2.m12 + mat1.m42 * mat2.m22 + mat1.m43 * mat2.m32 + mat1.m44 * mat2.m42;
        mat3.m43 = mat1.m41 * mat2.m13 + mat1.m42 * mat2.m23 + mat1.m43 * mat2.m33 + mat1.m44 * mat2.m43;
        mat3.m44 = mat1.m41 * mat2.m14 + mat1.m42 * mat2.m24 + mat1.m43 * mat2.m34 + mat1.m44 * mat2.m44;
        
        return mat3;
    }
    
    static float4 mul(const Matrix4X4& mat, const float4& vec)
    {
        float4 bVec;
        
        bVec.x = mat.m11 * vec.x + mat.m12 * vec.y + mat.m13 * vec.z + mat.m14 * vec.w;
        bVec.y = mat.m21 * vec.x + mat.m22 * vec.y + mat.m23 * vec.z + mat.m24 * vec.w;
        bVec.z = mat.m31 * vec.x + mat.m32 * vec.y + mat.m33 * vec.z + mat.m34 * vec.w;
        bVec.w = mat.m41 * vec.x + mat.m42 * vec.y + mat.m43 * vec.z + mat.m44 * vec.w;
        
        return bVec;
    }
};

}

#endif /* Math_hpp */
