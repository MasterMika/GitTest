#ifndef VB_VISUALIZER_H
#define VB_VISUALIZER_H


#include <QtWidgets>
#include <QAudioBuffer>
#include <vector>

#include "vb_column.h"

//Class that inherits QGraphicsScene that puts a certain number of vb_column

class VB_visualizer : public QGraphicsScene
{
    Q_OBJECT

public:
//constructors
    VB_visualizer(QRect rect, unsigned rows, unsigned cols);
    VB_visualizer(int x, int y, double width, double height, unsigned rows, unsigned cols);

//setters
    void setRowsNum     (const unsigned rows);
    void setColumnsNum  (const unsigned cols);

    void setHeight      (const double height);
    void setWidth       (const double width);

    void setPadding     (unsigned padding);

//getters
    unsigned rowsNum    () const;
    unsigned columnsNum () const;

    double height       () const;
    double width        () const;

    unsigned padding    () const;

public slots:
//slot for updating the scene using raw data from QAudioProbe
    void update(const QAudioBuffer&);

private:
//coordinates
    double m_x = 0;
    double m_y = 0;
//number of rows for each column
    unsigned m_num_rows = 10;
//number of columns in visualizer
    unsigned m_num_cols = 10;
//visualizer dimensions
    double m_height = 100.0;
    double m_width = 100.0;
//padding for the columns
    unsigned m_padding = 1;
//vector containing pointers to all columns
    std::vector<VB_column *> columns;
};

#endif // VB_VISUALIZER_H
