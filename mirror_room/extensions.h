#ifndef EXTENSIONS_H
#define EXTENSIONS_H

#include <QDataStream>
#include <QFile>
#include <QString>


template <typename T>
void dumpToFile(const QString &filename, const T &o, QFile::OpenMode openMode = QFile::WriteOnly)
{
    QFile file(filename);

    if (!file.open(openMode)) {
        qWarning(QString("error on openning file \'%1\' - dump failed").arg(filename).toLocal8Bit().data());
        return;
    }

    QDataStream ds(&file);

    ds << o;
}

template <typename T>
void loadFromDump(const QString &filename, T &o)
{
    QFile file(filename);

    if (!file.open(QFile::ReadOnly)) {
        qWarning(QString("error on openning file \'%1\' - load from dump failed").arg(filename).toLocal8Bit().data());
        return;
    }

    QDataStream ds(&file);

    ds >> o;
}

#endif // EXTENSIONS_H
