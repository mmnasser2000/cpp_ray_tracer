#include "lightabst.hpp"

LightAbstract::LightAbstract() {

}

LightAbstract::~LightAbstract() {

}

bool LightAbstract::ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                         const std::vector<std::shared_ptr<ObjectAbstract>> &objectList,
                                         const std::shared_ptr<ObjectAbstract> &currentObject,
                                         qbVector<double> &color, double &intensity) {
	return false;
}