#ifndef __ESLEVENTSMODELITEM_H__
#define __ESLEVENTSMODELITEM_H__

#include <QtCore/QList>
#include <QtCore/QVariant>

class ESLEventsModelItem
{
  public:
    ESLEventsModelItem(ESLEventsModelItem *parent) : _parent(parent) {}

    virtual QVariant data(int role) const { return QVariant(); }
    virtual int columnCount() const { return 1; }

    int childCount() const { return _data.size(); }
    ESLEventsModelItem *parent() { return _parent; }
    int row() const;
    const ESLEventsModelItem *parent() const { return _parent; }
    ESLEventsModelItem *child(const int row) const { return _data.at(row); }

    void appendChild(ESLEventsModelItem *childItem) { _data.append(childItem); }

  protected:
    QList<ESLEventsModelItem*> _data;
    ESLEventsModelItem *_parent;
};

#endif
