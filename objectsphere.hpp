#ifndef OBJECTSPHERE_H
#define OBJECTSPHERE_H

#include "objectabst.hpp"
#include "geotrans.hpp"

class ObjectSphere : public ObjectAbstract {
	public:
		ObjectSphere();
		virtual ~ObjectSphere() override;
		virtual bool TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor) override;
};

#endif
