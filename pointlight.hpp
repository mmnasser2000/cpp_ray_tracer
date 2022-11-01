#ifndef POINTLIGHT_H
#define POINTLIGHT_HS
#include "lightabst.hpp"

class PointLight : public LightAbstract {
	public:
		PointLight();		
		virtual ~PointLight() override;

        virtual bool ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                         const std::vector<std::shared_ptr<ObjectAbstract>> &objectList,
                                         const std::shared_ptr<ObjectAbstract> &currentObject,
                                         qbVector<double> &color, double &intensity) override;

};



#endif