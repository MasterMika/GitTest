#ifndef VB_COLUMN_H
#define VB_COLUMN_H

#include <QGraphicsItem>

//Class that inherits QGraphicsItem that draws a single column for the visualizer

class VB_column : public QGraphicsItem{
public:
//constructors
    VB_column(unsigned value, unsigned rows);
    VB_column(unsigned value, unsigned rows, double width, double height);

//QGraphicsItem inherited member funcs
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
//setters
    void setValue    (const unsigned value);

    void setMaxRows  (const unsigned rows);

    void setWidth    (const double width);
    void setHeight   (const double height);

    void setPadding  (const unsigned padding);

//getters
    unsigned value   () const;

    unsigned maxRows () const;

    double width     () const;
    double height    () const;

    unsigned padding () const;

//member function for changing the value and updating the image of the column
    void updatewvalue(unsigned value);
private:
//column value
    unsigned m_value = 0;

//column max number of rows
    unsigned m_num_rows = 10;

//column dinemsions
    double m_width = 10;
    double m_height = 100;

//column padding between rows and edges
    unsigned m_padding = 1;
};
#endif // VB_COLUMN_H
