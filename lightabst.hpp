#ifndef LIGHTABST_H
#define LIGHTABST_H

#include <memory>
#include "./qbLinAlg/qbVector.h"
#include "ray.h"
#include "objectabst.hpp"

class LightAbstract
{
	public:
		LightAbstract();		
		virtual ~LightAbstract();

        virtual bool ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                         const std::vector<std::shared_ptr<ObjectAbstract>> &objectList,
                                         const std::shared_ptr<ObjectAbstract> &currentObject,
                                         qbVector<double> &color, double &intensity);
																				
		public:
			qbVector<double> m_color {3};
			qbVector<double> m_location	{3};
            double m_intensity;
		
};



#endif