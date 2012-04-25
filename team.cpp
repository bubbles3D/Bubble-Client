#include "team.h"

Team::Team()
{
}

Team::Team(QVariantMap map)
{
    cR = map["cR"].toInt();
    cG = map["cG"].toInt();
    cB = map["cB"].toInt();
    name = map["name"].toString();;
    num = map["num"].toInt();
    pts = map["pts"].toInt();
}


void Team::getColor(float* r, float* g, float* b)
{
    *r = this->cR / 255.0;
    *g = this->cG / 255.0;
    *b = this->cB / 255.0;
}
