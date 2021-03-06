/*******************************************************************************
 *  Project: BlockSnapping
 *  Purpose: QGraphicsItem snap example
 *  Author: Jeison Santiago, jeison.santiago@gmail.com
 *  Language: C++
 *******************************************************************************
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2020 Jeison Santiago
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *******************************************************************************/

#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_graphicsView = new QGraphicsView(this);
    this->setCentralWidget(m_graphicsView);

    m_graphicsScene = new QGraphicsScene(this);
    m_graphicsView->setScene(m_graphicsScene);

    // draw graphics items
    BlockGraphicsItem *item = new BlockGraphicsItem("Test 0");
    m_graphicsScene->addItem(item);
    item->setPos(-200,-200);

    BlockGraphicsItem *item2 = new BlockGraphicsItem("Test 1");
    item2->setPos(1,1);
    m_graphicsScene->addItem(item2);

    BlockGraphicsItem *item3 = new BlockGraphicsItem("Test 2");
    item3->setPos(1,200);
    m_graphicsScene->addItem(item3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

