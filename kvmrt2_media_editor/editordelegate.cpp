#include "editorDelegate.h"
#include <QLineEdit>
#include <qdebug.h>

editorDelegate::editorDelegate(QObject *parent)
	: QSqlRelationalDelegate(parent)
{
}

editorDelegate::~editorDelegate()
{
}


void editorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	int nValueExt;
	char uTemp[2];
	memset(uTemp,0,sizeof(uTemp));
	QStyleOptionViewItem myOption;
	uTemp[0]=(char)index.model()->data(index,Qt::DisplayRole).toInt();
	myOption=option;
	myOption.displayAlignment=Qt::AlignCenter|Qt::AlignVCenter;
	drawDisplay(painter,myOption,myOption.rect,QString(uTemp));
	drawFocus(painter,myOption,myOption.rect);
}
QWidget* editorDelegate::createEditor(QWidget *aParent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QLineEdit  *editor=new QLineEdit (aParent);
	connect(editor,SIGNAL(currentIndexChanged(int)),this,SLOT(commitAndCloseEditor()));
	return editor;	
}
void editorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	char uTemp[2];
	memset(uTemp,0,sizeof(uTemp));
	uTemp[0]=(char)index.model()->data(index,Qt::DisplayRole).toInt();
	QLineEdit  *lineEdit=qobject_cast<QLineEdit *>(editor);
	if(uTemp[0])	
		lineEdit->setText(uTemp);
	else
		lineEdit->setText("0");
}
void editorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	char uTemp[2];
	memset(uTemp,0,sizeof(uTemp));
	QLineEdit  *lineEdit=qobject_cast<QLineEdit *>(editor);
	uTemp[0]=lineEdit->text().toStdString().at(0);
	model->setData(index,uTemp[0]);
}

void editorDelegate::commitAndCloseEditor()
{
	QLineEdit  *lineEdit=qobject_cast<QLineEdit *>(sender());
	emit commitData(lineEdit);
	emit closeEditor(lineEdit);
}