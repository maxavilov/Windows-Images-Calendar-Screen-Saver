/*
 * Windows Images+Calendar Screen Saver
 *
 * file: mainwindows.h
 * designation: Screen saver main window header file
 *
 * Copyright (C) 2016 Maxim Avilov (maxim.avilov@gmail.com)
 *
 * This file is part of Windows Images+Calendar Screen Saver
 *
 * Windows Images+Calendar Screen Saver is free software: you can
 * redistribute it and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * (Этот файл — часть Windows Images+Calendar Screen Saver
 * Windows Images+Calendar Screen Saver-  свободная программа: вы можете
 * перераспространять ее и/или изменять ее на условиях Стандартной
 * общественной лицензии GNU в том виде, в каком она была опубликована
 * Фондом свободного программного обеспечения; либо версии 3 лицензии,
 * либо (по вашему выбору) любой более поздней версии.
 *
 * Эта программа распространяется в надежде, что она будет полезной,
 * но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
 * или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Стандартной
 * общественной лицензии GNU.
 *
 * Вы должны были получить копию Стандартной общественной лицензии GNU
 * вместе с этой программой. Если это не так, см.
 * <http://www.gnu.org/licenses/>.)
 *
 * +++++++++++++[>+>+++++>+++++++++>++++++++>++>++++++<<<<<<-]>>.>.-.>.<-----.++
 * +.<-------.>>>++++++.>-.<<-------.<++++++.>++++++++.++++.>.<<<+++++++.>--.>--
 * --.+++.+++.<.<<---.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QDesktopWidget.h>
#include <vector>
#include <QFontMetrics>

#define IMGS_COUNT 4
#define TIMER_INTERVAL_MS 10000

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *obj, QEvent *event);
    ~MainWindow();

public slots:
    void onTimer();

private:

    std::vector<QString> monthStrings; //Вектор нужен из за ошибки в QString QLocale::standaloneMonthName
                                       //(Qt 5.7.1 на Mac OS 10.12 возвращает то же, что и QLocale::monthName для русской локали)
    bool firstEventSkiped;

    Ui::MainWindow *ui;

    QGraphicsScene* scene;

    QString extraLightFontFamily;
    QString boldFontFamily;

    QTimer* timer;

    int currentImgIdx;

    std::vector<QPixmap> images;

    void changeImage();
};

#endif // MAINWINDOW_H
