#include "vb_visualizer.h"
#include "vb_column.h"

#include <iostream>
#include <iterator>
#include <algorithm>



VB_visualizer::VB_visualizer(QRect rect, unsigned rows, unsigned cols)
    :QGraphicsScene(),
      m_num_rows(rows), m_num_cols(cols)
    {
        this->setSceneRect(rect);
        this->setItemIndexMethod(QGraphicsScene::NoIndex);

        columns.resize(cols);

        for(unsigned i = 0 ; i < m_num_cols; i++){
            columns[i] = new VB_column(0, m_num_rows, rect.width() / cols, rect.height());
            columns[i]->setPos(rect.x() + i * rect.width() / cols, 0);
            this->addItem(columns[i]);
        }
    }



VB_visualizer::VB_visualizer(int x, int y, qreal width, qreal height, unsigned rows, unsigned cols)
    :QGraphicsScene(),
      m_num_rows(rows), m_num_cols(cols)
{
    this->setSceneRect(x, y, width, height);
    this->setItemIndexMethod(QGraphicsScene::NoIndex);
    columns.resize(cols);
    for(unsigned i = 0 ; i < m_num_cols; i++){
        columns[i] = new VB_column(0, m_num_rows, width / cols, height);
        columns[i]->setPos(x + i * width/cols, 0);
        this->addItem(columns[i]);
    }
}

void VB_visualizer::setPadding(unsigned padding)
{
    m_padding = padding;
    for(unsigned i = 0 ; i < m_num_cols; i++){
        columns[i]->setPadding(m_padding);
    }
}
void VB_visualizer::vupdate(std::vector<unsigned> values)
{
    for(unsigned i = 0 ; i < m_num_cols; i++){
        columns[i]->vupdate(values[i]);
    }
}

void VB_visualizer::test(const QAudioBuffer &buffer)
{
    std::vector<int> data ((int *)buffer.data(), (int *)buffer.data() + buffer.byteCount()/(sizeof(int) * 8));

    int max = *(std::max_element(data.begin(), data.end()));
    int min = *(std::min_element(data.begin(), data.end()));
    int absmax = abs(min) > abs(max) ? abs(min): abs(max);
    absmax /= m_num_rows / 2;
    absmax = absmax==0 ? 1: absmax;
//    std::cout << absmax << std::endl;
    auto data_iter = data.cbegin();
    int used_columns = m_num_cols / 2;

    int num_for_avg = data.size() / used_columns;
    for(unsigned i = half_flag * used_columns ; i < (half_flag + 1) * used_columns; i++, data_iter = data_iter + num_for_avg){
        int max_val = *(std::max_element(data_iter, data_iter + num_for_avg - 1));
        int min_val = *(std::min_element(data_iter, data_iter + num_for_avg - 1));
        int abs_val = abs(max_val) < abs(min_val)? max_val: min_val;
        int value = (abs_val / absmax);// + m_num_rows / 2;

        std::cout << value << std::endl;
        columns[i]->vupdate(value);
    }
    half_flag = half_flag == 0 ? 1 : 0;

    std::cout << std::endl << std::endl << std::endl;
}

