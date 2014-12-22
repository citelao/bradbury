//
//  vector.h
//  bradbury
//
//  An immutable, arbitrary length vector, designed for doubles, with typical matrix operations.
//
//  Created by Ben Stolovitz on 12/14/14.
//  Copyright (c) 2014 citelao. All rights reserved.
//

#ifndef bradbury_vector_h
#define bradbury_vector_h

#include <algorithm>
#include <string>
#include <vector>
#include <initializer_list>
#include <iostream>

template<size_t D>
class Vector {
public:
    // Default constructor
    Vector() : Vector(0) {};
    
    // Default value constructor
    template <class T>
    Vector(T r) {
        _components = std::vector<double>(D, r);
    };
    
    // Copy constructors
    template <size_t E>
    Vector(Vector<E> const &vector) {
        throw std::length_error("Cannot initalize vector of size " + std::to_string(E) + " for dimension " + std::to_string(D));
    }
    Vector(Vector<D> const &vector) {
        _components = vector._components;
    };
    
    // List & vector constructors
    template <class T>
    Vector(std::initializer_list<T> components) {
        if(components.size() != D) {
            throw std::length_error("Cannot initalize vector of size " + std::to_string(components.size()) + " for dimension " + std::to_string(D));
        }
        
        _components = std::vector<double>(components.begin(), components.end());
    };
    template <class T>
    Vector(std::vector<T> components) {
        if(components.size() != D) {
            throw std::length_error("Cannot initalize vector of size " + std::to_string(components.size()) + " for dimension " + std::to_string(D));
        }
        
        _components = std::vector<double>(components.begin(), components.end());
    };
    
    // Specialized constructors for the first 4 dimensions.
    template <class T>
    Vector<2>(T x, T y) {
        _components = {static_cast<double>(x), static_cast<double>(y)};
    };
    template <class T>
    Vector<3>(T x, T y, T z) {
        _components = {static_cast<double>(x), static_cast<double>(y), static_cast<double>(z)};
    };
    template <class T>
    Vector<4>(T x, T y, T z, T t) {
        _components = {static_cast<double>(x), static_cast<double>(y), static_cast<double>(z), static_cast<double>(t)};
    };
    
    // Access operators
    const double operator[](int i) const {
        if(D <= i) {
            throw std::out_of_range("no " + std::to_string(i) + " component for dimension " + std::to_string(D));
        }
        
        return _components[i];
    };
    const double x() const {
        return (*this)[0];
    };
    const double y() const {
        if(D < 2) {
            throw std::out_of_range("no y component for dimension " + std::to_string(D));
        }
        
        return (*this)[1];
    };
    const double z() const {
        if(D < 3) {
            throw std::out_of_range("no z component for dimension " + std::to_string(D));
        }
        
        return (*this)[2];
    };
    const double t() const {
        if(D < 4) {
            throw std::out_of_range("no z component for dimension " + std::to_string(D));
        }
        
        return (*this)[3];
    }
    
//    double magnitude() const;
//    double squaredmagnitude() const;
    
    const size_t dimension() const {
        return D;
    }
    
    bool operator==(const Vector &nv) const {
        if(nv.dimension() != this->dimension())
            return false;
        
        Vector diff = nv - *this;
        
        return (diff.x() < tolerance &&
                diff.y() < tolerance &&
                diff.z() < tolerance);
    };
    bool operator!=(const Vector &nv) const {
        return !this->operator==(nv);
    };
    
    // vector-vector operations
    const Vector<D> operator+(const Vector<D> &nv) const {
        std::vector<double> results = {};
        for(int i = 0; i < _components.size(); i++) {
            results.push_back(_components[i] + nv._components[i]);
        }
        
        return Vector<D>(results);
    };
    const Vector<D> operator-(const Vector<D> &nv) const{
        std::vector<double> results = {};
        for(int i = 0; i < _components.size(); i++) {
            results.push_back(_components[i] - nv._components[i]);
        }
        
        return Vector<D>(results);
    }
    Vector<D> operator-() const {
        std::vector<double> results = {};
        for(int i = 0; i < _components.size(); i++) {
            results.push_back(-_components[i]);
        }
        
        return Vector<D>(results);
    };
    double operator*(const Vector &nv) const {
        return this->dot(nv);
    };
    double dot(const Vector &nv) const {
        return x() * nv.x() +
        y() * nv.y() +
        z() * nv.z();
    };
    Vector cross(const Vector &nv) const {
        return Vector(y() * nv.z() - z() * nv.y(),
                      - x() * nv.z() + z() * nv.x(),
                      x() * nv.y() - y() * nv.x());
    };
    
    // vector-number operations
    Vector operator*(const double &d) const  {
        return Vector(x() * d,
                      y() * d,
                      z() * d);
    };
    friend Vector operator*(const double &d, const Vector &v)  {
        return v * d;
    };
    Vector operator/(const double &d) const {
        return Vector(x() / d,
                      y() / d,
                      z() / d);
    }
;
    
protected:
    std::vector<double> _components;
    
    double tolerance = 0.000001;
    
    template <typename Array>
    void init(Array components) {
        _components = components;
    };
};

#endif // bradbury_vector_h