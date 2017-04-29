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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtWidgets>
#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include <QMoveEvent>
#include <QFileDialog>
#include <QUndoStack>
#include <QUndoCommand>
#include <QCloseEvent>
#include "channelcommandmodel.h"
#include "presetwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void moveEvent(QMoveEvent *event);
    PresetWidget* presetWindow;

protected:
    void closeEvent (QCloseEvent *event);

private:
    QTableView* tableView;
    ChannelCommandModel* channelCommandModel;
    QLabel* ipLabel;
    QLineEdit* ipEdit;
    QGridLayout* ipLayout;
    QWidget* ipWidget;
    QGridLayout* layout;
    QWidget* central;
    QMenuBar* menuBarMain;

private slots:
    void save();
    void clear();
    void importFile();
    void exportFile();
//    void exit();
//    void undo();
//    void redo();
//    void cut();
//    void copy();
//    void paste();
    void help();
    void about();

private:
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QAction *saveAct;
    QAction *clearAct;
    QAction *importAct;
    QAction *exportAct;
//    QAction *exitAct;
    QAction *undoAct;
    QAction *redoAct;
//    QAction *cutAct;
//    QAction *copyAct;
//    QAction *pasteAct;
    QAction *helpAct;
    QAction *aboutAct;
};

#endif // MAINWINDOW_H
