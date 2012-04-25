#ifndef TEAM_H
#define TEAM_H

#include <QString>
#include <QVariant>

class Team
{
public:
    Team();
    Team(QVariantMap map);

    void getColor(float* r, float* g, float* b);
    void update(QVariantMap map);

    int cR, cG, cB;
    QString name;
    int num;
    int pts;
};

#endif // TEAM_H
