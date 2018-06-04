#include "vb_visualizer.h"
#include "vb_column.h"

#include <algorithm>
#include <iostream>
#include <iterator>



VB_visualizer::VB_visualizer(QRect rect, unsigned rows, unsigned cols)
    :QGraphicsScene(),
      m_x       (rect.x()),
      m_y       (rect.y()),
      m_height  (rect.height()),
      m_width   (rect.width()),
      m_num_rows(rows),
      m_num_cols(cols)
    {
        this->setSceneRect(rect);
        columns.resize(cols);
        for(unsigned i = 0 ; i < m_num_cols; i++){
            //creating columns with width being the width of the visualizer divided by the number of columns
            columns[i] = new VB_column(0, m_num_rows, m_width / m_num_cols, m_height);
            //positioning them
            columns[i]->setPos(m_x + i * m_width / m_num_cols, m_y);
            //adding them to the scene(visualizer)
            this->addItem(columns[i]);
        }
    }



VB_visualizer::VB_visualizer(int x, int y, double width, double height, unsigned rows, unsigned cols)
    :QGraphicsScene(),
      m_x       (x),
      m_y       (y),
      m_height  (height),
      m_width   (width),
      m_num_rows(rows),
      m_num_cols(cols)
{
    this->setSceneRect(m_x, m_y, m_width, m_height);
    columns.resize(cols);
    for(unsigned i = 0 ; i < m_num_cols; i++){
        //creating columns with width being the width of the visualizer divided by the number of columns
        columns[i] = new VB_column(0, m_num_rows, m_width / m_num_cols, m_height);
        //positioning them
        columns[i]->setPos(m_x + i * m_width / m_num_cols, m_y);
        //adding them to the scene(visualizer)
        this->addItem(columns[i]);
    }
}
//setters
void VB_visualizer::setRowsNum(const unsigned rows)
{
    m_num_rows = rows;
    //setting the number of rows for each column
    for(unsigned i = 0 ; i < m_num_cols; i++){
        columns[i]->setMaxRows(m_num_rows);
    }
}
void VB_visualizer::setColumnsNum(const unsigned cols)
{

    m_num_cols = cols;
    //deleting all columns from visualizer
    this->clear();
    //resizing the vector for the new number of columns
    columns.resize(m_num_cols);
    //creating new number of columns
    for(unsigned i = 0 ; i < m_num_cols; i++){
        columns[i] = new VB_column(0, m_num_rows, m_width / m_num_cols, m_height);
        columns[i]->setPos(m_x + i * m_width / m_num_cols, m_y);
        this->addItem(columns[i]);
    }
}

void VB_visualizer::setHeight(const double height)
{
    m_height = height;
    //resizing the scene(visualizer) rectangle
    this->setSceneRect(m_x, m_y, m_width, m_height);
    //setting the height for each column
    for(unsigned i = 0 ; i < m_num_cols; i++){
        columns[i]->setHeight(m_height);
    }
}
void VB_visualizer::setWidth(const double width)
{
    m_width = width;
    //resizing the scene(visualizer) rectangle
    this->setSceneRect(m_x, m_y, m_width, m_height);
    //setting the width for and repositioning each column
    for(unsigned i = 0 ; i < m_num_cols; i++){
        columns[i]->setWidth(m_width / m_num_cols);
        columns[i]->setPos(m_x + i * m_width / m_num_cols, m_y);
    }
}

void VB_visualizer::setPadding(unsigned padding)
{
    m_padding = padding;
    //setting the padding for each column
    for(unsigned i = 0 ; i < m_num_cols; i++){
        columns[i]->setPadding(m_padding);
    }
}

//getters
unsigned VB_visualizer::rowsNum() const
{
    return m_num_rows;
}
unsigned VB_visualizer::columnsNum() const
{
    return m_num_cols;
}
double VB_visualizer::height() const
{
    return m_height;
}
double VB_visualizer::width() const
{
    return m_width;
}
unsigned VB_visualizer::padding() const
{
    return m_padding;
}


void VB_visualizer::update(const QAudioBuffer &buffer)
{
    //transforming raw data to a vector of ints
    std::vector<int> data ((int *)buffer.constData(), (int *)buffer.constData() + buffer.byteCount()/(sizeof(int)));
    //geting only positive numbers
    std::transform(data.begin(), data.end(), data.begin(), abs);
    //value of one unit
    int max = *(std::max_element(data.begin(), data.end())) / m_num_rows;
    max = max == 0 ? 1: max;

    auto data_iter = data.cbegin();
    //samples per group for one column
    int samples_per_group = data.size() / m_num_cols;
    //going through the columns and samples_per_group of samples
    for(unsigned i = 0; i < m_num_cols; i++, data_iter = data_iter + samples_per_group){
        //number of units of one column
        int value = *(std::max_element(data_iter, data_iter + samples_per_group - 1)) / max;
        //updating the column
        columns[i]->updatewvalue(value);
    }
}

