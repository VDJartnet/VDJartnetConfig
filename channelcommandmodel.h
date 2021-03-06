//This file is part of VDJartnetConfig.
//
//VDJartnetConfig is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//VDJartnetConfig is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with VDJartnetConfig.  If not, see <http://www.gnu.org/licenses/>.

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
#include <QUndoStack>
#include "textundocommand.h"

const int commandLength = 512;
const int dmxChannels = 512;

class ChannelCommandModel : public QAbstractTableModel, public Refreshable {
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

    QUndoStack* undoStack = new QUndoStack();
private:
    //QFile* fileRead;
    QSaveFile* fileWrite;
    std::string path;
};

#endif // CHANNELCOMMANDMODEL_H
