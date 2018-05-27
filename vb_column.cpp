#include "vb_column.h"
#include "drawfunc.h"

#include <QPainter>
#include <iostream>


VB_column::VB_column(int value, unsigned rows)
    :m_value(value),
      m_num_rows(rows)
{
}

VB_column::VB_column(int value, unsigned rows, qreal width, qreal height)
    :m_value(value), m_num_rows(rows),
      m_width(width), m_height(height)
{
}

QRectF VB_column::boundingRect() const
{
    return QRectF(0 , 0,
                  m_width, m_height);
}

void VB_column::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    qreal row_h = m_height / m_num_rows;
    DrawFunc df;
    int help_value;

    for(unsigned i = 0; i < m_num_rows; i++)
    {
        help_value = (i >= m_num_rows / 2 ? i + 1: i) - m_num_rows / 2;

        df((help_value <= m_value && m_value > 0 && help_value > 0) ||
           (help_value >= m_value && m_value < 0 && help_value < 0),
               painter,
               0,
               m_height - row_h - i * row_h,
               m_width,
               row_h,
               m_padding
               );
    }
}

void VB_column::vupdate(int value)
{
    m_value = value;
    QGraphicsItem::update(this->boundingRect());
}

void VB_column::setPadding(unsigned padding)
{
    m_padding = padding;
}

int VB_column::value() const
{
    return m_value;
}
