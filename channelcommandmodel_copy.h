#ifndef CHANNELCOMMANDMODEL_H
#define CHANNELCOMMANDMODEL_H

#include <QAbstractTableModel>

class ChannelCommandModel : public QAbstractTableModel
{
public:
    ChannelCommandModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

#endif // CHANNELCOMMANDMODEL_H
