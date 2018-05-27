#ifndef VB_COLUMN_H
#define VB_COLUMN_H

#include <QGraphicsItem>


class VB_column : public QGraphicsItem{
public:
    VB_column(int value, unsigned rows);
    VB_column(int value, unsigned rows, qreal width, qreal height);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void vupdate(int value);

    void setPadding(unsigned padding);

    int value() const;

private:
    int m_value = 0;
    unsigned m_num_rows = 10;

    qreal m_width = 10;
    qreal m_height = 100;

    unsigned m_padding = 1;

    bool smer = true;
};
#endif // VB_COLUMN_H
