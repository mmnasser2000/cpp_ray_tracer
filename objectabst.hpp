#ifndef OBJECTAbstract_H
#define OBJECTAbstract_H

#include "./qbLinAlg/qbVector.h"
#include "ray.h"
#include "geotrans.hpp"


class ObjectAbstract {
	public:
		ObjectAbstract();
		virtual ~ObjectAbstract();
		
		virtual bool TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor);
		
		bool close(const double f1, const double f2);
		void SetTransformMatrix(const GeoTransformation &transformation);
		
	public:
		qbVector<double> m_baseColor {3};
		GeoTransformation m_transformation_matrix;
};

#endif
