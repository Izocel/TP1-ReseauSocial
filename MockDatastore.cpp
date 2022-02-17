#include "MockDatastore.h"

json MockDatastore::getMembre(std::string membreUuid)
{
<<<<<<< HEAD
    return m_mapMembre.at(membreUuid);
=======
    return json();
>>>>>>> 8e7c447c98c4fd0ca08b6402b868569b235d6278
}

json MockDatastore::putMembre(json membreData)
{
    return json();
}
