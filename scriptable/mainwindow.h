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
    QToolBar *getToolBar();
    QPlainTextEdit *getTextEdit();
    QListWidget *getPluginMenu();

private Q_SLOTS:
    void slotRunScript();
    void slotPrintDiagnostics();
    void slotPluginItemClicked(QListWidgetItem*);

private:
    void runScript(const QStringList &);

    QPlainTextEdit *m_scriptEdit;
    QToolBar *m_toolBar;
    QListWidget *m_pluginMenu;
    const QFileInfo m_inputDir = QFileInfo("/home/shyamnath/qt_for_python/shyam/presentations/kde_akademy_2022/scriptable/plugins");
};

#endif // MAINWINDOW_H
