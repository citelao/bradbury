//
//  vector.h
//  bradbury
//
//  Created by Ben Stolovitz on 12/14/14.
//  Copyright (c) 2014 citelao. All rights reserved.
//

#ifndef bradbury_vector_h
#define bradbury_vector_h

class Vector {
public:
    Vector(double r) : _x(r), _y(r), _z(r) {};
    Vector(double x, double y, double z) : _x(x), _y(y), _z(z) {};
    
    double x() const;
    double y() const;
    double z() const;
    
//    double magnitude() const;
//    double squaredmagnitude() const;
    
    bool operator==(const Vector &nv) const;
    bool operator!=(const Vector &nv) const;
    
    // vector-vector operations
    Vector operator+(const Vector &nv) const;
    Vector operator-(const Vector &nv) const;
    Vector operator-() const;
    double operator*(const Vector &nv) const;
    double dot(const Vector &nv) const;
    Vector cross(const Vector &nv) const;
    
    // vector-number operations
    Vector operator*(const double &d) const;
    friend Vector operator*(const double &d, const Vector &v);
    Vector operator/(const double &d) const;
    
protected:
    double _x;
    double _y;
    double _z;
    
    double tolerance = 0.000001;
};

#endif // bradbury_vector_h