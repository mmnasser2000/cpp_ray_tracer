#ifndef GEOTRANS_H
#define GEOTRANS_H

#include "./qbLinAlg/qbVector.h"
#include "./qbLinAlg/qbMatrix.h"
#include "ray.h"
#define FORWARDS true
#define BACKWARDS false

class GeoTransformation {
    public:
        GeoTransformation();
        ~GeoTransformation();
        
        GeoTransformation(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck);
        
        void SetTransform(const qbVector<double> &translation,
                    const qbVector<double> &rotation,
                    const qbVector<double> &scale);
                                                
        qbMatrix2<double> GetForward();
        qbMatrix2<double> GetBackward();
        
        Ray Apply(const Ray &inputRay, bool dirFlag);
        qbVector<double> Apply(const qbVector<double> &inputVector, bool dirFlag);
        
        friend GeoTransformation operator* (const GeoTransformation &lhs, const GeoTransformation &rhs);
        
        GeoTransformation operator= (const GeoTransformation &rhs);
        
        void PrintMatrix(bool dirFlag);
        
        static void PrintVector(const qbVector<double> &vector);
        
    private:
        void Print(const qbMatrix2<double> &matrix);
        
    private:
        qbMatrix2<double> m_fwdtfm {4, 4};
        qbMatrix2<double> m_bcktfm {4, 4};
};

#endif