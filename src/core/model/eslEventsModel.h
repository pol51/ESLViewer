#ifndef __ESLEVENTSMODEL_H__
#define __ESLEVENTSMODEL_H__

#include <QtCore/QAbstractItemModel>
#include <QtCore/QMap>

class ESLEventsModelItem;

class ESLEventsModel : public QAbstractItemModel
{
  Q_OBJECT

  public:
    explicit ESLEventsModel(QObject *parent = NULL);
    ~ESLEventsModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

  protected:
    ESLEventsModelItem *_root;
};

#endif
