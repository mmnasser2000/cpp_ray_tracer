#ifndef OBJECTPLANE_H
#define OBJECTPLANE_H

#include "objectabst.hpp"
#include "geotrans.hpp"

class ObjectPlane : public ObjectAbstract {
	public:
		ObjectPlane();
		virtual ~ObjectPlane() override;
		virtual bool TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor) override;
};

#endif
