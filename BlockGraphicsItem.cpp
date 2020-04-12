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

#include "BlockGraphicsItem.h"

BlockGraphicsItem::BlockGraphicsItem(const QString &title, QGraphicsItem *parent) : QGraphicsItem(parent), m_title(title)
{
    this->setFlags(QGraphicsItem::ItemIsMovable |
                   QGraphicsItem::ItemIsSelectable |
                   QGraphicsItem::ItemSendsGeometryChanges);

    this->setAcceptDrops(true);
    this->setAcceptedMouseButtons(Qt::LeftButton);

    m_width = 20*9;
    m_height = 20*5;
    m_rect = QRect(1,1,m_width,m_height);

    m_color = Qt::lightGray;
    m_brush.setColor(m_color);

    m_marginHeight = m_height/4;

    m_penNotSelected = QPen();
    m_penNotSelected.setWidthF(0.5);

    m_penSelected = QPen(Qt::SolidLine);
    m_penSelected.setColor(Qt::red);
    m_penSelected.setWidthF(2);

    m_pen = m_penNotSelected;
    this->setZValue(0);

    m_overlaping = false;
}

int BlockGraphicsItem::type() const
{
    return Type;
}

QRectF BlockGraphicsItem::boundingRect() const
{
    return m_rect.marginsAdded(QMargins(0,m_marginHeight,0,m_marginHeight));
}

QPainterPath BlockGraphicsItem::shape() const
{
    QPainterPath path;
    path.addRect(m_rect);
    return path;
}

void BlockGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(m_pen);
    painter->setBrush(m_color);
    painter->drawRect(m_rect);

    QBrush b(Qt::white);
    painter->setBrush(b);

    QRect rectText(2,2,m_width-2,30);
    painter->setPen(Qt::NoPen);
    painter->drawRect(rectText);

    painter->setPen(m_simplePen);
    QFontMetrics m(painter->fontMetrics());
    painter->setPen("#404244");
    painter->drawText(rectText,Qt::AlignCenter,m_title);
}

void BlockGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << " -------------";
    for(BlockGraphicsItem*item:m_adjacentItems){
        qDebug() << " item:" << item;
    }

    this->setCursor(Qt::ClosedHandCursor);
    this->setSelected(true);

    QGraphicsItem::mousePressEvent(event);
}

QVariant BlockGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    // update selection red outline
    if(change == QGraphicsItem::ItemSelectedChange){
        this->setSelected(value.toBool());
    }

    // position changes, if item is being dragged
    // check if there's any other adjacent BlockGraphicsItem,
    // if so, snap to it (set position), and update m_adjacentItems pointers
    if(change == ItemPositionChange){

        if(QApplication::mouseButtons() == Qt::LeftButton){

            if(m_overlaping) return value.toPointF();

            QList<QGraphicsItem*> items = this->collidingItems(Qt::IntersectsItemBoundingRect);
            if(!items.isEmpty()){
                for(QGraphicsItem* item:items){
                    m_otherItem = qgraphicsitem_cast<BlockGraphicsItem*>(item);
                    m_otherItem->updateAdjacent();
                }
            }else{
                m_otherItem = nullptr;
            }

            if(!m_otherItem){
                return value.toPoint();
            }else{
                if(m_snap){
                    this->updateAdjacent();
                    if(this->pos().y() < m_otherItem->pos().y()){// above
                        return QPointF(m_otherItem->pos().x(),m_otherItem->pos().y()-m_height);
                    }else if(this->pos().y() > m_otherItem->pos().y()){// below
                        return QPointF(m_otherItem->pos().x(),m_otherItem->pos().y()+m_height);
                    }
                }
            }
        }
    }

    return QGraphicsItem::itemChange(change, value);
}

QRect BlockGraphicsItem::rect() const
{
    return m_rect;
}

void BlockGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // check if the mouse is hovering the item
    // so it can be (unsnaped)
    m_snap = this->contains(event->pos());

    // if the item is overlaping other, snnaping is disabled
    // so there wont be any (overlaped and snnaped items)
    m_overlaping = this->posOverlap(event->pos());

    QGraphicsItem::mouseMoveEvent(event);
}

void BlockGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(Qt::ArrowCursor);
    this->setSelected(false);
    QGraphicsItem::mouseReleaseEvent(event);
}

QString BlockGraphicsItem::title() const
{
    return m_title;
}

// change z value while item is selected,
// so there's no obstructions in the outline
void BlockGraphicsItem::setSelected(bool value)
{
    if(value){
        m_pen = m_penSelected;
        this->setZValue(10);
    }else{
        m_pen = m_penNotSelected;
        this->setZValue(0);
    }
}

// check with BLockGraphicsItem are connected (above, below) with
// the current item, then keep track of those with pointers
void BlockGraphicsItem::updateAdjacent()
{
    QList<QGraphicsItem*> items = this->collidingItems(Qt::IntersectsItemBoundingRect);
    m_adjacentItems = {nullptr,nullptr};

    if(m_overlaping) return;

    for(QGraphicsItem *item:items){
        BlockGraphicsItem *itm = qgraphicsitem_cast<BlockGraphicsItem*>(item);
        if(itm){
            if(this->pos().y() > itm->pos().y()){
                m_adjacentItems[0] = itm;
            }
            if(this->pos().y() < itm->pos().y()){
                m_adjacentItems[1] = itm;
            }
        }
    }
}

// check if the item is overlaping other BlockGraphicsItem
// if true, snapping is disable
bool BlockGraphicsItem::posOverlap(const QPointF &pos)
{
    QPointF posMap = this->mapToScene(pos);

    QList<QGraphicsItem*> items = this->collidingItems(Qt::IntersectsItemShape);

    for(QGraphicsItem*item:items){
        BlockGraphicsItem*itm = qgraphicsitem_cast<BlockGraphicsItem*>(item);
        if(itm){
            QRect rectFromScene(itm->pos().toPoint(),
                                itm->m_rect.size());
            int addMargin = itm->m_rect.width();
            rectFromScene = rectFromScene.marginsAdded(QMargins(addMargin,0,addMargin,0));

            if(rectFromScene.contains(posMap.toPoint())){
                return true;
            }
         }
    }

    return false;
}
