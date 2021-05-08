#include "hbimageview.h"

#include <QPainter>
#include <QDebug>

HBImageView::HBImageView(QWidget *parent) : QWidget(parent)
{


}

void HBImageView::configImage(const QPixmap map, HBContentMode mode)
{

    Qt::AspectRatioMode tMode = Qt::IgnoreAspectRatio;
    int w = width(), h = height();

    if (mode == IgnoreAspectRatio)
        tMode = Qt::IgnoreAspectRatio;
    else if (mode == KeepAspectRatio)
        tMode = Qt::KeepAspectRatio;
    else if (mode == KeepAspectCenter) {
        tMode = Qt::KeepAspectRatio;

        if ((float)w / (float) h > (float)map.width() / (float)map.height()) {
            //相对 图为竖图
            h = (float)map.width() / (float)w * map.height();
        } else {
            //相对 图为横图
            w = (float)map.height() / (float)h * map.width();
        }

     } else {
        tMode = Qt::KeepAspectRatioByExpanding;
        w = map.width();
        h = map.height();
    }

    QPixmap tempMap = map.scaled(w, h, tMode);

    switch (mode) {
    case IgnoreAspectRatio:
    case KeepAspectRatio:
        m_map = tempMap;
        break;
    case LeftTop: {
        m_map = tempMap.copy(0, 0, qMin(width(), tempMap.width()), qMin(height(), tempMap.height()));

        break;
    }
    case LeftBottom: {
        m_map = tempMap.copy(0, qMax(0, tempMap.height() - height()), qMin(width(), tempMap.width()), qMin(height(), tempMap.height()));
        break;
    }
    case RightTop: {
        m_map = tempMap.copy(qMax(0, tempMap.width() - width()), 0, qMin(width(), tempMap.width()), qMin(height(), tempMap.height()));
        break;
    }
    case RightBottom: {
        m_map = tempMap.copy(qMax(0, tempMap.width() - width()), qMax(0, tempMap.height() - height()), qMin(width(), tempMap.width()), qMin(height(), tempMap.height()));
        break;
    }
    case KeepAspectCenter:
    case Center: {
        int offx = (tempMap.width() - width()) / 2;
        //图大： offx > 0     图小：offx < 0
        int offy = (tempMap.height() - height()) / 2;

        m_map = tempMap.copy(offx, offy, width(), height());

        break;
    }

    }


    update();
}

void HBImageView::clear()
{
    m_map = QPixmap();
    update();
}


void HBImageView::paintEvent(QPaintEvent *event)
{
    if (m_map.isNull())
    {
        QWidget::paintEvent(event);
        return;
    }

    QPainter painter(this);
//    painter.drawPixmap(0, 0, width(), height(), m_map);

    int x = 0, y = 0;

    x = (width() - m_map.width()) / 2;
    x = x > 0 ? x : 0;

    y = (height() - m_map.height()) / 2;
    y = y > 0 ? y : 0;

    painter.drawImage(x, y, m_map.toImage());

}
