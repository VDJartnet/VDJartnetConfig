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
    QString path;
};

#endif // PRESETWIDGET_H
