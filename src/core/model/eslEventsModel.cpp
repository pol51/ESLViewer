#include "eslEventsModel.h"

#include <core/model/eslEventsModelItem.h>

ESLEventsModel::ESLEventsModel(QObject *parent) : QAbstractItemModel(parent)
{
  _root = new ESLEventsModelItem(NULL);
  _root->appendChild(new ESLEventsModelItem(_root));
  _root->appendChild(new ESLEventsModelItem(_root));
  _root->appendChild(new ESLEventsModelItem(_root));
  _root->appendChild(new ESLEventsModelItem(_root));
}

ESLEventsModel::~ESLEventsModel()
{
  delete _root;
}

QModelIndex ESLEventsModel::index(int row, int column, const QModelIndex &parent) const
{
  if (!hasIndex(row, column, parent))
    return QModelIndex();

  ESLEventsModelItem *ParentItem;

  if (!parent.isValid())
    ParentItem = _root;
  else
    ParentItem = (ESLEventsModelItem*)parent.internalPointer();

  ESLEventsModelItem *ChildItem = ParentItem->child(row);
  if (ChildItem)
    return createIndex(row, column, ChildItem);
  else
    return QModelIndex();
}

QModelIndex ESLEventsModel::parent(const QModelIndex &child) const
{
  if (!child.isValid())
    return QModelIndex();

  ESLEventsModelItem *ParentItem = ((ESLEventsModelItem*)child.internalPointer())->parent();

  if (ParentItem == _root)
    return QModelIndex();

  return createIndex(ParentItem->row(), 0, ParentItem);
}

int ESLEventsModel::rowCount(const QModelIndex &parent) const
{
  if (parent.column() > 0)
    return 0;
  
  if (!parent.isValid())
    return _root->childCount();
  else
    return ((ESLEventsModelItem*)parent.internalPointer())->childCount();
}

int ESLEventsModel::columnCount(const QModelIndex &parent) const
{
  if (parent.isValid())
    return ((ESLEventsModelItem*)parent.internalPointer())->columnCount();
  return _root->columnCount();
}

QVariant ESLEventsModel::data(const QModelIndex &index, int role) const
{
  if (index.isValid())
    return ((ESLEventsModelItem*)index.internalPointer())->data(role);
  return QVariant();
}
