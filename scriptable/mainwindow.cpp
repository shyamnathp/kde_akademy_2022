// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "mainwindow.h"
#include "pythonutils.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidgetItem>

#include <QtGui/QAction>
#include <QtGui/QFontDatabase>
#include <QtGui/QIcon>

#include <QtCore/QDebug>
#include <QtCore/QTextStream>
#include <QtCore/QFile>

static const char defaultScript[] = R"(
import AppLib
print("Hello, world")
mainWindow.testFunction1()
)";

MainWindow::MainWindow()
    : m_scriptEdit(new QPlainTextEdit(QString::fromLatin1(defaultScript).trimmed(), this))
{
    setWindowTitle(tr("Scriptable Application"));

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    const QIcon runIcon = QIcon::fromTheme(QStringLiteral("system-run"));
    QAction *runAction = fileMenu->addAction(runIcon, tr("&Run..."), this, &MainWindow::slotRunScript);
    runAction->setShortcut(Qt::CTRL | Qt::Key_R);
    QAction *diagnosticAction = fileMenu->addAction(tr("&Print Diagnostics"), this, &MainWindow::slotPrintDiagnostics);
    diagnosticAction->setShortcut(Qt::CTRL | Qt::Key_D);
    fileMenu->addAction(tr("&Invoke testFunction1()"), this, &MainWindow::testFunction1);
    fileMenu->addAction(tr("&Open File"), this, &MainWindow::openFile);

    const QIcon quitIcon = QIcon::fromTheme(QStringLiteral("application-exit"));
    QAction *quitAction = fileMenu->addAction(quitIcon, tr("&Quit"), qApp, &QCoreApplication::quit);
    quitAction->setShortcut(Qt::CTRL | Qt::Key_Q);

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    const QIcon clearIcon = QIcon::fromTheme(QStringLiteral("edit-clear"));
    QAction *clearAction = editMenu->addAction(clearIcon, tr("&Clear"), m_scriptEdit, &QPlainTextEdit::clear);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    const QIcon aboutIcon = QIcon::fromTheme(QStringLiteral("help-about"));
    QAction *aboutAction = helpMenu->addAction(aboutIcon, tr("&About Qt"), qApp, &QApplication::aboutQt);

    m_toolBar = new QToolBar;
    addToolBar(m_toolBar);
    m_toolBar->addAction(quitAction);
    m_toolBar->addSeparator();
    m_toolBar->addAction(clearAction);
    m_toolBar->addSeparator();
    m_toolBar->addAction(runAction);
    m_toolBar->addSeparator();
    m_toolBar->addAction(aboutAction);

    m_scriptEdit->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    // setCentralWidget(m_scriptEdit);

    if (!PythonUtils::bindAppObject("__main__", "mainWindow", PythonUtils::MainWindowType, this))
       statusBar()->showMessage(tr("Error loading the application module"));

    m_pluginMenu = new QListWidget();

    // Init plugins
    if (!m_inputDir.isDir()) {
        qWarning() << "No plugins detected";
    } else {
        QStringList l;
        QDir directory(m_inputDir.absoluteFilePath());
        QStringList plugins = directory.entryList(QStringList() << "*.py", QDir::Files);
        for(QString &filename: plugins) {
            // QString filePath = directory.filePath(filename);
            // QFile f(filePath);
            // if (!f.open(QFile::ReadOnly | QFile::Text)) break;
            // QTextStream in(&f);
            // for (auto line: in.readAll().split("\n"))
            //     l << line;
            QListWidgetItem *item = new QListWidgetItem(filename);
            item->setSizeHint(QSize(item->sizeHint().width(), 30));
            m_pluginMenu->addItem(item);
        }

        connect(m_pluginMenu, &QListWidget::itemClicked, this, &MainWindow::slotPluginItemClicked);
        // if (PythonUtils::runScript(l)) {
        //     qDebug() << "Plugins loaded";
        // } else {
        //     qDebug() << "Error while loading plugins";
        // }
    }


    QWidget *centralWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout();
    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->addWidget(new QLabel("Plugins"));
    leftLayout->addWidget(m_pluginMenu);
    layout->addLayout(leftLayout, 1);
    layout->addWidget(m_scriptEdit, 3);
    centralWidget->setLayout(layout);

    this->setStyleSheet("font-size: 12px;");

    setCentralWidget(centralWidget);
}

void MainWindow::slotRunScript()
{
    const QString text = m_scriptEdit->toPlainText().trimmed();
    const QStringList script = text.split(u'\n', Qt::SkipEmptyParts);
    if (!script.isEmpty())
        runScript(script);
}

void MainWindow::slotPrintDiagnostics()
{
    const QStringList script = QStringList()
            << "import sys" << "print('Path=', sys.path)" << "print('Executable=', sys.executable)";
    runScript(script);
}

void MainWindow::runScript(const QStringList &script)
{
    if (!::PythonUtils::runScript(script))
        statusBar()->showMessage(tr("Error running script"));
}

void MainWindow::testFunction1()
{
    static int n = 1;
    QString message;
    QTextStream(&message) << __FUNCTION__ << " called #" << n++;
    qDebug().noquote() << message;
    statusBar()->showMessage(message);
}

void MainWindow::openFile()
{
    auto fileName = QFileDialog::getOpenFileName(this, QString(), "/home/shyamnath/qt_for_python/pyside-setup/examples/scriptableapplication/plugins", tr("Python Files (*.py)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    m_scriptEdit->setPlainText(file.readAll());
    QString message;
    QTextStream(&message) << fileName << "\n";
    qDebug().noquote() << message;
}

QToolBar* MainWindow::getToolBar()
{
    return m_toolBar;
}

QPlainTextEdit* MainWindow::getTextEdit()
{
    return m_scriptEdit;
}

QListWidget* MainWindow::getPluginMenu()
{
    return m_pluginMenu;
}

void MainWindow::slotPluginItemClicked(QListWidgetItem* item)
{
    QString fileName = item->text();
    QDir pluginsPath(m_inputDir.absoluteFilePath());
    QString filePath = pluginsPath.filePath(fileName);
    QString message;
    QTextStream(&message) << filePath << "\n";
    qDebug().noquote() << message;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    m_scriptEdit->setPlainText(file.readAll());
}

void MainWindow::setTextEdit(QPlainTextEdit* newscriptEdit)
{
    m_scriptEdit = newscriptEdit;
}