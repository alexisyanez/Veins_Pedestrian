//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <veins/modules/mobility/traci/TraCIPersonInserter.h>

//
// Copyright (C) 2006-2018 Christoph Sommer <sommer@ccs-labs.org>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include <vector>
#include <algorithm>

#include "veins/modules/mobility/traci/TraCIScenarioManager.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"

#include "veins/base/utils/FindModule.h"

Define_Module(veins::TraCIPersonInserter);

using namespace veins;

TraCIPersonInserter::TraCIPersonInserter()
    : mobRng(nullptr)
{
}

TraCIPersonInserter::~TraCIPersonInserter()
{
}

int TraCIPersonInserter::numInitStages() const
{
    return std::max(cSimpleModule::numInitStages(), 2);
}

void TraCIPersonInserter::initialize(int stage)
{
    cSimpleModule::initialize(stage);
    if (stage != 1) {
        return;
    }

    // internal 1
    manager = TraCIScenarioManagerAccess().get();

    // signals
    manager->subscribe(TraCIScenarioManager::traciModuleAddedSignal, this);
    manager->subscribe(TraCIScenarioManager::traciTimestepBeginSignal, this);

    // parameters
    personRngIndex = par("personRngIndex");
    numPersons = par("numPersons");

    // internal 2
    personNameCounter = 0;
    mobRng = getRNG(personRngIndex);
}

void TraCIPersonInserter::finish()
{
    unsubscribe(TraCIScenarioManager::traciModuleAddedSignal, this);
    unsubscribe(TraCIScenarioManager::traciTimestepBeginSignal, this);
}

void TraCIPersonInserter::finish(cComponent* component, simsignal_t signalID)
{
    cListener::finish(component, signalID);
}

void TraCIPersonInserter::handleMessage(cMessage* msg)
{
}

void TraCIPersonInserter::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details)
{
    if (signalID == TraCIScenarioManager::traciModuleAddedSignal) {
        ASSERT(manager->isConnected());
        cModule* mod = check_and_cast<cModule*>(obj);
        auto* mob = FindModule<TraCIMobility*>::findSubModule(mod);
        ASSERT(mob != nullptr);
        std::string nodeId = mob->getExternalId();
        if (queuedPersons.find(nodeId) != queuedPersons.end()) {
            queuedPersons.erase(nodeId);
        }
    }
}

void TraCIPersonInserter::receiveSignal(cComponent* source, simsignal_t signalID, const SimTime& t, cObject* details)
{
    if (signalID == TraCIScenarioManager::traciTimestepBeginSignal) {
        ASSERT(manager->isConnected());
        if (simTime() > 1) {
            if (personTypeIds.size() == 0) {
                std::list<std::string> vehTypes = manager->getCommandInterface()->getVehicleTypeIds();
                for (std::list<std::string>::const_iterator i = vehTypes.begin(); i != vehTypes.end(); ++i) {
                    if (i->substr(0, 8).compare("DEFAULT_") != 0) {
                        EV_DEBUG << *i << std::endl;
                        personTypeIds.push_back(*i);
                    }
                }
            }
            if (routeIds.size() == 0) {
                std::list<std::string> routes = manager->getCommandInterface()->getRouteIds();
                for (std::list<std::string>::const_iterator i = routes.begin(); i != routes.end(); ++i) {
                    std::string routeId = *i;
                    if (par("useRouteDistributions").boolValue() == true) {
                        if (std::count(routeId.begin(), routeId.end(), '#') >= 1) {
                            EV_DEBUG << "Omitting route " << routeId << " as it seems to be a member of a route distribution (found '#' in name)" << std::endl;
                            continue;
                        }
                    }
                    EV_DEBUG << "Adding " << routeId << " to list of possible routes" << std::endl;
                    routeIds.push_back(routeId);
                }
            }
            for (int i = manager->getManagedHosts().size() + queuedPersons.size(); i < numPersons; i++) {
                insertNewPerson();
            }
        }

        insertPerson();
    }
}

void TraCIPersonInserter::insertNewPerson()
{
    std::string type;
    if (personTypeIds.size()) {
        int vehTypeId = mobRng->intRand(personTypeIds.size());
        type = personTypeIds[vehTypeId];
    }
    else {
        type = "DEFAULT_PEDTYPE";
    }
    int routeId = mobRng->intRand(routeIds.size());
    personInsertQueue[routeId].push(type);
}

void TraCIPersonInserter::insertPerson()
{

    for (std::map<int, std::queue<std::string>>::iterator i = personInsertQueue.begin(); i != personInsertQueue.end();) {
        std::string route = routeIds[i->first];
        EV_DEBUG << "process " << route << std::endl;
        std::queue<std::string> persons = i->second;
        while (!i->second.empty()) {
            bool suc = false;
            std::string type = i->second.front();
            std::stringstream veh;
            veh << type << "_" << personNameCounter;
            EV_DEBUG << "trying to add " << veh.str() << " with " << route << " person type " << type << std::endl;

            suc = manager->getCommandInterface()->addPed(veh.str(), type, route, simTime());
            if (!suc) {
                i->second.pop();
            }
            else {
                EV_DEBUG << "successful inserted " << veh.str() << std::endl;
                queuedPersons.insert(veh.str());
                i->second.pop();
                personNameCounter++;
            }
        }
        std::map<int, std::queue<std::string>>::iterator tmp = i;
        ++tmp;
        personInsertQueue.erase(i);
        i = tmp;
    }
}
