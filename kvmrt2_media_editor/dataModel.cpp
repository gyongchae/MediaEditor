

#include "dataModel.h"
#include <QDragMoveEvent>
#include <QStringList>
#include <QMimeData>

///#ifndef NOMINMAX

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

//#endif  /* NOMINMAX */



//const QString g_strLEDMime = "application/ledindicator";

dataModel::dataModel(TYPESETTINGS *pSettings,int nColumnCount,QObject *parent)
	: QAbstractTableModel(parent),m_bTableIsModified(false),m_nColumnCount(nColumnCount),m_pTypeSettings(pSettings)
		,m_pvVector(nullptr),m_pvDeletedItems(nullptr)
{

}

dataModel::~dataModel()
{

}

Qt::DropActions dataModel::supportedDropActions() const
{
	return Qt::MoveAction;
}

Qt::ItemFlags dataModel::flags(const QModelIndex &index) const
{
	Qt::ItemFlags theFlags = QAbstractTableModel::flags(index);
	if(index.isValid())
	{
		Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);
		if (index.isValid()) 
		{
			return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | defaultFlags;
		}
		else 
		{
			return Qt::ItemIsDropEnabled | Qt::ItemIsEnabled | Qt::ItemIsSelectable | defaultFlags;
		}
	}
	return theFlags;
}

void dataModel::dragMoveEvent(QDragMoveEvent *event)
{
	event->setDropAction(Qt::MoveAction);
	event->accept();
}

int dataModel::rowCount(const QModelIndex &) const
{
	if(m_pvVector)
		return m_pvVector->size();
	else
		return 0;
}

int dataModel::columnCount(const QModelIndex &) const
{
	return m_nColumnCount;
}

QVariant dataModel::data(const QModelIndex &index,int role) const
{
	if(!index.isValid())
		return QVariant();
	if(role==Qt::TextAlignmentRole)
	{
		return int(Qt::AlignLeft|Qt::AlignVCenter);
	}
	else if((role==Qt::DisplayRole)||(role==Qt::EditRole))
	{
		int nIndex=index.row();
		int nColumn=index.column();
		if(nColumn<m_nColumnCount)
		{
			(*m_pvVector)[nIndex].get()->MappingMembers();
			switch(m_pTypeSettings[nColumn].nTYPE)
			{
			case TYPE_INTEGER:
				{
					int nValue=(*((int*)(m_pTypeSettings[nColumn].POINTER)));
					return QVariant(*((int*)(m_pTypeSettings[nColumn].POINTER)));
				}
				break;
			case TYPE_TEXT:
				{
					wchar_t *p=(wchar_t*)m_pTypeSettings[nColumn].POINTER;
					return QString::fromWCharArray((wchar_t*)m_pTypeSettings[nColumn].POINTER);
				}
				break;
			case TYPE_FLOAT:
				{
					float fValue = (*((float*)(m_pTypeSettings[nColumn].POINTER)));
					return QVariant(*((float*)(m_pTypeSettings[nColumn].POINTER)));
				}
				break;
			case TYPE_DOUBLE:
				{
					double dValue=(*((double*)(m_pTypeSettings[nColumn].POINTER)));
					return QVariant(*((double*)(m_pTypeSettings[nColumn].POINTER)));
				}
				break;
			case TYPE_DATALENGTH:
				{
					return QVariant(*((unsigned int*)(m_pTypeSettings[nColumn].POINTER)));
				}
				break;
			case TYPE_DATA:
				{
					std::shared_ptr<unsigned char> *pByte=(std::shared_ptr<unsigned char> *)m_pTypeSettings[nColumn].POINTER;
					unsigned char *pPtr=(unsigned char*)pByte->get();
					return QVariant((unsigned int)pByte->get());
				}
				break;
			}
		}
	}
	return QVariant();
}

QVariant dataModel::headerData(int section,Qt::Orientation orientation,int role) const
{
	if(role!=Qt::DisplayRole)
		return QVariant();
	if (orientation == Qt::Horizontal) 
	{
		if(section<m_nColumnCount)
			return QString::fromWCharArray(m_pTypeSettings[section].szCOLUMNNAME);
	}
	return section + 1;
}

