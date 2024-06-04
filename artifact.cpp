#include "artifact.h"

Artifact::Artifact(QString Name, QString PathToArtifactIcon, double HealthBuff, double DamageBuff, int Cost)
{
    name = Name;
    pathToArtifactIcon = PathToArtifactIcon;
    healthBuff = HealthBuff;
    damageBuff = DamageBuff;
    cost = Cost;
    QString statHealthBuff;
    QString statDamageBuff;

    utilityCoeff = (damageBuff * 100)/cost;

    if(healthBuff != 0)
    {

        statHealthBuff = "Health: +" + QString::number(healthBuff);
    }
    else
    {
        statHealthBuff = "";
    }
    //}

    if(damageBuff < 1)
    {
        statDamageBuff = "Damage: +" + QString::number(damageBuff * 100) + "%";
    }
    else if(damageBuff > 1)
    {
        statDamageBuff = "Damage: +" + QString::number(damageBuff);
    }
    else
    {
        statDamageBuff = "";
    }

    if(statHealthBuff == "")
    {
        stats =statDamageBuff;
    }
    else
    {
        stats = statHealthBuff + "\n" + statDamageBuff;
    }


    artifactIcon = new ArtifactPixmapItem(QPixmap(PathToArtifactIcon).scaled(100, 100, Qt::KeepAspectRatio), name, stats);
    //artifactIcon->setPixmap(QPixmap(PathToArtifactIcon).scaled(100, 100, Qt::KeepAspectRatio));
    artifactIcon->setScale(0.5);

}

Artifact::Artifact()
{

}

QString Artifact::getNameOfArtifact()
{
    return name;
}

double Artifact::makeDamageBuff(int damage)
{
    if(damageBuff < 0)
    {
        return damage + (damage * damageBuff);
    }
    else
    {
        return damage + damageBuff;
    }
}

int Artifact::makeHealthBuff(int health)
{
    return health + healthBuff;
}

double Artifact::getCost()
{
    return cost;
}

ArtifactPixmapItem * Artifact::getArtifactIcon()
{
    return artifactIcon;
}

QString Artifact::getStatsOfArtifact()
{
    return stats;
}

QString Artifact::getPathToArtifactIcon()
{
    return pathToArtifactIcon;
}

double Artifact::getDamageBuff()
{
    return damageBuff;
}
