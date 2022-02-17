#include "MockDatastore.h"

json MockDatastore::getMembre(std::string membreUuid)
{
    return m_mapMembre.at(membreUuid);
}

json MockDatastore::putMembre(json membreData)
{
    return json();
}
