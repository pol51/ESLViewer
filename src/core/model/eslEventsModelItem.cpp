#include "eslEventsModelItem.h"

int ESLEventsModelItem::row() const
{
  if (_parent)
    return _parent->_data.indexOf((ESLEventsModelItem*)this);
  return 0;
}
