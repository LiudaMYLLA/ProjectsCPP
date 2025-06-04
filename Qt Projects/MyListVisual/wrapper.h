#pragma once
#include <QObject>
#include "cdll.h"
#include <QVariantList>
class Wrapper : public QObject{
    Q_OBJECT
public:
    Wrapper();

    Q_INVOKABLE void addAtTheBeginning(const QVariant& value);
    Q_INVOKABLE void addAtTheEnd(const QVariant& value);
    Q_INVOKABLE void addAtThePosition(QVariant data, QVariant pos);

    Q_INVOKABLE void deleteAll();
    Q_INVOKABLE void deleteFromPosition(QVariant pos);

    //QVariantList is an analog of std::vector<QVariant>
    Q_INVOKABLE QVariantList getAll() const;

    Q_INVOKABLE void printAllInBackOrder() const;

private:
    cdll<int> list1;
};

