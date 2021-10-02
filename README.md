# QGraphicsItem-Snapping
**Very simple** snapping implementation using QGraphicsItem with SceneEvents

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
<img src="https://github.com/jeisonsantiago/QGraphicsItem-Snapping/blob/master/snapBlocks.gif" alt="" height="50%" width="50%"/></br>
# License
[The MIT License (MIT)](http://www.opensource.org/licenses/mit-license.php)
