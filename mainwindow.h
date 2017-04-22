#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include <QMoveEvent>
#include <QFileDialog>
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
    void exit();
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
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
    QAction *exitAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *helpAct;
    QAction *aboutAct;
};

#endif // MAINWINDOW_H
