#ifndef MY360BUTTON_H
#define MY360BUTTON_H

#include <QPushButton>

/**
 * @brief The mainButton class
 *  用于主的图片
 */
class mainButton : public QPushButton
{
    Q_OBJECT
public:
    mainButton(QString pixnormal,QString pixenter,QString pixleave,QWidget*parent);
    ~mainButton();

};

/**
 * @brief The main2Button class
 *  //用于4太图片加下文字
 */
class main2Button:public QPushButton
{
    Q_OBJECT
public:
    main2Button(QString pixnormal,QString text,QWidget*parent);
};

/**
 * @brief The main3Button class
 *  //用于四态图片
 */
class main3Button:public QPushButton
{

};

/**
 * @brief The headButton class
 *  //头像按钮
 */
class headButton:public QPushButton
{

};

/**
 * @brief The wordslineButton class
 *  //下划线按钮
 */
class wordslineButton:public QPushButton
{

};

/**
 * @brief The checkButton class
 */
class checkButton:public QPushButton
{

};

/**
 * @brief The main4Button class
 *  //8个图与4个图
 */
class main4Button:public QPushButton
{

};

/**
 * @brief The cleanMainButton class
 *  //清理界面的按钮
 */
class cleanMainButton:public QPushButton
{

};

/**
 * @brief The main5Button class
 *  //用于四态图片加中间文字
 */
class main5Button:public QPushButton
{

};

/**
 * @brief The main6Button class
 */
class main6Button:public QPushButton
{

};

#endif // MY360BUTTON_H
