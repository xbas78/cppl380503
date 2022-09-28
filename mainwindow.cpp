#include "mainwindow.h"

QImage MainWindow::blurImage(QImage src, int blurRadius) {
  if (src.isNull()) return QImage();
  QGraphicsScene scene;
  QGraphicsPixmapItem item;
  item.setPixmap(QPixmap::fromImage(src));
  auto *blur = new QGraphicsBlurEffect;
  blur->setBlurRadius(blurRadius);
  item.setGraphicsEffect(blur);
  scene.addItem(&item);
  QImage result(src.size(), QImage::Format::Format_ARGB32);
  result.fill(Qt::transparent);
  QPainter painter(&result);
  scene.render(&painter, QRectF(),
               QRectF(0, 0, src.width(), src.height()));
  return result;
}

void MainWindow::on_horizontalSlider_valueChanged(int value) {
  label->setPixmap(
    QPixmap::fromImage(
      blurImage(QImage(filePath), value).scaled(
        label->width(), label->height(), Qt::KeepAspectRatio)));
}

void MainWindow::on_pushButton_clicked() {
  filePath = QFileDialog::getOpenFileName(
    nullptr, "Open", "./", "image (*.jpg)");
  label->setPixmap(
    QPixmap::fromImage(
      QImage(filePath).scaled(
        label->width(), label->height(), Qt::KeepAspectRatio)));
}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
  centralWidget = new QWidget;
  gridLayout = new QGridLayout(centralWidget);
  label = new QLabel(centralWidget);
  horizontalSlider = new QSlider(centralWidget);
  pushButton = new QPushButton(centralWidget);
  pushButton->setText("Open");

  horizontalSlider->setMaximum(10);
  horizontalSlider->setOrientation(Qt::Horizontal);

  gridLayout->addWidget(label, 0, 0, 1, 1);
  gridLayout->addWidget(horizontalSlider, 1, 0, 1, 1);
  gridLayout->addWidget(pushButton, 2, 0, 1, 1);

  centralWidget->setLayout(gridLayout);
  setCentralWidget(centralWidget);
  resize(640, 480);

  QObject::connect(
    pushButton, &QPushButton::clicked,
    this, &MainWindow::on_pushButton_clicked
  );

  QObject::connect(
    horizontalSlider, &QSlider::valueChanged,
    this, &MainWindow::on_horizontalSlider_valueChanged
  );
}
