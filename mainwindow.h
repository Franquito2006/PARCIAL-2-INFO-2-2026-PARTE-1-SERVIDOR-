#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <qtcpserver.h>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;


private slots:
    void iniciar_servidor();
    void nueva_conexion();
    void leer_datos();

private:
    Ui::MainWindow *ui;
    QTcpServer servidor;
    QTcpSocket *socket;
};



#endif // MAINWINDOW_H
