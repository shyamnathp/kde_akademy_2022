// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtCore/QFileInfo>

class QPlainTextEdit;
class QListWidget;
class QListWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

    void testFunction1();
    void openFile();
    QToolBar *getToolBar();
    QPlainTextEdit *getTextEdit();
    QListWidget *getPluginMenu();
    void setTextEdit(QPlainTextEdit*);

private Q_SLOTS:
    void slotRunScript();
    void slotPrintDiagnostics();
    void slotPluginItemClicked(QListWidgetItem*);

private:
    void runScript(const QStringList &);

    QPlainTextEdit *m_scriptEdit;
    QToolBar *m_toolBar;
    QListWidget *m_pluginMenu;
    const QFileInfo m_inputDir = QFileInfo("/home/shyamnath/qt_for_python/pyside-setup/examples/scriptableapplication/plugins");
};

#endif // MAINWINDOW_H