bool dataModel::setData(const QModelIndex &index,const QVariant &value,int role)
{
	if (!index.isValid() || role != Qt::EditRole ||
		index.row() < 0 || index.row() >= m_pvVector->size())
		return false;
	int nIndex=index.row();
	int nColumn=index.column();
	bool bOk=false;
	if(nColumn<m_nColumnCount)
	{
		(*m_pvVector)[nIndex].get()->MappingMembers();
		switch(m_pTypeSettings[nColumn].nTYPE)
		{
		case TYPE_INTEGER:
			{
				int nValue=value.toInt(&bOk);
				if(bOk)
				{
					(*m_pvVector)[nIndex].get()->SetData(nColumn,(void*)(&nValue));
				}
			}
			break;
		case TYPE_TEXT:
			{
				std::shared_ptr<wchar_t> pByte=std::shared_ptr<wchar_t>((wchar_t*)malloc((value.toString().length()+1)*sizeof(wchar_t)),free);
				memset(pByte.get(),0,sizeof(wchar_t)*(value.toString().length()+1));
				wcscpy(pByte.get(),value.toString().toStdWString().c_str());
				(*m_pvVector)[nIndex].get()->SetData(nColumn,(void*)pByte.get());
			}
			break;
		case TYPE_DOUBLE:
			{
				double dValue=value.toDouble(&bOk);
				if(bOk)
				{
					(*m_pvVector)[nIndex].get()->SetData(nColumn,(void*)(&dValue));
				}
			}
			break;

		case TYPE_FLOAT:
			{
				float fValue = value.toFloat(&bOk);
				if (bOk)
				{
					(*m_pvVector)[nIndex].get()->SetData(nColumn, (void*)(&fValue));
				}
			}
			break;
		case TYPE_DATALENGTH:
			{
				int nValue=value.toInt(&bOk);
				if(bOk)
				{
					(*m_pvVector)[nIndex].get()->SetData(nColumn,(void*)(&nValue));
				}
			}
			break;
		case TYPE_DATA:
			{
				void *pBuffer=(void *)value.toUInt(&bOk);
				if(bOk)
				{
					(*m_pvVector)[nIndex].get()->SetData(nColumn,pBuffer);
				}
			}
			break;
		}
	}
	else
		Q_ASSERT(false);
	emit dataChanged(index, index);
	return true;
}

bool dataModel::insertRows(int row, int count, const QModelIndex&)
{
	beginInsertRows(QModelIndex(), row, row + count - 1);
	if(m_pvVector)
		m_pEditor->Insert(row);
	endInsertRows();
	return true;
}

bool dataModel::removeRows( int row, int count, const QModelIndex&)
{
	beginRemoveRows(QModelIndex(), row, row + count - 1);
	if(m_pvVector)
		m_pEditor->Remove(row);
	m_bTableIsModified=true;		
	endRemoveRows();
	return true;
}



bool dataModel::setData(int nIndex,int nColumn,const QVariant &value,int nRole)
{
	std::vector<std::shared_ptr<CSQLData>>::iterator nit;
	nit=find_if(m_pvVector->begin(),m_pvVector->end(),findSQLData(nIndex));
	if(nit!=m_pvVector->end())
	{
		int row=distance(m_pvVector->begin(),nit);
		QModelIndex indexValid=index(row,nColumn);
		if(indexValid.isValid())
		{
			setData(indexValid,value,nRole);
			return true;
		}	
	}
	return false;
}

bool dataModel::removeRow(int nIndex)
{
	std::vector<std::shared_ptr<CSQLData>>::iterator nit;
	nit=find_if(m_pvVector->begin(),m_pvVector->end(),findSQLData(nIndex));
	if(nit!=m_pvVector->end())
	{
		int row=distance(m_pvVector->begin(),nit);
		beginRemoveRows(QModelIndex(), row, row);
		if(m_pvVector)
			m_pEditor->Remove(row);
		m_bTableIsModified=true;		
		endRemoveRows();
		return true;
	}
	return false;
}

std::shared_ptr<CSQLData> dataModel::insertRow()
{
	int nRetVal=-1;
	int row=m_pvVector->size();
	beginInsertRows(QModelIndex(), row, row);
	if(m_pvVector)
		m_pEditor->Insert(row);
	endInsertRows();
	return m_pvVector->at(row);
}


bool dataModel::setModified(int nIndex)
{
	std::vector<std::shared_ptr<CSQLData>>::iterator nit;
	nit=find_if(m_pvVector->begin(),m_pvVector->end(),findSQLData(nIndex));
	if(nit!=m_pvVector->end())
	{
		if(nit->get()->GetRecordState()==EDIT_NOT_MODIFIED)
		{
			nit->get()->SetRecordState(EDIT_UPDATED);
			return true;
		}
	}
	return false;
}




