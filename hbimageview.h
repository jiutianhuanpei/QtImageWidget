#ifndef HBIMAGEVIEW_H
#define HBIMAGEVIEW_H

#include <QWidget>
#include <QPixmap>

class HBImageView : public QWidget
{
    Q_OBJECT
public:

    enum HBContentMode {


        IgnoreAspectRatio,  //填充
        KeepAspectRatio,    //等比例
        KeepAspectCenter,   //等比例适应居中

        //显示原图的哪部分
        LeftTop, //显示左上角
        RightTop,
        LeftBottom,
        RightBottom,
        Center
    };


    explicit HBImageView(QWidget *parent = nullptr);

public slots:
    void configImage(const QPixmap map, HBContentMode model = KeepAspectCenter);

    void clear();

private:
    QPixmap m_map;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // HBIMAGEVIEW_H
