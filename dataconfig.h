#ifndef DATACONFIG_H
#define DATACONFIG_H

#include <QObject>
#include<QMap>
#include<QVector>
class dataconfig : public QObject
{
    Q_OBJECT
public:
    explicit dataconfig(QObject *parent = nullptr);

    QMap<int,QVector<QVector<int>> >mdata;
signals:

public slots:
};

#endif // DATACONFIG_H
