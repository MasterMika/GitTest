#include <QWidget>
#include <QMediaPlayer>
#include <QAudioProbe>
#include "vb_visualizer.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QMediaPlayer *player = new QMediaPlayer();
    QAudioProbe *probe = new QAudioProbe;
    probe->setSource(player);

    player->setMedia(QUrl::fromLocalFile("/home/mika/VisualBeatz/Music/FooFighters-Run.mp3"));
    player->setVolume(50);
    player->play();

    QGraphicsView view;
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "VisualBeatz"));
    view.resize(400, 300);

    VB_visualizer visualizer(view.rect(), 20, 20);

    visualizer.setPadding(2);

    view.resize(410, 310);
    view.setScene(&visualizer);
    view.show();

    QObject::connect(probe, SIGNAL(audioBufferProbed(const QAudioBuffer &)), &visualizer, SLOT(test(const QAudioBuffer&)));

//    QGraphicsScene scene;
//    scene.setSceneRect(-300, -300, 600, 600);
//    scene.addItem(new VB_column(-3, 10, 10, 200));
//    QGraphicsView view(&scene);
//    view.show();
    return app.exec();
}
