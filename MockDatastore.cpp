#include "MockDatastore.h"

json MockDatastore::getMembre(std::string membreUuid)
{
    try
    {
        return m_mapMembre.at(membreUuid);
    }
    catch (const std::exception&)
    {
        return json();
    }
    return json();
}

json MockDatastore::putMembre(json membreData)
{
    std::string uuid = membreData.at("uuid");
    
    if (uuid.empty()) return json();
    
    m_mapMembre[uuid] = membreData;
    return membreData;
}
