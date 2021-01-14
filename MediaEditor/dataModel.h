#ifndef dataModel_H
#define dataModel_H

#include <QAbstractTableModel>
#include "SQLData.h"
//#include "DataManage.h"


#define dim(x) (sizeof(x)/sizeof(x[0]))

class QDragMoveEvent;


class dataModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	explicit dataModel(TYPESETTINGS *pSettings,int nSize,QObject *parent=0);
	virtual ~dataModel();

public:
	int rowCount(const QModelIndex &parent=QModelIndex()) const;
	int columnCount(const QModelIndex &parent=QModelIndex()) const;
	QVariant data(const QModelIndex&,int) const;
	QVariant headerData(int section,Qt::Orientation orientation,int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &,const QVariant &,int);
	bool insertRows(int,int, const QModelIndex &parent=QModelIndex());
	bool removeRows(int,int, const QModelIndex &parent=QModelIndex());
	bool setVectors(std::vector<std::shared_ptr<CSQLData>> *pHeader,std::vector<std::shared_ptr<CSQLData>> *pDelItems,int nParentIndex=-1);
	void setEditor(std::shared_ptr<CEditSQLData> pEditor);
	void setMimeName(wchar_t *pszName);

	std::vector<std::shared_ptr<CSQLData>> *getVector()
	{
		return m_pvVector;
	}

	std::vector<std::shared_ptr<CSQLData>> *getDeletedItemsVector()
	{
		return m_pvDeletedItems;
	}


	bool setData(int nIndex,int nColumn,const QVariant &value,int nRole);
	bool removeRow(int nIndex);
	std::shared_ptr<CSQLData> insertRow();
	bool setModified(int nIndex);





	Qt::ItemFlags flags(const QModelIndex &index);
	void dragMoveEvent(QDragMoveEvent *event);
	Qt::DropActions supportedDropActions() const;


	bool dropMimeData(const QMimeData *data,Qt::DropAction action, int row, int column, const QModelIndex &parent);
	QStringList mimeTypes() const;
	QMimeData *mimeData(const QModelIndexList &indexes) const;



	QString m_strMime;


	std::shared_ptr<CEditSQLData> m_pEditor;
	std::vector<std::shared_ptr<CSQLData>> *m_pvVector;
	std::vector<std::shared_ptr<CSQLData>> *m_pvDeletedItems;

	bool isValid();

signals:
	void selectionChanged(int /*nTop*/,int /*nBottom*/);

private:
	int m_nColumnCount;
	bool m_bTableIsModified;
	TYPESETTINGS *m_pTypeSettings;
	int getNewCode();
	
};

#endif // distanceModel_H
  