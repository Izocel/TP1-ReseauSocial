#include "MockDatastore.h"

json MockDatastore::getMembre(std::string membreUuid)
{
    json membreJson;
    try
    {
        membreJson = m_mapMembre.at(membreUuid);
    }
    catch (const std::exception&)
    {
    }
    return membreJson;
}

json MockDatastore::getConversation(std::string messageID)
{
    json messagesJson;
    try
    {
        messagesJson =  m_mapMessages.at(messageID);
    }
    catch (const std::exception&)
    {

    }
    return messagesJson;
}

json MockDatastore::getRelations(std::string membreUuid)
{
    json relationJson;
    try
    {
        relationJson = m_mapRelations.at(membreUuid);
    }
    catch (const std::exception&)
    {
        
    }
    return relationJson;
}

json MockDatastore::putMembre(json membreData)
{

    std::string uuid = membreData.at("uuid");
    
    if (uuid.empty()) return json();
    
    m_mapMembre[uuid] = membreData;
    return membreData;
}

json MockDatastore::putMessage(std::string messageID, json messageData)
{
    m_mapMessages[messageID].push_back(messageData);
    return m_mapMessages[messageID];
}


json MockDatastore::putRelation(json relationData)
{
    std::string uuid = relationData.at("uuid");
    std::string relationUuid = relationData.at("relationUuid");

    if (uuid.empty() || relationUuid.empty()) return json();

    // Ajout de la relation source->cible 
    m_mapRelations[uuid].push_back(relationUuid);

    // Ajout de la relation inverse cible->source
    m_mapRelations[relationUuid].push_back(uuid);

    return json(relationUuid);
}
