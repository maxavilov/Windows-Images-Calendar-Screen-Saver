/*
 * Windows Images+Calendar Screen Saver
 *
 * file:main.cpp
 * designation: Screen saver main
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
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(argc>1) {
        if ((strcmp(argv[1],"/c")==0) || (strcmp(argv[1],"/C")==0)) {
            // Config;
            return 0;
        }
        else if((strcmp(argv[1],"/p")==0) || (strcmp(argv[1],"/P")==0)) {
            // Preview
            return 0;
        }
        else if((strcmp(argv[1],"/s")==0) || (strcmp(argv[1],"/S")==0)) {
            MainWindow w;
            w.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
            w.showFullScreen();
            return a.exec();
        }
    } else {
        MainWindow w;
        w.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
        w.showFullScreen();
        return a.exec();
    }
}
