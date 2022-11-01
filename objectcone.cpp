#include "objectcone.hpp"
#include <cmath>

ObjectCone::ObjectCone() {

}

ObjectCone::~ObjectCone() {

}

bool ObjectCone::TestIntersection( const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor) {

	Ray backRay = m_transformation_matrix.Apply(castRay, BACKWARDS);
	
	qbVector<double> v = backRay.m_lab;
	v.Normalize();
	
	qbVector<double> p = backRay.m_point1;
	
	double a = std::pow(v.GetElement(0), 2.0) + std::pow(v.GetElement(1), 2.0) - std::pow(v.GetElement(2), 2.0);
	double b = 2 * (p.GetElement(0)*v.GetElement(0) + p.GetElement(1)*v.GetElement(1) - p.GetElement(2)*v.GetElement(2));
	double c = std::pow(p.GetElement(0), 2.0) + std::pow(p.GetElement(1), 2.0) - std::pow(p.GetElement(2), 2.0);
	
	double numSQRT = sqrtf(std::pow(b, 2.0) - 4 * a * c);
	
	std::array<qbVector<double>, 3> poi;
	std::array<double, 3> t;
	bool t1_valid, t2_valid, t3_valid;
	if (numSQRT > 0.0) {
		t.at(0) = (-b + numSQRT) / (2 * a);
		t.at(1) = (-b - numSQRT) / (2 * a);
		
		poi.at(0) = backRay.m_point1 + (v * t[0]);
		poi.at(1) = backRay.m_point1 + (v * t[1]);
		
		if ((t.at(0) > 0.0) && (poi.at(0).GetElement(2) > 0.0) && (poi.at(0).GetElement(2) < 1.0)) {
			t1_valid = true;
		} else {
			t1_valid = false;
			t.at(0) = 100e6;
		}

		if ((t.at(1) > 0.0) && (poi.at(1).GetElement(2) > 0.0) && (poi.at(1).GetElement(2) < 1.0)) {
			t2_valid = true;
		} else {
			t2_valid = false;
			t.at(1) = 100e6;
		}
	} else {
		t1_valid = false;
		t2_valid = false;
		t.at(0) = 100e6;
		t.at(1) = 100e6;
	}
	
	if (close(v.GetElement(2), 0.0)) {
		t3_valid = false;
		t.at(2) = 100e6;
	} else {	
		t.at(2) = (backRay.m_point1.GetElement(2) - 1.0) / -v.GetElement(2);
		poi.at(2) = backRay.m_point1 + t.at(2) * v;
		
		if ((t.at(2) > 0.0) && (sqrtf(std::pow(poi.at(2).GetElement(0), 2.0) + std::pow(poi.at(2).GetElement(1), 2.0)) < 1.0)) {
			t3_valid = true;
		} else {
			t3_valid = false;
			t.at(2) = 100e6;
		}						
	}
	
	if ((!t1_valid) && (!t2_valid) && (!t3_valid)) {
		return false;	
	}
	
	int minIndex = 0;
	double minValue = 10e6;
	for (int i=0; i<3; ++i) {
		if (t.at(i) < minValue) {
			minValue = t.at(i);
			minIndex = i;
		}
	}
	
	qbVector<double> validPOI = poi.at(minIndex);
	if (minIndex < 2) {		
		intPoint = m_transformation_matrix.Apply(validPOI, FORWARDS);		
			
		qbVector<double> orgNormal {3};
		qbVector<double> newNormal {3};
		qbVector<double> localOrigin {std::vector<double> {0.0, 0.0, 0.0}};
		qbVector<double> globalOrigin = m_transformation_matrix.Apply(localOrigin, FORWARDS);		
		double tX = validPOI.GetElement(0);
		double tY = validPOI.GetElement(1);
		double tZ = -sqrtf(pow(tX, 2.0) + pow(tY, 2.0));
		orgNormal.SetElement(0, tX);
		orgNormal.SetElement(1, tY);
		orgNormal.SetElement(2, tZ);
		newNormal = m_transformation_matrix.Apply(orgNormal, FORWARDS) - globalOrigin;
		newNormal.Normalize();		
		localNormal = newNormal;
			
		localColor = m_baseColor;
	
		return true;
	} else {
		if (!close(v.GetElement(2), 0.0)) {
			if (sqrtf(std::pow(validPOI.GetElement(0), 2.0) + std::pow(validPOI.GetElement(1), 2.0)) < 1.0) {
				intPoint = m_transformation_matrix.Apply(validPOI, FORWARDS);				
				
				qbVector<double> localOrigin {std::vector<double> {0.0, 0.0, 0.0}};
				qbVector<double> normalVector {std::vector<double> {0.0, 0.0, 1.0}};
				qbVector<double> globalOrigin = m_transformation_matrix.Apply(localOrigin, FORWARDS);
				localNormal = m_transformation_matrix.Apply(normalVector, FORWARDS) - globalOrigin;
				localNormal.Normalize();
						
				localColor = m_baseColor;
						
				return true;				
			} else {
				return false;
			}			
		} else {
			return false;
		}
		
	}		
	
	return false;
}
