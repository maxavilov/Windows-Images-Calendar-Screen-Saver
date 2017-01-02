/*
 * Windows Images+Calendar Screen Saver
 *
 * file: mainwindows.cpp
 * designation: Screen saver main window implementation
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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this)),
    extraLightFontFamily(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/fonts/SourceCodePro-ExtraLight.otf")).at(0)),
    boldFontFamily(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/fonts/SourceCodePro-Bold.otf")).at(0)),
    timer(new QTimer(this))
{
    ui->setupUi(this);

    monthStrings.push_back(QString::fromUtf8("Январь"));
    monthStrings.push_back(QString::fromUtf8("Февраль"));
    monthStrings.push_back(QString::fromUtf8("Март"));
    monthStrings.push_back(QString::fromUtf8("Апрель"));
    monthStrings.push_back(QString::fromUtf8("Май"));
    monthStrings.push_back(QString::fromUtf8("Июнь"));
    monthStrings.push_back(QString::fromUtf8("Июль"));
    monthStrings.push_back(QString::fromUtf8("Август"));
    monthStrings.push_back(QString::fromUtf8("Сентябрь"));
    monthStrings.push_back(QString::fromUtf8("Октябрь"));
    monthStrings.push_back(QString::fromUtf8("Ноябрь"));
    monthStrings.push_back(QString::fromUtf8("Декабрь"));

    currentImgIdx = 0;
    for (int i = 0; i < IMGS_COUNT; i++) {
        QString imgResource = QString(":/img/%1.png").arg(i+1);
        images.push_back(QPixmap(imgResource));
    }

    ui->graphicsView->setScene(scene);
    ui->graphicsView->scale( ((float) QApplication::desktop()->screenGeometry().width() ) / ((float) images[0].size().width()),
            ((float) QApplication::desktop()->screenGeometry().height() ) / ((float) images[0].size().height()));

    connect(timer, SIGNAL(timeout()), SLOT(onTimer()));
    timer->start(TIMER_INTERVAL_MS);

    this->setCursor(Qt::BlankCursor);

    firstEventSkiped = false;
    qApp->installEventFilter(this);
}

void MainWindow::showEvent(QShowEvent *event) {
    QWidget::showEvent( event );
    changeImage();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    switch (event->type()) {
    case QEvent::MouseButtonDblClick:
    case QEvent::MouseButtonPress:
    case QEvent::MouseMove:
    case QEvent::KeyPress:
        if (firstEventSkiped) {
            QApplication::quit();
        } else {
            firstEventSkiped = true;
        }
        //No need break in this place
    default:
        return QWidget::eventFilter(obj, event);
        break;
    }
}

void MainWindow::onTimer() {
    changeImage();
}

void MainWindow::changeImage() {
    scene->clear();
    scene->setSceneRect(images[currentImgIdx].rect());
    scene->addPixmap(images[currentImgIdx]);

    QPainterPath textPath;
    QRect textRect(images[currentImgIdx].width() * 3 / 100,
                   images[currentImgIdx].height() * 85 / 100,
                   images[currentImgIdx].width() * 65 / 100 - images[currentImgIdx].width() * 3 / 100,
                   images[currentImgIdx].height() * 99 / 100 - images[currentImgIdx].height() * 85 / 100);

    QDate curDate(QDate::currentDate());
    QTime curTime(QTime::currentTime());

    QFont bigFont(extraLightFontFamily, textRect.height()/4, 12);
    QFontMetrics bigFontMetric(bigFont);
    QFont otherFont(extraLightFontFamily, textRect.height()/13, 12);
    QFont otherBold(boldFontFamily, textRect.height()/13, QFont::Bold);
    int vShiftUnit =  textRect.height()/26;

    textPath.addText(textRect.left(),textRect.top() + vShiftUnit*6, bigFont, monthStrings[curDate.month()-1]);

    int daysInMonth = curDate.daysInMonth();

    QString weeksStr("");
    weeksStr.reserve(daysInMonth*3-1+10);
    QString weeksBoldStr("");
    weeksBoldStr.reserve(daysInMonth*3-1+10);
    QString daysStr("");
    daysStr.reserve(daysInMonth*3-1+10);
    QString daysBoldStr("");
    daysBoldStr.reserve(daysInMonth*3-1+10);
    QString weekDaysStr("");
    weekDaysStr.reserve(daysInMonth*3-1+10);

    QPointF weeksPos(textRect.left(), textRect.top() + vShiftUnit*13);
    QPointF datesPos(textRect.left(), textRect.top() + vShiftUnit*16);
    QPointF weekDaysPos(textRect.left(), textRect.top() + vShiftUnit*19);

    const QString lineAndSpace(QString::fromUtf8("\u2502 "));
    const QString twoSpace("  ");
    const QString space(" ");
    const QString zero("0");
    for (int i = 1; i <= daysInMonth; i++) {
        QDate workDate(curDate.year(), curDate.month(), i);
        if (workDate.dayOfWeek() == Qt::Monday) {
            weeksStr += lineAndSpace % twoSpace;
            if (workDate.weekNumber() < 10) {
                weeksBoldStr += twoSpace % QString::number(workDate.weekNumber()) % space;
            } else {
                weeksBoldStr += twoSpace % QString::number(workDate.weekNumber());
            }
            daysStr += lineAndSpace;
            daysBoldStr += twoSpace;
            weekDaysStr += lineAndSpace;
        } else {
            weeksStr += twoSpace;
            weeksBoldStr += twoSpace;
        }
        if (i == curDate.day()) {
            if (i < 10) {
                daysBoldStr += zero;
            }
            daysBoldStr += QString::number(i);
            daysStr += twoSpace;
        } else {
            if (i < 10) {
                daysStr += zero;
            }
            daysStr += QString::number(i);
            daysBoldStr += twoSpace;
        }
        weekDaysStr += workDate.toString("ddd").mid(0, 2);
        if (i != curDate.daysInMonth()) {
            weeksStr += space;
            weeksBoldStr += space;
            daysStr += space;
            daysBoldStr += space;
            weekDaysStr += space;
        }
    }

    textPath.addText(weeksPos, otherFont, weeksStr);
    textPath.addText(weeksPos, otherBold, weeksBoldStr);
    textPath.addText(datesPos, otherFont, daysStr);
    textPath.addText(datesPos, otherBold, daysBoldStr);
    textPath.addText(weekDaysPos, otherFont, weekDaysStr);

    QString timeString = curTime.toString("HH:mm");
    textPath.addText(images[currentImgIdx].width() * 99 / 100 - bigFontMetric.width(timeString), images[currentImgIdx].height() * 99 / 100, bigFont, timeString);

    scene->addPath(textPath, QPen(QBrush(Qt::white), 1), QBrush(Qt::white));

    currentImgIdx++;
    if (currentImgIdx >= IMGS_COUNT) currentImgIdx = 0;
}

MainWindow::~MainWindow()
{
    timer->stop();
    delete timer;
    delete scene;
    delete ui;
}
