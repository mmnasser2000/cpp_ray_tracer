#ifndef CONE_H
#define CONE_H

#include "objectabst.hpp"
#include "geotrans.hpp"
#include <array>

class ObjectCone : public ObjectAbstract {
	public:
		ObjectCone();
		virtual ~ObjectCone() override;
		
		virtual bool TestIntersection(	const Ray &castRay, qbVector<double> &intPoint,
										qbVector<double> &localNormal, qbVector<double> &localColor) override;			
};


#endif