bool dataModel::setVectors(std::vector<std::shared_ptr<CSQLData>> *pVector,std::vector<std::shared_ptr<CSQLData>> *pDeletedItem,int nParentIndex)
{
	if(pVector&&pDeletedItem)
	{
#if QT_VERSION >= 0x050000
		beginResetModel();
		m_pvVector = pVector;
		m_pvDeletedItems = pDeletedItem;
		m_pEditor->SetVectors(pVector, pDeletedItem);
		if (nParentIndex != -1)
		{
			m_pEditor->SetCurParentIndex(nParentIndex);
		}
		endResetModel();
#else if
		m_pvVector = pVector;
		m_pvDeletedItems = pDeletedItem;
		m_pEditor->SetVectors(pVector, pDeletedItem);
		if (nParentIndex != -1)
		{
			m_pEditor->SetCurParentIndex(nParentIndex);
		}
		reset();
#endif

		return true;
	}
	else
	{

#if QT_VERSION >= 0x050000
		beginResetModel();
		m_pvVector = nullptr;
		m_pvDeletedItems = nullptr;
		endResetModel();
#else if
		m_pvVector = nullptr;
		m_pvDeletedItems = nullptr;
		reset();
#endif
	}
	return false;
}


int dataModel::getNewCode()
{
	int nValue=0;
// 	vector<CTrainHeaderTable*>::iterator nit;
// 	for(nit=m_pvVector->begin();nit!=m_pvVector->end();nit++)
// 	{
// 		nValue=max(nValue,(*nit)->nNo);
// 	}
	return ++nValue;
}

void dataModel::setEditor(std::shared_ptr<CEditSQLData> pEditor)
{
	m_pEditor=pEditor;
	wchar_t *pTableName=m_pEditor->GetTableName();
	if(pTableName)
		setMimeName(pTableName);
}


void dataModel::setMimeName(wchar_t *pszName)
{
	m_strMime="application/"+QString::fromStdWString(pszName);
}

QStringList dataModel::mimeTypes() const
{
	return QStringList() << m_strMime;
}

QMimeData *dataModel::mimeData(const QModelIndexList &indexes) const
{
	int nMin,nMax;
	Q_ASSERT(indexes.count());
	nMax=nMin=indexes.at(0).row();
	if(indexes.count())
	{
		for(int i=0;i<indexes.count();i++)
		{
			nMin=min(nMin,indexes.at(i).row());
			nMax=max(nMax,indexes.at(i).row());
		}	
		QMimeData *mimeData = new QMimeData;
		mimeData->setHtml(QString("%1").arg(m_pvVector->at(nMin)->GetIndex()));
		mimeData->setData(m_strMime,nullptr);
		QString strText=QString("%1,%2").arg(nMin).arg(nMax);
		mimeData->setText(strText);
		return mimeData;
	}
	return 0;
}


bool dataModel::dropMimeData(const QMimeData *mimeData,
							 Qt::DropAction action, int row, int column,
							 const QModelIndex &parent)
{
	if (action == Qt::IgnoreAction)
		return true;
	if (action != Qt::MoveAction || !mimeData || !mimeData->hasFormat(m_strMime))
		return false;

	QStringList strList=mimeData->text().split(",");
	Q_ASSERT(strList.count()==2);
	int nMin=strList.takeFirst().toInt();
	int nMax=strList.takeFirst().toInt();
	int nRow=parent.row();
	if(parent.isValid())
	{
		int nDelta=nRow-(nMax-nMin);
		std::vector<std::shared_ptr<CSQLData>> vVector;
	
		vVector.insert(vVector.begin(),m_pvVector->begin()+nMin,m_pvVector->begin()+nMax+1);
		beginRemoveRows(parent, nMin, nMax);
		m_pvVector->erase(m_pvVector->begin()+nMin,m_pvVector->begin()+nMax+1);
		endRemoveRows();



		if(nRow<nMin)
		{
			beginInsertRows(parent,nRow,nRow+vVector.size());
			m_pvVector->insert(m_pvVector->begin()+nRow,vVector.begin(),vVector.end());
			endInsertRows();
			emit selectionChanged(nRow,nRow+vVector.size()-1);
		}

		if(nRow>nMax)
		{
			beginInsertRows(parent,nDelta,nDelta+vVector.size());
			m_pvVector->insert(m_pvVector->begin()+nDelta,vVector.begin(),vVector.end());
			endInsertRows();
			emit selectionChanged(nDelta,nDelta+vVector.size()-1);
		}
		return true;
	}
// 	if (TaskItem *item = itemForIndex(parent)) {
// 		emit stopTiming();
// 		QByteArray xmlData = qUncompress(mimeData->data(MimeType));
// 		QXmlStreamReader reader(xmlData);
// 		if (row == -1)
// 			row = parent.isValid() ? parent.row()
// 			: rootItem->childCount();
// 		beginInsertRows(parent, row, row);
// 		readTasks(&reader, item);
// 		endInsertRows();
// 		return true;
// 	}
	return false;
}

bool dataModel::isValid()
{
	if(m_pvVector&&m_pvDeletedItems)
		return true;
	return false;
}