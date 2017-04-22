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

#include "channelcommandmodel.h"

std::istream& safeGetline(std::istream& is, std::string& t)
{
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
            case '\n':
                return is;
            case '\r':
                if(sb->sgetc() == '\n')
                    sb->sbumpc();
                return is;
            case EOF:
                // Also handle the case when the last line has no line ending
                if(t.empty())
                    is.setstate(std::ios::eofbit);
                return is;
            default:
                t += (char)c;
        }
    }
}

ChannelCommandModel::ChannelCommandModel(QObject *parent):QAbstractTableModel(parent) {
    for(int i = 0; i < dmxChannels; i++) {
        channelCommands[i] = (char*)calloc(commandLength, sizeof(char));
    }
    ipAddr = (char*)calloc(commandLength, sizeof(char));

    path += QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString();

#if (defined(Q_OS_WIN))

    path += "\\VirtualDJ\\Plugins\\AutoStart\\VDJartnet\\config.txt");

#elif (defined(Q_OS_MAC))

    path += "/VirtualDJ/Plugins64/AutoStart/VDJartnet/config.txt";

#endif

    openFromPath(path);
}

//void ChannelCommandModel::openFromPath(QString openPath) {
//    fileRead = new QFile(openPath);
//    if(!fileRead->open(QIODevice::ReadOnly | QIODevice::Text)) {
//        QMessageBox::information(0,"error",fileRead->errorString());
//    } else {
//        fileRead->readLine(ipAddr, commandLength);
//        strtok(ipAddr, "\n");

//        char line[commandLength + 4];

//        while (fileRead->readLine(line, commandLength + 4) != -1) {
//            //int channelNo = (int)strtol(strtok(line, "~"), nullptr, 0) - 1;
//            auto x = strtok(line, "~");
//            int channelNo = (int)strtol(x, nullptr, 0) - 1;
//            qDebug() << x << (int)strtol(x, nullptr, 0);
//            if (channelNo < dmxChannels && channelNo >= 0) {
//                if (channelCommands[channelNo] == nullptr) {
//                    channelCommands[channelNo] = (char*)malloc(512);
//                }
//                strcpy(channelCommands[channelNo], strtok(nullptr, "\n"));
//            }
//        }
//        fileRead->close();
//    }
//    refresh();
//}

void ChannelCommandModel::openFromPath(std::string openPath) {
    //FILE* file = fopen(path, "r");
    std::ifstream fin (path);

    //if (file != nullptr) {
    if (fin.is_open()) {
        //fgets(host, commandLength, file);
        //fin >> host;
        //fin.getline(host, commandLength);

        //fin >> host;
        safeGetline(fin, ipAddr);
        //zed_net_get_address(&address, host.c_str(), port);

        //char line[commandLength + 4];

        //while (fgets(line, commandLength + 4, file)) {
        //while (fin >> line) {
        //while (!std::ios::eof()) {
        //while (fin.getline(line, commandLength + 4)) {
            //int channelNo = (int)strtol(strtok(line, "~"), nullptr, 0) - 1;
            //if (channelNo < noChannels && channelNo >= 0) {
                //free(channelCommands[channelNo]);
                //channelCommands[channelNo] = (char*)calloc(512, 1);
                //strcpy(channelCommands[channelNo], strtok(nullptr, ""));
            //}
        //}

        std::string line;

        //while (fin >> line) {
        safeGetline(fin, line);
        while (line != "") {
            int posOfDelim = (int)line.find('~'); //Convert unsigned long to int explicitly to stop compiler complaining
            std::string channelNoS = line.substr(0, posOfDelim);
            int channelNo = stoi(channelNoS) - 1;

            if (channelNo < dmxChannels && channelNo >= 0) {
                channelCommands[channelNo] = line.substr(posOfDelim + 1, std::string::npos);
            }
            safeGetline(fin, line);
        }

        //fclose(file);
        fin.close();
    }

    refresh();
}

int ChannelCommandModel::rowCount(const QModelIndex & /*parent*/) const {
   return dmxChannels;
}

int ChannelCommandModel::columnCount(const QModelIndex & /*parent*/) const {
    return 1;
}

QVariant ChannelCommandModel::data(const QModelIndex &index, int role) const {
    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        switch (index.column()) {
        case 0:
            return QString::fromStdString(channelCommands[index.row()]);
            break;
        }
        break;
    default:
        break;
    }
    return QVariant();
}

bool ChannelCommandModel::setData(const QModelIndex & index, const QVariant & value, int role) {
    switch (role) {
    case Qt::EditRole:
        switch (index.column()) {
        case 0:
            channelCommands[index.row()] = value.toString().toStdString();
            break;
        }
        break;
    default:
        break;
    }
    return true;
}

Qt::ItemFlags ChannelCommandModel::flags(const QModelIndex & /*index*/) const {
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsDropEnabled;
}

void ChannelCommandModel::save() {
    saveToPath(path);
}

void ChannelCommandModel::saveToPath(std::string savePath) {
    fileWrite = new QSaveFile(QString::fromStdString(savePath));
    if(!fileWrite->open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::information(0,"error",fileWrite->errorString());
    } else {
        fileWrite->write(ipAddr.c_str(), ipAddr.length());
        fileWrite->write("\n", 1);

        for(int i = 0; i < dmxChannels; i++) {
            if(channelCommands[i][0] != 0) {
                char channelNo[4] = "000";
                snprintf(channelNo, 4, "%03d", i + 1);
                fileWrite->write(channelNo, 3);
                fileWrite->write("~", 1);
                fileWrite->write(channelCommands[i].c_str(), channelCommands[i].length());
                fileWrite->write("\n", 1);
                fileWrite->flush();
            }
        }

        fileWrite->commit();
    }
    refresh();
}

void ChannelCommandModel::refresh() {
    dataChanged(createIndex(0,0),createIndex(dmxChannels - 1, 0));
}

Qt::DropActions ChannelCommandModel::supportedDropActions() const {
    return Qt::CopyAction;
}

bool ChannelCommandModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) {
    if (row < 0 || row >= dmxChannels) {
        row = parent.row();
    }

    if (data->hasText()) {
        channelCommands[row] = data->data("text/plain").data();
        return true;
    } else {
        return false;
    }
}

bool ChannelCommandModel::canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const {
    if (data->hasText()) {
        return true;
    } else {
        return false;
    }
}
