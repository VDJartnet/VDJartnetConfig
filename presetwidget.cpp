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

#include "presetwidget.h"

PresetList::PresetList() {
}

PresetList::~PresetList() {
}

void PresetList::startDrag(Qt::DropActions supportedActions) {
    QMimeData* mimeData = new QMimeData();
    mimeData->setData("text/plain", currentItem()->data(Qt::UserRole).toByteArray());
    QDrag* drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->exec(Qt::CopyAction);
}

PresetWidget::PresetWidget() {
    setWindowTitle("VDJartnet Presets");
    setFixedSize(200, 400);

    presetList = new PresetList();
    presetList->setDragEnabled(true);
    presetList->show();

    path += QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString();

#if (defined(Q_OS_WIN))

    path += "\\VirtualDJ\\Plugins\\AutoStart\\VDJartnet\\presets.txt";

#elif (defined(Q_OS_MAC))

    path += "/VirtualDJ/Plugins64/AutoStart/VDJartnet/presets.txt";

#endif

    fileRead = new QFile(QString::fromStdString(path));
    if(!fileRead->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(0,"error",fileRead->errorString());
    } else {
        char line[1024];

        while (fileRead->readLine(line, 1024) != -1) {
            QListWidgetItem* item = new QListWidgetItem(strtok(line, "~"), presetList);
            item->setData(Qt::UserRole, strtok(nullptr, "\n"));
        }
        fileRead->close();
    }


    QGridLayout* layout = new QGridLayout;
    layout->addWidget(presetList, 0, 0);

    setLayout(layout);
}

PresetWidget::~PresetWidget() {
}
