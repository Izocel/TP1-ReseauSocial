#pragma once
#include <iostream>
#include <sstream>
#include <chrono>
#include "Membre.h"
#include "Serveur.h"
#include "RequeteClient.h"
#include "ReponseServeur.h"

//// Third-Party
#include "json.hpp"
using json = nlohmann::json;
// Ref: https://github.com/nlohmann/json#readme