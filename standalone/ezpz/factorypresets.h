#ifndef FACTORYPRESETS_H
#define FACTORYPRESETS_H

#include <QVariant>

class FactoryPresets
{
public:
    FactoryPresets();

    QVariantMap programChangeMap;
    void        createProgramChange();

    QVariantMap factoryElevenRackMap;
    void        createElevenRackMap();

    QVariantMap factoryPodMap;
    void        createPodMap();

    QVariantMap factoryLiveMap;
    void        createLiveMap();
};

#endif // FACTORYPRESETS_H
