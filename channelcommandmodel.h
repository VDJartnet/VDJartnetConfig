#ifndef CHANNELCOMMANDMODEL_H
#define CHANNELCOMMANDMODEL_H

#include <QAbstractTableModel>
#include <QString>
#include <QFile>
#include <QSaveFile>
#include <QMessageBox>
#include <QLineEdit>
#include <string>
#include <fstream>
#include <QMimeData>
#include <QDebug>
#include <QStandardPaths>

const int commandLength = 512;
const int dmxChannels = 512;

class ChannelCommandModel : public QAbstractTableModel {
public:
    ChannelCommandModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const;
    std::string ipAddr;
    std::string channelCommands[dmxChannels];
    void save();
    Qt::DropActions supportedDropActions() const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
    bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const;
    void openFromPath(std::string openPath);
    void saveToPath(std::string savePath);
    void refresh();
private:
    //QFile* fileRead;
    QSaveFile* fileWrite;
    std::string path;
};

#endif // CHANNELCOMMANDMODEL_H
