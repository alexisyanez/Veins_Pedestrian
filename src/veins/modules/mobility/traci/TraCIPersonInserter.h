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



#pragma once

#include <queue>

#include "veins/veins.h"
#include "veins/modules/mobility/traci/TraCIScenarioManager.h"

namespace veins {
/**
 * @brief
 * Uses the TraCIScenarioManager to programmatically insert new vehicles at the TraCI server.
 *
 * This is done whenever the total number of active vehicles drops below a given number.
 *
 * See the Veins website <a href="http://veins.car2x.org/"> for a tutorial, documentation, and publications </a>.
 *
 * @author Christoph Sommer, David Eckhoff, Falko Dressler, Zheng Yao, Tobias Mayer, Alvaro Torres Cortes, Luca Bedogni
 *
 * @see TraCIScenarioManager
 *
 */
class VEINS_API TraCIPersonInserter : public cSimpleModule, public cListener {
public:
    TraCIPersonInserter();
    ~TraCIPersonInserter() override;
    int numInitStages() const override;
    void initialize(int stage) override;
    void finish() override;
    void finish(cComponent* component, simsignal_t signalID) override;
    void handleMessage(cMessage* msg) override;
    void receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details) override;
    void receiveSignal(cComponent* source, simsignal_t signalID, const SimTime& t, cObject* details) override;

protected:
    /**
     * adds a new vehicle to the queue which are tried to be inserted at the next SUMO time step;
     */
    void insertNewPerson();

    /**
     * tries to add all vehicles in the vehicle queue to SUMO;
     */
    void insertPerson();

    // parameters
    int personRngIndex;
    int numPersons;

    // internal
    TraCIScenarioManager* manager;
    cRNG* mobRng;
    std::map<int, std::queue<std::string>> personInsertQueue;
    std::set<std::string> queuedPersons;
    std::vector<std::string> routeIds;
    uint32_t personNameCounter;
    std::vector<std::string> personTypeIds;
};

} // namespace veins

