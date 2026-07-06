#pragma once

#include <discordpp.h>

namespace Shirag {
    class Discord {
    private:
        std::shared_ptr<discordpp::Client> client = std::make_shared<discordpp::Client>();
        discordpp::Activity activity;

    public:
        void init(uint64_t AppID);
        void runCallbacks();
        void setActivityState(std::string stateText);
        void setActivityDetails(std::string detailsText);
        void updateActivity();
    };
}