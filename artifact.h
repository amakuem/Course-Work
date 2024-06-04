#ifndef ARTIFACT_H
#define ARTIFACT_H

#include <QWidget>
#include "artifactpixmapitem.h"

class Artifact:public QWidget
{
public:
    Artifact(QString Name, QString PathToArtifactIcon, double HealthBuff, double DamageBuff, int Cost);
    Artifact();
    QString getNameOfArtifact();
    QString getStatsOfArtifact();
    QString getPathToArtifactIcon();
    double makeDamageBuff(int damage);
    int makeHealthBuff(int health);

    double getCost();
    ArtifactPixmapItem *getArtifactIcon();
    double getDamageBuff();
private:
    QString name;
    QString stats;
    QString pathToArtifactIcon;
    ArtifactPixmapItem *artifactIcon;
    double healthBuff;
    double damageBuff;
    double cost;
    double utilityCoeff;
};

#endif // ARTIFACT_H
