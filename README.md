# QGraphicsItem-Snapping
Simple snapping implementation using QGraphicsItem.

# Motivation
To be used in a personal project

# Installation
Just clone and open the project file with **QtCreator**, have fun!

# Usage
setup your **```QGraphicsView```** and **```QGraphicsScene```**,
then you can simple copy ```BlockGraphicsItem.h``` and ```BlockGraphicsItem.cpp```.
see the **MainWindow.cpp**.

```cpp
m_graphicsView = new QGraphicsView(this);
this->setCentralWidget(m_graphicsView);

m_graphicsScene = new QGraphicsScene(this);
m_graphicsView->setScene(m_graphicsScene);

BlockGraphicsItem *item = new BlockGraphicsItem("Test 0");
m_graphicsScene->addItem(item);

```
# Screenshot

# License
[The MIT License (MIT)](http://www.opensource.org/licenses/mit-license.php)
