#include <QWidget>
#include <QMediaPlayer>
#include <QAudioProbe>
#include "vb_visualizer.h"

#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

//for playing the song
    QMediaPlayer *player = new QMediaPlayer();

//for geting raw data from song
    QAudioProbe *probe = new QAudioProbe;
    probe->setSource(player);

//setting the song and playing it
    player->setMedia(QUrl::fromLocalFile("/home/mika/VisualBeatz/Music/song.mp3"));
    player->setVolume(50);
    player->play();

//class for visualizing the audio
    VB_visualizer visualizer(0, 0, 300, 300, 35, 40);

//padding around the squares in the visualizer
    visualizer.setPadding(1);

    QGraphicsView view;
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "VisualBeatz"));
    view.setFixedSize(1000, 500);
    view.setScene(&visualizer);
    view.show();

//sending raw data via QAudioBuffer to the visualizer
    QObject::connect(probe, SIGNAL(audioBufferProbed(const QAudioBuffer &)), &visualizer, SLOT(update(const QAudioBuffer &)));


    return app.exec();
}
