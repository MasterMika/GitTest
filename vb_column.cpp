#include "vb_column.h"

#include <QPainter>

//constructor for column with some default size
VB_column::VB_column(unsigned value, unsigned rows)
    :m_value(value),
      m_num_rows(rows)
{
}

//constructor for column with size
VB_column::VB_column(unsigned value, unsigned rows, double width, double height)
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
    //height of a single square the width being the width of the whole column
    double row_h = m_height / m_num_rows;

    //drawing m_num_rows squares verically
    for(unsigned i = 0; i < m_num_rows; i++)
    {
        if(i < m_value){
            painter->setBrush(Qt::black);
            painter->drawRect(m_padding,
                              m_height - row_h - i * row_h + m_padding,
                              m_width - 2 * m_padding,
                              row_h- 2 * m_padding);
        }else {
            painter->setPen(Qt::black);
            painter->setBrush(Qt::white);
            painter->drawRect(m_padding,
                              m_height - row_h - i * row_h + m_padding,
                              m_width - 2 * m_padding,
                              row_h- 2 * m_padding);
        }
    }
}
//setters
void VB_column::setValue    (const unsigned value)
{
    m_value = value;
}

void VB_column::setMaxRows  (const unsigned rows)
{
    m_num_rows = rows;
}

void VB_column::setWidth    (const double width)
{
    m_width = width;
}
void VB_column::setHeight   (const double height)
{
    m_height = height;
}

void VB_column::setPadding  (const unsigned padding)
{
    m_padding = padding;
}


//getters
unsigned VB_column::value   () const
{
    return m_value;
}

unsigned VB_column::maxRows () const
{
    return m_num_rows;
}

double VB_column::width     () const
{
    return m_width;
}
double VB_column::height    () const
{
    return m_height;
}

unsigned VB_column::padding () const
{
    return m_padding;
}
//member function for changing the value and updating the image of the column
void VB_column::updatewvalue(unsigned value)
{
    m_value = value;
    QGraphicsItem::update(this->boundingRect());
}

