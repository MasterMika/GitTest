#ifndef VB_VISUALIZER_H
#define VB_VISUALIZER_H


#include <QtWidgets>
#include <QAudioBuffer>
#include <vector>

#include "vb_column.h"


class VB_visualizer : public QGraphicsScene
{
    Q_OBJECT

public:
    VB_visualizer(QRect rect, unsigned rows, unsigned cols);
    VB_visualizer(int x, int y, qreal width, qreal height, unsigned rows, unsigned cols);

    void setPadding(unsigned padding);

public slots:
    void test(const QAudioBuffer&);
    void vupdate(std::vector<unsigned> values);

private:
    unsigned m_num_rows;
    unsigned m_num_cols;
    unsigned half_flag = 0;
    std::vector<VB_column *> columns;

    unsigned m_padding = 1;
};

#endif // VB_VISUALIZER_H
