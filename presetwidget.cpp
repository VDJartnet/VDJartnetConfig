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

#if (defined(Q_OS_WIN))

    char pathDocs[commandLength];
    SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_DEFAULT, nullptr, pathDocs);
    path += pathDocs
    path += "\\VirtualDJ\\Plugins\\AutoStart\\VDJartnet\\presets.txt");

#elif (defined(Q_OS_MAC))

    path += getenv("HOME");
    path += "/Documents/VirtualDJ/Plugins64/AutoStart/VDJartnet/presets.txt";

#endif

    fileRead = new QFile(path);
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
