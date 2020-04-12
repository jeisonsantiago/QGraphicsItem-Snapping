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

#ifndef BLOCKGRAPHICSITEM_H
#define BLOCKGRAPHICSITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QRect>
#include <QDebug>
#include <QApplication>
#include <QVariant>
#include <QMargins>
#include <QPointF>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>

class BlockGraphicsItem : public QGraphicsItem
{

public:
    explicit BlockGraphicsItem(const QString &title = nullptr, QGraphicsItem *parent = nullptr);

    enum { Type = UserType + 1 };
    int type() const override;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QRect rect() const;
    QString title() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QString m_title;
    QRect m_rect;

    int m_width;
    int m_height;
    int m_marginHeight;

    QBrush m_brush;
    QPen m_pen;
    QPen m_simplePen;
    QPen m_penSelected;
    QPen m_penNotSelected;
    QColor m_color;

    bool m_snap;
    bool m_overlaping;

    BlockGraphicsItem *m_otherItem = nullptr;

    // {top, bottom}
    QVector<BlockGraphicsItem*> m_adjacentItems = {nullptr,nullptr};

    void setSelected(bool value);
    void updateAdjacent();
    bool posOverlap(const QPointF &pos);
};

#endif // BLOCKGRAPHICSITEM_H

