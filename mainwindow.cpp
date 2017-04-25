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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    setWindowTitle("VDJartnetConfig");
    setFixedSize(600, 400);

    tableView = new QTableView();
    channelCommandModel = new ChannelCommandModel(nullptr);
    tableView->setModel(channelCommandModel);
    tableView->horizontalHeader()->hide();
    tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    tableView->setDragDropMode(QAbstractItemView::DropOnly);
    tableView->setAcceptDrops(true);
    tableView->viewport()->setAcceptDrops(true);
    tableView->setDropIndicatorShown(true);
    tableView->setAutoScroll(true);

    ipLabel = new QLabel("Dest IP:");
    ipEdit = new QLineEdit(QString::fromStdString(channelCommandModel->ipAddr));

    ipLayout = new QGridLayout;
    ipLayout->addWidget(ipLabel, 0, 0);
    ipLayout->addWidget(ipEdit, 0, 1);

    ipWidget = new QWidget();
    ipWidget->setLayout(ipLayout);

    menuBarMain = new QMenuBar(0);

    layout = new QGridLayout;
    layout->addWidget(menuBarMain, 0, 0);
    layout->addWidget(ipWidget, 1, 0);
    layout->addWidget(tableView, 2, 0);

    central = new QWidget();
    setCentralWidget(central);
    central->setLayout(layout);

    presetWindow = new PresetWidget();
    presetWindow->show();

    saveAct = new QAction("Save", this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip("Save settings to disk");
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    clearAct = new QAction("Clear", this);
    clearAct->setShortcuts(QKeySequence::Delete);
    clearAct->setStatusTip("Clear all settings");
    connect(clearAct, &QAction::triggered, this, &MainWindow::clear);

    importAct = new QAction("Import", this);
    importAct->setShortcuts(QKeySequence::Open);
    importAct->setStatusTip("Import settings from disk");
    connect(importAct, &QAction::triggered, this, &MainWindow::importFile);

    exportAct = new QAction("Export", this);
    exportAct->setShortcuts(QKeySequence::SaveAs);
    exportAct->setStatusTip("Export settings to disk");
    connect(exportAct, &QAction::triggered, this, &MainWindow::exportFile);

//    exitAct = new QAction("Exit2", this);
//    exitAct->setShortcuts(QKeySequence::Close);
//    exitAct->setShortcuts(QKeySequence::Quit);
//    exitAct->setStatusTip("Quit program");
//    connect(exitAct, &QAction::triggered, this, &MainWindow::exit);

    undoAct = channelCommandModel->undoStack->createUndoAction(0, "");
//    undoAct = new QAction("Undo", this);
    undoAct->setShortcuts(QKeySequence::Undo);
//    undoAct->setStatusTip("Undo last change");
//    connect(undoAct, &QAction::triggered, this, &MainWindow::undo);

    redoAct = channelCommandModel->undoStack->createRedoAction(0, "");
//    redoAct = new QAction("Redo", this);
    redoAct->setShortcuts(QKeySequence::Redo);
//    redoAct->setStatusTip("Redo last change");
//    connect(redoAct, &QAction::triggered, this, &MainWindow::redo);

//    cutAct = new QAction("Cut", this);
//    cutAct->setShortcuts(QKeySequence::Cut);
//    cutAct->setStatusTip("Cut selection to clipboard");
//    connect(cutAct, &QAction::triggered, this, &MainWindow::cut);

//    copyAct = new QAction("Copy", this);
//    copyAct->setShortcuts(QKeySequence::Copy);
//    copyAct->setStatusTip("Copy selection to clipboard");
//    connect(copyAct, &QAction::triggered, this, &MainWindow::copy);

//    pasteAct = new QAction("Paste", this);
//    pasteAct->setShortcuts(QKeySequence::Paste);
//    pasteAct->setStatusTip("Paste selection from clipboard");
//    connect(pasteAct, &QAction::triggered, this, &MainWindow::paste);

    helpAct = new QAction("Help", this);
    helpAct->setShortcuts(QKeySequence::HelpContents);
    helpAct->setStatusTip("View help window");
    connect(helpAct, &QAction::triggered, this, &MainWindow::help);

    aboutAct = new QAction("About", this);
//    aboutAct->setShortcuts(QKeySequence::WhatsThis);
    aboutAct->setStatusTip("View about window");
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    fileMenu = menuBarMain->addMenu("File");
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(clearAct);
    fileMenu->addSeparator();
    fileMenu->addAction(importAct);
    fileMenu->addAction(exportAct);
//    fileMenu->addSeparator();
//    fileMenu->addAction(exitAct);

    editMenu = menuBarMain->addMenu("Edit");
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
//    editMenu->addSeparator();
//    editMenu->addAction(cutAct);
//    editMenu->addAction(copyAct);
//    editMenu->addAction(pasteAct);

    helpMenu = menuBarMain->addMenu("Help");
    helpMenu->addAction(helpAct);
    helpMenu->addAction(aboutAct);
}

MainWindow::~MainWindow() {
}

void MainWindow::closeEvent (QCloseEvent *event) {
    if (channelCommandModel->undoStack->isClean()) {
        event->accept();
    } else {
        QMessageBox::StandardButton savePrompt = QMessageBox::question( this, "VDJartnetConfig", "Do you want to save before quitting?\n",
                                                                        QMessageBox::Cancel | QMessageBox::Discard | QMessageBox::Save, QMessageBox::Save);
        switch (savePrompt) {
        case QMessageBox::Cancel:
            event->ignore();
            return;
            break;
        case QMessageBox::Discard:
            event->accept();
            break;
        case QMessageBox::Save:
            save();
            event->accept();
            break;
        }
    }
}

void MainWindow::save() {
    channelCommandModel->ipAddr = ipEdit->text().toStdString();
    channelCommandModel->save();
    channelCommandModel->undoStack->setClean();
}

void MainWindow::clear() {
    for(int i = 0; i < dmxChannels; i++) {
        channelCommandModel->channelCommands[i] = (char*)calloc(commandLength, sizeof(char));
    }
    channelCommandModel->undoStack->clear();
    channelCommandModel->refresh();
}

void MainWindow::importFile() {
    std::string importPath = QFileDialog::getOpenFileName(this, "Import File", nullptr, "All Files (*)").toStdString();
    channelCommandModel->openFromPath(importPath);
    ipEdit->setText(QString::fromStdString(channelCommandModel->ipAddr));
}

void MainWindow::exportFile() {
    channelCommandModel->ipAddr = ipEdit->text().toStdString();
    std::string exportPath = QFileDialog::getSaveFileName(this, "Export File", nullptr, "All Files (*)").toStdString();
    channelCommandModel->saveToPath(exportPath);
}

//void MainWindow::exit() {
//    close();
//}

//void MainWindow::undo() {

//}

//void MainWindow::redo() {

//}

//void MainWindow::cut() {

//}

//void MainWindow::copy() {

//}

//void MainWindow::paste() {

//}

void MainWindow::help() {

}

void MainWindow::about() {

}

void MainWindow::moveEvent(QMoveEvent *event) {
    presetWindow->move(presetWindow->pos() += event->pos() - event->oldPos());
}
