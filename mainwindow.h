#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QPainter>

class MainWindow : public QMainWindow {

  QWidget *centralWidget;
  QGridLayout *gridLayout;
  QLabel *label;
  QSlider *horizontalSlider;
  QPushButton *pushButton;
  QString filePath = nullptr;

  QImage blurImage(QImage src, int blurRadius);

  void on_horizontalSlider_valueChanged(int value);

  void on_pushButton_clicked();

public:
  explicit MainWindow(QWidget *parent = nullptr);
};
