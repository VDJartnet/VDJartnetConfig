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

#ifndef PRESETWIDGET_H
#define PRESETWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QGridLayout>
#include <QMimeData>
#include <QDrag>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QStandardPaths>

class PresetList : public QListWidget {
public:
    PresetList();
    ~PresetList();
    void startDrag(Qt::DropActions supportedActions);
};

class PresetWidget : public QWidget {
public:
    PresetWidget();
    ~PresetWidget();
private:
    PresetList* presetList;
    QFile* fileRead;
    std::string path;
};

#endif // PRESETWIDGET_H
